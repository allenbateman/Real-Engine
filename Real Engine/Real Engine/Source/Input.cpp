#include "Application.h"
#include "Input.h"
#include "Window.h"

#include "Defs.h"
#include "Log.h"

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
	//glfwSetInputMode(app->window->window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetKeyCallback(app->window->window, KeyCallback);
	glfwSetWindowCloseCallback(app->window->window, windowCloseCallback);
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
