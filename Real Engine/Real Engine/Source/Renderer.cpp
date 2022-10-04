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

	/*glLineWidth(2.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(255, 0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(700.0f, 500.0f, 0.0f);
	glVertex3f(700.0f, 0.0f, 0.0f);
	glEnd();*/

	glLineWidth(2.0f);

	glBegin(GL_LINES);

	float d = 200.0f;

	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();



//	app->window->Swapbuffers();
	app->uiSystem->RenderUi();

	return true;
}

bool Renderer::CleanUp()
{
	return true;
}


