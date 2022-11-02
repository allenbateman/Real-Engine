#include "Renderer.h"
#include "Application.h"
#include "Window.h"
#include "UiSystem.h"
#include "EventSystem.h"
#include "Events.h"
#include "glmath.h" 
#include "Tag.h"



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


	app->eventSystem->SubscribeModule(this,PANEL_RESIZE);
	app->eventSystem->SubscribeModule(this, ON_PANEL_FOCUS);
	app->eventSystem->SubscribeModule(this, MOUSE_SCROLL);
	app->eventSystem->SubscribeModule(this, ON_FOV_CHANGE);
	return true;
}

bool Renderer::Start()
{
	const char *  vs = "../Output/Assets/Shaders/default.vertex";
	const char* fs = "../Output/Assets/Shaders/default.fragment";

	defaultShader = new Shader(vs, fs);

	currentCamera = app->entityComponentSystem.CreateEntity();
	app->entityComponentSystem.AddComponent(currentCamera, TagComponent{ "Camera" });
	app->entityComponentSystem.AddComponent(currentCamera, Transform{});
	app->entityComponentSystem.AddComponent(currentCamera, Camera());
	camera = app->entityComponentSystem.GetComponent<Camera>(currentCamera);
	camera.Start();

	OnResize(0, 0, app->window->GetWidth(), app->window->GetHeight());
	buffer.GenerateBuffer(app->window->GetWidth(), app->window->GetHeight());

	return true;
}

bool Renderer::PreUpdate()
{
	
	//clear window rendered buffer
	app->window->Clear();
	buffer.ClearBuffer();
	glMatrixMode(GL_MODELVIEW);

	return true;
}

bool Renderer::Update()
{

	return true;
}

bool Renderer::PostUpdate()
{	
	//calcualte view mtarix 

	camera = app->entityComponentSystem.GetComponent<Camera>(currentCamera);
	camera.CalculateViewMatrix();
	glLoadMatrixf(camera.GetViewMatrix());
	//bind renderer to the texture we want to render to (Frame buffer object)
	glBindFramebuffer(GL_FRAMEBUFFER, buffer.FBO);

	//Render every thing here -------------------------------------------
	//-----------------------
	//vec3 cubePos(0.0f, 0.0f, 0.0f);
	//DrawDirectCube(cubePos, 10.0f);

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

	//render Every Go
	for (auto& ent : entities)
	{
		auto& transform = app->entityComponentSystem.GetComponent<Transform>(ent);
		auto& mesh = app->entityComponentSystem.GetComponent<Mesh>(ent);
		auto& material = app->entityComponentSystem.GetComponent<Material>(ent);

		//attach shader 
		//set attributes for rendering the textures
		defaultShader->Use();
		float* projection = ProjectionMatrix.M;
		float* model;
		mat4x4 pos = translate(transform.position.x, transform.position.y, transform.position.z);
		mat4x4 rotationX = rotate(transform.rotation.x,transform.right);
		mat4x4 rotationY = rotate(transform.rotation.y,transform.up);
		mat4x4 rotationZ = rotate(transform.rotation.z,transform.forward);
		mat4x4 rotation = (rotationX * rotationY * rotationZ);
		mat4x4 size = scale(transform.scale.x, transform.scale.y, transform.scale.z);
		model = (pos * size * rotation).M;
		float* view = camera.GetViewMatrix();
		defaultShader->SetMat4("projection", projection);
		defaultShader->SetMat4("model", model);
		defaultShader->SetMat4("view", view);
		//render obj
		mesh.Draw(*defaultShader, material);

	}

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

static float aspect_ratio;

void Renderer::OnResize(int xPos, int yPos, int width, int height)
{
	//resize the texture 
	buffer.GenerateBuffer(width, height);

	glViewport(xPos, yPos, width, height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(camera.GetFieldOfView(), (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	aspect_ratio = width / height;
}

void Renderer::HandleEvent(Event* e)
{

	switch (e->type)
	{
	case PANEL_RESIZE:
	{
		OnPanelResize* Pr = dynamic_cast<OnPanelResize*>(e);
		if(Pr->id == eViewport)
			OnResize(0, 0, Pr->x, Pr->y);
		lastSize.x = Pr->x;
		lastSize.y = Pr->y;
	}
		break;
	case ON_PANEL_FOCUS:
	{
		OnPanelFocus* Pf = dynamic_cast<OnPanelFocus*>(e);
		if (Pf->id == eViewport)
		{
			auto& camera = app->entityComponentSystem.GetComponent<Camera>(currentCamera);
			camera.SetFocus(Pf->focused);
		}
	}
	break;
	case MOUSE_SCROLL:
	{
		OnResize(0, 0, lastSize.x, lastSize.y);
	}
	break;
	case ON_FOV_CHANGE:
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		ProjectionMatrix = perspective(camera.GetFieldOfView(), (float)lastSize.x / (float)lastSize.y, 0.125f, 512.0f);
		glLoadMatrixf(&ProjectionMatrix);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		aspect_ratio = lastSize.x / lastSize.y;
	}
	break;
	default:
		break;
	}
}

void Renderer::DrawDirectCube(vec3 position, float size)
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
	glVertex3f(x, y + size, z + size);

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
