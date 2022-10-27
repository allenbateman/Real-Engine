
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

int Input::mouseDX = 0;
int Input::mouseDY = 0;

int Input::mouseScrollX = 0;
int Input::mouseScrollY = 0;

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
	glfwSetScrollCallback(app->window->window, MouseScrollCallback);


	subscribedEvents.push_back(EventType::KEY_INPUT);


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
	keyEvent.keys = keyboard;
	app->eventSystem->PostEvent(&keyEvent);

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
		shared_ptr<Input> input = app->input;
		input->RetriveKeyCallBack(key, scancode, action, mods);
}

void Input::RetriveKeyCallBack(int key, int scancode, int action, int mods)
{
	/*keyEvent.key = key;
	keyEvent.scancode = scancode;
	keyEvent.keyState = keyboard[key];*/
	/*keyEvent.keys = keyboard;
	app->eventSystem->PostEvent(&keyEvent);*/
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
	shared_ptr<Input>  input = app->input;
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
	if(mouseX != 0) mouseDX = xpos - mouseX;
	if(mouseY != 0) mouseDY = ypos - mouseY;
	mouseX = xpos;
	mouseY = ypos;
	shared_ptr<Input>  input = app->input;
	input->RetriveMousePositionCallBack(xpos,ypos, mouseDX, mouseDY);
}

void Input::RetriveMousePositionCallBack(double xpos, double ypos, double dx, double dy)
{
	mousePositionEvent.x = xpos;
	mousePositionEvent.y = ypos;
	mousePositionEvent.dx = dx;
	mousePositionEvent.dy = dy;
	app->eventSystem->PostEvent(&mousePositionEvent);
}

void Input::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	mouseScrollX = xOffset;
	mouseScrollY = yOffset;
	shared_ptr<Input>  input = app->input;
	input->RetrieveMouseScrollCallback(mouseScrollX, mouseScrollY);
}
void Input::RetrieveMouseScrollCallback(double xOffset, double yOffset)
{
	mouseScrollEvent.dx = xOffset;
	mouseScrollEvent.dy = yOffset;
	app->eventSystem->PostEvent(&mouseScrollEvent);
}

void Input::windowCloseCallback(GLFWwindow* window)
{
	//check if we want to close the window, save project.... etc
	windowEvents[WE_QUIT] = true;
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}
