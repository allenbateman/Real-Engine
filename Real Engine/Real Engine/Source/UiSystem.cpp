#include "UiSystem.h"
#include "Window.h"

UiSystem::UiSystem(bool isActive) : Module(isActive)
{
}

UiSystem::~UiSystem()
{
}

bool UiSystem::Start()
{

    // Setup Dear ImGui context------------------------------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    io->ConfigViewportsNoTaskBarIcon = true;
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(app->window->window, true);
	ImGui_ImplOpenGL3_Init("#version 410");

	camViewport = new Viewport(eViewport,true);
    mainRenderer = new RendererPanel(eRender_Settings,false);
    fpsGraph = new FPSGraph(eFPS_Graph, false);
	panelList.push_back(camViewport);
    panelList.push_back(mainRenderer);
    panelList.push_back(fpsGraph);

	for (vector<Panel*>::iterator it = panelList.begin(); it != panelList.end(); it++)
	{
		(*it)->Init();
	}

    OpenMainWindow = true;

	return true;
}

bool UiSystem::PreUpdate()
{
	PrepareFrame();
	return true;
}

void UiSystem::PrepareFrame()
{
	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}


bool UiSystem::Update(float dt)
{
    MainAppDockSpace(&OpenMainWindow);
	UpdatePanels();
   
	return true;
}

bool UiSystem::CleanUp()
{
    for (vector<Panel*>::iterator it = panelList.begin(); it != panelList.end(); it++)
    {
        (*it)->CleanUp();
    }

  //  LOG("Quitting ImGui subsystem");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
    io = nullptr;
    panelList.clear();
    camViewport = nullptr;
    mainRenderer = nullptr;
	return true;
}



void UiSystem::UpdatePanels()
{
	for (vector<Panel*>::iterator it = panelList.begin(); it != panelList.end(); it++)
    {
		(*it)->Update();
	}
}

void UiSystem::RenderUi()
{
	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
   

    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void UiSystem::MainAppDockSpace(bool* p_open)
{
    // In this example, we're embedding the Dockspace into an invisible parent window to make it more configurable.
    // We set ImGuiWindowFlags_NoDocking to make sure the parent isn't dockable into because this is handled by the Dockspace.
    //
    // ImGuiWindowFlags_MenuBar is to show a menu bar with config options. This isn't necessary to the functionality of a
    // Dockspace, but it is here to provide a way to change the configuration flags interactively.
    // You can remove the MenuBar flag if you don't want it in your app, but also remember to remove the code which actually
    // renders the menu bar, found at the end of this function.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiConfigFlags_DockingEnable;

    // Is the window in Fullscreen mode
    if (opt_fullscreen)
    {
        // If so, get the main viewport:
        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        // Set the parent window's position, size, and viewport to match that of the main viewport. This is so the parent window
        // completely covers the main viewport, giving it a "full-screen" feel.
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        // Set the parent window's styles to match that of the main viewport:
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f); // No corner rounding on the window
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f); // No border around the window

        // Manipulate the window flags to make it inaccessible to the user (no titlebar, resize/move, or navigation)
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        // The example is not in Fullscreen mode (the parent window can be dragged around and resized), disable the
        // ImGuiDockNodeFlags_PassthruCentralNode flag.
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so the parent window should not have its own background:
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // If the padding option is disabled, set the parent window's padding size to 0 to effectively hide said padding.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::Begin("Real Engie", p_open, window_flags);

    // Remove the padding configuration - we pushed it, now we pop it:
    if (!opt_padding)
        ImGui::PopStyleVar();

    // Pop the two style rules set in Fullscreen mode - the corner rounding and the border size.
    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Check if Docking is enabled:
    ImGuiIO& io = ImGui::GetIO();
    
    
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        // If it is, draw the Dockspace with the DockSpace() function.
        // The GetID() function is to give a unique identifier to the Dockspace - here, it's "MyDockSpace".
        ImGuiID dockspace_id = ImGui::GetID("Main window");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    else
    {
        cout << "Dockin disabled";
    }

    // This is to show the menu bar that will change the config settings at runtime.
    // If you copied this demo function into your own code and removed ImGuiWindowFlags_MenuBar at the top of the function,
    // you should remove the below if-statement as well.
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Windows"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
            //ImGui::MenuItem("Padding", NULL, &opt_padding);

            if (ImGui::MenuItem("Render Settings"))
            {
                mainRenderer->active = true;
                ImGui::SetWindowFocus(mainRenderer->name.GetString());
            }
            ImGui::MenuItem("Inspector");
            if(ImGui::MenuItem("FPS Graph"))
            {
                fpsGraph->active = true;
                ImGui::SetWindowFocus(fpsGraph->name.GetString());
            }
            ImGui::Separator();

 
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // End the parent window that contains the Dockspace:
    ImGui::End();
}

ImVec2 UiSystem::GetPanelSize(PanelID id)
{
    for (int i = 0; i < panelList.size(); i++)
    {
        if (panelList.at(i)->id == id)
        {
            return panelList.at(i)->GetPanelSize();
        }
    }
    cout << "Panel not found" << endl;
    return ImVec2(0, 0);
}
