#include "Window.h"
#include "Application.h"
#include "Defs.h"
#include "Log.h"

//#include "Defs.h"
//#include "Log.h"

Window::Window(bool isActive) : Module(isActive)
{
	window = NULL;
	screenSurface = NULL;
	name = "window";
}

// Destructor
Window::~Window()
{
}

// Called before render is available
bool Window::Awake()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	return ret;
}

// Called before quitting
bool Window::CleanUp()
{
	LOG("Destroying window and quitting all SDL systems");

	//// Destroy window
	//if (window != NULL)
	//{
	//	SDL_DestroyWindow(window);
	//}

	//// Quit SDL subsystems
	//SDL_Quit();
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
