#include "Renderer.h"
#include "Application.h"
#include "Window.h"
#include "UiSystem.h"
#include "EventSystem.h"
#include "Events.h"
#include "Camera.h"
#include "glmath.h" 




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

	app->eventSystem->SubscribeModule(this,PANEL_RESIZE);
	app->eventSystem->SubscribeModule(this, ON_PANEL_FOCUS);
	app->eventSystem->SubscribeModule(this, MOUSE_SCROLL);
	return true;
}

bool Renderer::Start()
{
	//objLoader.LoadObject("../Output/Assets/warrior.FBX");
	objLoader.LoadObject("../Output/Assets/BakerHouse.fbx");
	const char *  vs = "../Real Engine/Source/default.vertex";
	const char* fs = "../Real Engine/Source/default.fragment";

	defaultShader = new Shader(vs, fs);
	
	maxFieldOfView = 100.0f;
	fieldOfView = 65.0f;
	minFieldOfView = 50.0f;

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
	//-----------------------
	vec3 cubePos(0.0f, 0.0f, 0.0f);
	DrawDirectCube(cubePos, 10.0f);

	glLineWidth(2.0f);

	glBegin(GL_LINES);
	glColor3f(150, 150, 150);

	float d = 200.0f;

	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();

	//render house--------------------------------------------
	//attach shader 
	//set attributes for rendering the textures
	defaultShader->Use();
	float* projection = ProjectionMatrix.M;

	float timeValue = glfwGetTime();
	float resize = sin(timeValue) / 2.0f + 5.0f;//rescale xD
	float* model;
	mat4x4 pos = translate(-10, 0, 0);
	mat4x4 size = scale(resize, resize, resize);
	model = (pos * size).M;
	float* view = app->camera->GetViewMatrix();
	defaultShader->SetMat4("projection", projection);
	defaultShader->SetMat4("model", model);
	defaultShader->SetMat4("view", view);
	
	//render obj
	for (int i = 0; i < objLoader.meshes.size(); i++)
		objLoader.meshes[i].Draw(*defaultShader, objLoader.materials[0]);

	//detach the shader to default so it doesnt affect other render process
	defaultShader->StopUse();

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
	ProjectionMatrix = perspective(this->fieldOfView, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void Renderer::ChangeFieldOfView(float fieldOfView, int width, int height)
{

	float fieldOfViewValue = this->fieldOfView - fieldOfView;

	if (minFieldOfView > fieldOfViewValue || fieldOfViewValue > maxFieldOfView) return;
	
	this->fieldOfView -= fieldOfView;
	
	//OnResize(0, 0, width, height);
	buffer.GenerateBuffer(width, height);

	glViewport(0.0f, 0.0f, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(this->fieldOfView, width / height, 0.125f, 512.0f);
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
	case ON_PANEL_FOCUS:
	{
		OnPanelFocus* Pf = dynamic_cast<OnPanelFocus*>(e);
		if (Pf->id == eViewport)
		{
			
			onFocus = Pf->focused;
		}
	}
	break;
	case MOUSE_SCROLL:
	{
		if (!onFocus)
			break;
		MouseScroll* ms = dynamic_cast<MouseScroll*>(e);

		ChangeFieldOfView(ms->dy, app->window->GetWidth(), app->window->GetHeight());
		ms->DisplayData();
		

	}
	break;
	default:
		break;
	}
	return false;
}
