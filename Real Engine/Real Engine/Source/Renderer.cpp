#include "Renderer.h"
#include "Application.h"
#include "Window.h"
#include "UiSystem.h"

Renderer::Renderer(bool isActive) : Module(isActive)
{

}

Renderer::~Renderer()
{
}

bool Renderer::Awake()
{
	return true;
}

bool Renderer::Start()
{
	return true;
}

bool Renderer::PreUpdate()
{
	//clear window rendered buffer
	app->window->Clear();
	

	return true;
}

bool Renderer::Update()
{

	return true;
}

bool Renderer::PostUpdate()
{
//	app->window->Swapbuffers();
	app->uiSystem->RenderUi();

	return true;
}

bool Renderer::CleanUp()
{
	return true;
}
