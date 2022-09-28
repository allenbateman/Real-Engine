


#include "Application.h"
#include "Input.h"
#include "Window.h"
#include "EventSystem.h"


#include "Defs.h"
#include "Log.h"


#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_glfw.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"


bool Input::windowEvents[WE_COUNT];
KeyState Input::keyboard[sizeof(KeyState) * MAX_KEYS];

Input::Input(bool isActive) : Module(isActive)
{
	name.Create("Input");

	//keyboard = new KeyState[MAX_KEYS];
	//memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
	memset(mouseButtons, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);

	
}

// Destructor
Input::~Input()
{
	//delete[] Input::keyboard;
}

// Called before render is available
bool Input::Awake()
{
	LOG("Init SDL input event system");




	bool ret = true;
	return ret;
}

// Called before the first frame
bool Input::Start()
{

	//bind input callback with glfw
	glfwSetInputMode(app->window->window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetKeyCallback(app->window->window, KeyCallback);
	glfwSetWindowCloseCallback(app->window->window, windowCloseCallback);


	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(app->window->window, true);
	ImGui_ImplOpenGL3_Init("#version 410");



	return true;
}

// Called each loop iteration
bool Input::PreUpdate()
{
	for (int i = 0; i < MAX_KEYS; i++)
	{
		if (keyboard[i] == KEY_UP)
		{
			keyboard[i] = KEY_IDLE;
		}
	}
	if (GetKey(GLFW_KEY_ESCAPE) == KEY_REPEAT)
	{
		windowCloseCallback(app->window->window);
	}

//------------------------------------


	if (GetKey(GLFW_KEY_SPACE) == KEY_DOWN)
	{
		event1 = new DemoEvent();
		app->eventSystem->AddEvent(event1);
	}


//------------------------------------
	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// render your GUI
	ImGui::Begin("Demo window");
	ImGui::Button("Hello!");
	ImGui::End();

	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	int display_w, display_h;
	glfwGetFramebufferSize(app->window->window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glfwSwapBuffers(app->window->window);

//------------------------------------




	return true;
}

int Input:: GetKey(int key)
{
	return keyboard[key];
}

// Called before quitting
bool Input::CleanUp()
{
	LOG("Quitting Input event subsystem");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	return true;
}



bool Input::GetWindowEvent(EventWindow ev)
{
	return windowEvents[ev];
}

void Input::GetMousePosition(int& x, int& y)
{
	x = mouseX;
	y = mouseY;
}

void Input::GetMouseMotion(int& x, int& y)
{
	x = mouseMotionX;
	y = mouseMotionY;
}


void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
		switch (action)
		{
		case GLFW_PRESS:
			keyboard[key] = KeyState::KEY_DOWN;
			break;
		case GLFW_REPEAT:
			keyboard[key] = KeyState::KEY_REPEAT;
			break;
		case GLFW_RELEASE:
			keyboard[key] = KeyState::KEY_UP;
			break;
		default:
			keyboard[key] = KeyState::KEY_IDLE;
			break;
		}	
}

void Input::windowCloseCallback(GLFWwindow* window)
{
	//check if we want to close the window, save project.... etc
	windowEvents[WE_QUIT] = true;
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}
