#include "Renderer.h"
#include "Application.h"
#include "Window.h"
#include "UiSystem.h"
#include "EventSystem.h"
#include "Events.h"
#include "Camera.h"


Renderer::Renderer(bool isActive) : Module(isActive)
{

}

Renderer::~Renderer()
{
}

bool Renderer::Awake()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearDepth(1.0f);

	glClearColor(0.f, 0.f, 0.f, 1.f);

	GLfloat MaterialAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

	GLfloat MaterialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	OnResize(0,0,app->window->GetWidth(), app->window->GetHeight());

	buffer.GenerateBuffer(app->window->GetWidth(), app->window->GetHeight());

	app->eventSystem->SubcribeModule(this,PANEL_RESIZE);

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
	buffer.ClearBuffer();
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(app->camera->GetViewMatrix());

	return true;
}

bool Renderer::Update()
{



	return true;
}

bool Renderer::PostUpdate()
{	
	//bind renderer to the texture we want to render to 
	glBindFramebuffer(GL_FRAMEBUFFER, buffer.FBO);

	//Render every thing here -------------------------------------------
	vec3 cubePos(0.0f, 0.0f, 0.0f);
	DrawDirectCube(cubePos, 10.0f);

	glLineWidth(2.0f);

	glBegin(GL_LINES);
	glColor3f(255, 255, 255);

	float d = 200.0f;

	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();
	//Stop render  -------------------------------------------

	//bind to the default renderer to render everything
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	app->uiSystem->RenderUi();
	app->window->Swapbuffers();

	return true;
}

bool Renderer::CleanUp()
{
	return true;
}

void Renderer::OnResize(int xPos, int yPos, int width, int height)
{
	//resize the texture 
	buffer.GenerateBuffer(width, height);

	glViewport(xPos, yPos, width, height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Renderer:: DrawDirectCube(vec3 position, float size)
{

	float x = position.x;
	float y = position.y;
	float z = position.z;

	glLineWidth(1.0f);
	glBegin(GL_TRIANGLES);
	
	
	//Front
	glColor3f(255, 0, 0);

	glVertex3f(x + size, y + size, z);
	glVertex3f(x, y + size, z);
	glVertex3f(x, y, z);

	glVertex3f(x, y, z);
	glVertex3f(x + size, y, z);
	glVertex3f(x + size, y + size, z);



	//Right
	glColor3f(255, 255, 0);

	glVertex3f(x + size, y + size, z);
	glVertex3f(x + size, y, z);
	glVertex3f(x + size, y, z + size);

	glVertex3f(x + size, y, z + size);
	glVertex3f(x + size, y + size, z + size);
	glVertex3f(x + size, y + size, z);

	//Top
	glColor3f(0, 255, 255);

	glVertex3f(x + size, y + size, z);
	glVertex3f(x + size, y + size, z + size);
	glVertex3f(x, y + size, z + size);

	glVertex3f(x, y + size, z + size);
	glVertex3f(x, y + size, z);
	glVertex3f(x + size, y + size, z);

	//Back
	glColor3f(0, 0, 255);

	glVertex3f(x + size, y + size, z + size);
	glVertex3f(x, y + size, z + size);
	glVertex3f(x, y, z + size);

	
	glVertex3f(x, y, z + size);
	glVertex3f(x + size, y, z + size);
	glVertex3f(x, y + size, z + size);

	//Left
	glColor3f(100, 255, 255);

	glVertex3f(x, y + size, z + size);
	glVertex3f(x, y + size, z);
	glVertex3f(x, y, z);

	glVertex3f(x, y, z);
	glVertex3f(x, y, z + size);
	glVertex3f(x , y + size, z + size);

	//Bottom
	glColor3f(100, 100, 255);

	glVertex3f(x + size, y, z + size);
	glVertex3f(x, y, z + size);
	glVertex3f(x, y, z);

	glVertex3f(x, y, z);
	glVertex3f(x + size, y, z);
	glVertex3f(x + size, y, z + size);



	glEnd();
}

bool Renderer::HandleEvent(Event* e)
{

	switch (e->type)
	{
	case PANEL_RESIZE:
	{
		OnPanelResize* Pr = dynamic_cast<OnPanelResize*>(e);
		if(Pr->id == eViewport)
			OnResize(0, 0, Pr->x, Pr->y);
	}
		break;
	default:
		break;
	}
	return false;
}
