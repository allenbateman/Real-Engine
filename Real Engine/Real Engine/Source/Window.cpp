#include "Window.h"
#include "Application.h"
#include "EventSystem.h"
#include "Events.h"




Window::Window(bool isActive) : Module(isActive)
{
	window = NULL;
	name.Create("Window");
}

// Destructor
Window::~Window()
{
}

// Called before render is available
bool Window::Awake()
{
	bool ret = true;

	LOG("Init glfw window ");


	if (!glfwInit())
	{
		ret = false;
		LOG("GLFW could not be loaded");
	}

	
	window = glfwCreateWindow(800, 600,"Real Engine", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		ret = false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	std::cout << glGetString(GL_VERSION) << std::endl;
	glfwGetFramebufferSize(window, &width, &height);

	glewInit();

	return ret;
}

bool Window::Start()
{
	app->eventSystem->SubscribeModule(this, EventType::KEY_INPUT);
	app->eventSystem->SubscribeModule(this, EventType::MOUSE_HOLE_MOUSE);
	return true;
}

// Called before quitting
bool Window::CleanUp()
{
	LOG("Destroying window and quitting all GLFW systems");

	glfwDestroyWindow(window);
	glfwTerminate();
	return true;
}

void Window::Swapbuffers()
{
	glfwSwapBuffers(window);
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Set new window title
void Window::SetTitle(const char* new_title)
{
	name = new_title;
}

void Window::GetWindowSize(unsigned int& width, unsigned int& height) const
{
	width = this->width;
	height = this->height;
}

unsigned int Window::GetScale() const
{
	return scale;
}

// Retrieve window Width
int Window::GetWidth() const
{
	return (int)width;
}

// Retrieve window height
int Window::GetHeight() const
{
	return (int)height;
}

void Window::SetFullScreen(bool fullScreen)
{

	this->fullScreen = fullScreen;
}

bool Window::GetFullScreen()
{
	return fullScreen;
}

bool Window::HandleEvent( Event* singleEvent) 
{

	switch (singleEvent->type)
	{
		case NONE:
		{
		}break;
		case KEY_INPUT:
			singleEvent->DisplayData();
			break;
		case MOUSE_HOLE_MOUSE:
			singleEvent->DisplayData();
			break;
		default:
			break;
	}

	return false;
}

void Window::ResizeWindow(int newWidth, int newHeight)
{
	
	glfwSetWindowSize(window, newWidth, newHeight);
	glfwGetFramebufferSize(window, &width, &height);
	width = newWidth;
	height = newHeight;
}
