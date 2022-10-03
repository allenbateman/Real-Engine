#include "Window.h"
#include "Application.h"
#include "Defs.h"
#include "Log.h"
#include <string>
#include <iostream>



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

	glfwGetFramebufferSize(window, &width, &height);

	if (!window)
	{
		glfwTerminate();
		ret = false;
	}

	glfwMakeContextCurrent(window);

	subscribedEvents.push_back(NONE);

	return ret;
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
	glClear(GL_COLOR_BUFFER_BIT);
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

bool Window::HandleEvent(Event* singleEvent)
{

	switch (singleEvent->type)
	{
		case NONE:
		{
			DemoEvent* dEvent = dynamic_cast<DemoEvent*>(singleEvent);
			if (dEvent != nullptr)
			{
				cout << dEvent->msg << endl;
				PrintTestEvent();
				return true;
			}
		}break;
		 
		default:
			break;
	}

	return false;
}

void Window::PrintTestEvent()
{
	cout << "What do I do with this data?" << endl;
}
