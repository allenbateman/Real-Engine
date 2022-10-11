
#include "Application.h"
#include "Input.h"
#include "Window.h"
#include "EventSystem.h"


#include "Defs.h"
#include "Log.h"

bool Input::windowEvents[WE_COUNT];
KeyState Input::keyboard[sizeof(KeyState) * MAX_KEYS];
KeyState Input::mouseButtons[sizeof(KeyState) * NUM_MOUSE_BUTTONS];

int Input::mouseX = 0;
int Input::mouseY = 0;

Input::Input(bool isActive) : Module(isActive)
{
	name.Create("Input");
}

// Destructor
Input::~Input()
{

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
	glfwSetMouseButtonCallback(app->window->window, MouseButtonCallback);
	glfwSetCursorPosCallback(app->window->window, MousePositionCallback);
	glfwSetWindowCloseCallback(app->window->window, windowCloseCallback);


	return true;
}

// Called each loop iteration
bool Input::PreUpdate()
{
	//get all events occurred in the window
	glfwPollEvents();

	//Set keys state
	for (int i = 0; i < MAX_KEYS; i++)
	{
		if (keyboard[i] == KEY_UP)
		{
			keyboard[i] = KEY_IDLE;
		}
	}
	for (int i = 0; i < NUM_MOUSE_BUTTONS; i++)
	{
		if (mouseButtons[i] == KEY_UP)
		{
			mouseButtons[i] = KEY_IDLE;
		}
	}

	if (GetKey(GLFW_KEY_ESCAPE) == KEY_REPEAT)
	{
		windowCloseCallback(app->window->window);
	}

//------------------------------------

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
		Input* input = app->input;
		input->RetriveKeyCallBack(key, scancode, action, mods);
}

void Input::RetriveKeyCallBack(int key, int scancode, int action, int mods)
{
	keyEvent.key = key;
	keyEvent.scancode = scancode;
	keyEvent.keyState = keyboard[key];
	app->eventSystem->PostEvent(&keyEvent);
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		mouseButtons[button] = KeyState::KEY_DOWN;
		break;
	case GLFW_REPEAT:
		mouseButtons[button] = KeyState::KEY_REPEAT;
		break;
	case GLFW_RELEASE:
		mouseButtons[button] = KeyState::KEY_UP;
		break;
	default:
		mouseButtons[button] = KeyState::KEY_IDLE;
		break;
	}
	Input* input = app->input;
	input->RetriveMouseButtonCallBack(button, action, mods);
}

void Input::RetriveMouseButtonCallBack(int button, int action, int mods)
{
	mouseButtonEvent.key = button;
	mouseButtonEvent.keyState = mouseButtons[button];
	app->eventSystem->PostEvent(&mouseButtonEvent);
}

void Input::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	mouseX = xpos;
	mouseY = ypos;
	Input* input = app->input;
	input->RetriveMousePositionCallBack(xpos,ypos);
}

void Input::RetriveMousePositionCallBack(double xpos, double ypos)
{
	mousePositionEvent.x = xpos;
	mousePositionEvent.y = ypos;
	app->eventSystem->PostEvent(&mousePositionEvent);
}

void Input::windowCloseCallback(GLFWwindow* window)
{
	//check if we want to close the window, save project.... etc
	windowEvents[WE_QUIT] = true;
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}
