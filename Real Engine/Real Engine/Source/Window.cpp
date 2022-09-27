#include "Window.h"
#include "Application.h"
#include "Defs.h"
#include "Log.h"

#include <glew.h>
#include <gl/gl.h>
#include "glfw3.h"

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

	return ret;
}

bool Window::PreUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT);

	return true;
}

bool Window::PostUpdate()
{
	glfwSwapBuffers(window);

	glfwPollEvents();
	
	return true;
}

// Called before quitting
bool Window::CleanUp()
{
	LOG("Destroying window and quitting all GLFW systems");
	glfwTerminate();
	return true;
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
