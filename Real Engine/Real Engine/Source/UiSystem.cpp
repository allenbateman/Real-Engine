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

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(app->window->window, true);
	ImGui_ImplOpenGL3_Init("#version 410");

	camViewport = new Viewport(true);
	panelList.push_back(camViewport);

	for (vector<Panel*>::iterator it = panelList.begin(); it != panelList.end(); it++)
	{
		(*it)->Init();
	}

	return true;
}

bool UiSystem::PreUpdate()
{
	PrepareFrame();
	return true;
}

bool UiSystem::Update(float dt)
{
	UpdatePanels();
	return true;
}

bool UiSystem::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	return true;
}

void UiSystem::PrepareFrame()
{
	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
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
}
