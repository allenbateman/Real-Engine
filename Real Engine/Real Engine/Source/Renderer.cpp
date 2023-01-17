#include "Renderer.h"

#include "glmath.h"
#include "Application.h"

#include "Window.h"
#include "UiSystem.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EventSystem.h"
#include "Events.h"
#include "Mesh.h" 
#include "Material.h" 
#include "Tag.h"
#include "GL/glew.h"
#include "EditorComponent.h"



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
	glEnable(GL_ALPHA_TEST);

	app->eventSystem->SubscribeModule(this, PANEL_RESIZE);
	app->eventSystem->SubscribeModule(this, ON_PANEL_FOCUS);
	app->eventSystem->SubscribeModule(this, MOUSE_SCROLL);
	app->eventSystem->SubscribeModule(this, ON_FOV_CHANGE);
	
	return true;
}

bool Renderer::Start()
{
	editorCam = app->entityComponentSystem.CreateEntity();
	app->entityComponentSystem.AddComponent(editorCam, TagComponent{ "Camera" });
	app->entityComponentSystem.AddComponent(editorCam, Transform{});
	app->entityComponentSystem.AddComponent(editorCam, Camera());
	app->entityComponentSystem.AddComponent(editorCam, EditorComponent());
	Camera* editorCamera = &app->entityComponentSystem.GetComponent<Camera>(editorCam);
	if (!editorCamera->Start())
		Debug::Error("Shader compile error");

	editor.camera = editorCamera;
	editor.type = eEditor;
	renderers.push_back(&editor);
	game.type = eGame;
	renderers.push_back(&game);

	for (vector<RenderSpace*>::iterator item = renderers.begin(); item != renderers.end(); item++)
	{
		(*item)->buffer.GenerateBuffer(app->window->GetWidth(), app->window->GetHeight());
	}
	return true;
}

bool Renderer::PreUpdate()
{
	
	//clear window rendered buffer
	for (vector<RenderSpace*>::iterator item = renderers.begin(); item != renderers.end(); item++)
	{
		(*item)->buffer.ClearBuffer();
	}

	app->window->Clear();
	glMatrixMode(GL_MODELVIEW);

	return true;
}

bool Renderer::Update(float dt)
{
	return true;
}

bool Renderer::PostUpdate()
{	
	//calcualte view mtarix 
	for (vector<RenderSpace*>::iterator item = renderers.begin(); item != renderers.end(); item++)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		glLoadMatrixf(&(*item)->ProjectionMatrix);

		glMatrixMode(GL_MODELVIEW);

		(*item)->camera->CalculateViewMatrix();
		glLoadMatrixf((*item)->camera->GetViewMatrix());
		//bind renderer to the texture we want to render to (Frame buffer object)
		glBindFramebuffer(GL_FRAMEBUFFER, (*item)->buffer.FBO);

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
		
		//Set Camera shader to render 
		float* projection = (*item)->ProjectionMatrix.M;
		float* view = (*item)->camera->GetViewMatrix();
		float* model;
		//render Every Go

		for (auto& ent : entities)
		{
			auto& transform = app->entityComponentSystem.GetComponent<Transform>(ent);
			auto& mesh = app->entityComponentSystem.GetComponent<Mesh>(ent);
			auto& material = app->entityComponentSystem.GetComponent<Material>(ent);
			if (material.resource == nullptr) continue;
			auto& shader = material.resource->shader;
			shader->Use();
			//attach shader 
			//set attributes for rendering the textures
			mat4x4 pos = translate(transform.position.x, transform.position.y, transform.position.z);
			mat4x4 rotationX = rotate(transform.eulerAngles.x, transform.right);
			mat4x4 rotationY = rotate(transform.eulerAngles.y, transform.up);
			mat4x4 rotationZ = rotate(transform.eulerAngles.z, transform.forward);
			mat4x4 rotation = (rotationX * rotationY * rotationZ);
			mat4x4 size = scale(transform.scale.x, transform.scale.y, transform.scale.z);
			model = (pos * size * rotation).M;
			shader->SetMat4("projection", projection);
			shader->SetMat4("model", model);
			shader->SetMat4("view", view);
			//render obj
			mesh.resource->Draw(shader, material.resource);
 
			shader->StopUse();
		}		
		//Stop render  -------------------------------------------

		//bind to the default renderer to render everything
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	app->window->Swapbuffers();
	app->uiSystem->RenderUi();
	return true;
}

bool Renderer::CleanUp()
{
	return true;
}

void Renderer::HandleEvent(Event* e)
{

	switch (e->type)
	{
	case PANEL_RESIZE:
	{
		OnPanelResize* Pr = dynamic_cast<OnPanelResize*>(e);
		switch (Pr->id)
		{
		case eViewport:
			editor.OnResize(0, 0, Pr->x, Pr->y);
			break;
		case eGameViewport:
			game.OnResize(0, 0, Pr->x, Pr->y);
			break;
		}	
	}
		break;
	case ON_PANEL_FOCUS:
	{
		OnPanelFocus* Pf = dynamic_cast<OnPanelFocus*>(e);
		switch (Pf->id)
		{
		case eViewport:
			editor.camera->SetFocus(Pf->focused);
			break;
		case eGameViewport:
			game.camera->SetFocus(Pf->focused);
			break;
		}
	}
	break;
	case MOUSE_SCROLL:
	{
		editor.OnFovChange();
	}
	break;
	case ON_FOV_CHANGE:
	{
		//game.OnFovChange();
		//editor.OnFovChange();
	}
	break;
	default:
		break;
	}
}

void Renderer::SetGameSpaceCamera(Camera* camera, RenderSpaceType type)
{
	game.camera = camera;		
	game.type = eGame;
	game.OnResize(0, 0, app->window->GetWidth(), app->window->GetHeight());
}