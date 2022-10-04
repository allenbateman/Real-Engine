#include "Application.h"

//include all modules 
#include "Window.h"
#include "Input.h"
#include "EventSystem.h"
#include "UiSystem.h"
#include "Renderer.h"

Application::Application(int argc, char* args[]) : argc(argc), args(args)
{
	appName.Create("Real Engine");
	frames = 0;

	window = new Window(true);
	input = new Input(true);
	eventSystem = new EventSystem(true);
	uiSystem = new UiSystem(true);
	renderer = new Renderer(true);

	//add modules order is important, cleanup is reverse order
	modules.push_back(window);
	modules.push_back(input);


	//last
	// 
	//renderer
	modules.push_back(uiSystem);
	modules.push_back(eventSystem);
	modules.push_back(renderer);

}

Application::~Application()
{
	modules.clear();
}

bool Application::Awake()
{
	bool ret = true;
	
	for (list<Module*>::iterator current = modules.begin(); current != modules.end(); current++)
	{
		(*current)->Awake();
	}

	return ret;
}

bool Application::Start()
{
	bool ret = true;

	for (list<Module*>::iterator current = modules.begin(); current != modules.end(); current++)
	{
		(*current)->Start();
	}

	return ret;
}

bool Application::Update()
{
	bool ret = true;

	PrepareUpdate();

	if (input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if (ret == true)
		ret = PreUpdate();

	if (ret == true)
		ret = DoUpdate();

	if (ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (list<Module*>::iterator current = modules.begin(); current != modules.end(); current++)
	{
		(*current)->CleanUp();
	}

	return ret;
}

void Application::AddModule(Module* module)
{
	module->Init();
	modules.push_back(module);
}

int Application::GetArgc() const
{
	return 0;
}

const char* Application::GetArgv(int index) const
{
	return nullptr;
}

const char* Application::GetTitle() const
{
	return nullptr;
}

const char* Application::GetOrganization() const
{
	return nullptr;
}

void Application::LoadGameRequest()
{
}

void Application::SaveGameRequest() const
{
}

list<Module*>* Application::GetModuleList() 
{
	return &modules;
}

void Application::BroadcastEvents()
{
	eventSystem->BroadcastEvents();
}

void Application::PrepareUpdate()
{
	BroadcastEvents();
}

void Application::FinishUpdate()
{
}

bool Application::PreUpdate()
{
	bool ret = true;

	for (list<Module*>::iterator current = modules.begin(); current != modules.end(); current++)
	{
	//  set Debug mode
	//	if (input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	//		current->data->DEBUG = !item->data->DEBUG;

		if ((*current)->active == false)
			continue;

		(*current)->PreUpdate();
	}

	return ret;
}

bool Application::DoUpdate()
{
	bool ret = true;
	//calculate frame rate


	for (list<Module*>::iterator current = modules.begin(); current != modules.end(); current++)
	{
		if ((*current)->active == false)
			continue;

		(*current)->Update(dt);
	}

	return ret;
}

bool Application::PostUpdate()
{
	bool ret = true;

	for (list<Module*>::iterator current = modules.begin(); current != modules.end(); current++)
	{
		if ((*current)->active == false)
			continue;

		(*current)->PostUpdate();
	}

	return ret;
}

bool Application::LoadGame()
{
	return false;
}

bool Application::SaveGame() const
{
	return false;
}
