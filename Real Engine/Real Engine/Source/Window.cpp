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

bool Window::Start()
{
	app->eventSystem->SubcribeModule(this, EventType::KEY_INPUT);
	app->eventSystem->SubcribeModule(this, EventType::MOUSE_HOLE_MOUSE);
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
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	int winWidth;
	int winHeight;
	//GetWindowSize(&width, &height);
	glViewport(-width/2, 0, width, height);
	
	//glLoadMatrixf(cam->GetOpenGLViewMatrix());
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
			//DemoEvent* dEvent = dynamic_cast<DemoEvent*>(singleEvent);
			//if (dEvent != nullptr)
			//{
			//	cout << dEvent->msg << endl;
			//	PrintTestEvent();
			//	return true;
			//}
		}break;
		case KEY_INPUT:
		{
			//KeyInput* keyboard = dynamic_cast<KeyInput*>(singleEvent);
			singleEvent->DisplayData();
		}
			break;
		default:
			break;
	}

	return false;
}

void Window::Test()
{
	cout << "I'm baby";
}

void Window::ResizeWindow(int newWidth, int newHeight)
{
	glfwSetWindowSize(window, newWidth, newHeight);
	glfwGetFramebufferSize(window, &width, &height);
	width = newWidth;
	height = newHeight;
}

void Window::PrintTestEvent()
{
	cout << "What do I do with this data?" << endl;
}
