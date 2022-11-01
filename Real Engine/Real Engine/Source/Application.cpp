#include "Application.h"

//include all modules 
#include "Window.h"
#include "Input.h"
#include "EventSystem.h"
#include "UiSystem.h"
#include "Renderer.h"
#include "CameraController.h"
#include "SceneManager.h"
#include "Tag.h"

//include All components


Application::Application(int argc, char* args[]) : argc(argc), args(args)
{
	appName.Create("Real Engine");
	frameCount = 0;

	entityComponentSystem.Init();

	window = entityComponentSystem.RegisterSystem<Window>();
	input = entityComponentSystem.RegisterSystem<Input>();
	eventSystem = entityComponentSystem.RegisterSystem<EventSystem>();
	sceneManager = entityComponentSystem.RegisterSystem<SceneManager>();
	{
		Signature signature;
		signature.set(entityComponentSystem.GetComponentType<TagComponent>());
		entityComponentSystem.SetSystemSignature<SceneManager>(signature);
	}
	uiSystem = entityComponentSystem.RegisterSystem<UiSystem>();
	{
		Signature signature;
		signature.set(entityComponentSystem.GetComponentType<TagComponent>());
		entityComponentSystem.SetSystemSignature<UiSystem>(signature);
	}

	cameraController = entityComponentSystem.RegisterSystem<CameraController>();
	{
		Signature signature;
		signature.set(entityComponentSystem.GetComponentType<TagComponent>());
		signature.set(entityComponentSystem.GetComponentType<Transform>());
		signature.set(entityComponentSystem.GetComponentType<Camera>());
		entityComponentSystem.SetSystemSignature<CameraController>(signature);
	}

	renderer = entityComponentSystem.RegisterSystem<Renderer>();
	{
		Signature signature;
		signature.set(entityComponentSystem.GetComponentType<TagComponent>());
		signature.set(entityComponentSystem.GetComponentType<Transform>());
		signature.set(entityComponentSystem.GetComponentType<Mesh>());
		signature.set(entityComponentSystem.GetComponentType<Material>());
		entityComponentSystem.SetSystemSignature<Renderer>(signature);
	}
	//add modules order is important, cleanup is reverse order
	modules.push_back(window);
	modules.push_back(input);
	modules.push_back(cameraController);
	modules.push_back(sceneManager);
	//last
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
	
	for (list<shared_ptr<Module>>::iterator current = modules.begin(); current != modules.end(); current++)
	{
		(*current)->Awake();
	}

	timer.Start();
	return ret;
}

bool Application::Start()
{
	bool ret = true;

	//load house  TODO move to scene
	objLoader.LoadObject("./Output/Assets/BakerHouse.fbx");

	for (list<shared_ptr<Module>>::iterator current = modules.begin(); current != modules.end(); current++)
	{
		ret = (*current)->Start();
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

	if (input->GetKey(GLFW_KEY_P) == KEY_DOWN)
	{
		entityComponentSystem.DebugComponentList<TagComponent>();
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (list<shared_ptr<Module>>::iterator current = modules.begin(); current != modules.end(); current++)
	{
		(*current)->CleanUp();
	}

	return ret;
}

void Application::AddModule(shared_ptr<Module> module)
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

list<shared_ptr<Module>>* Application::GetModuleList()
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

	for (list<shared_ptr<Module>>::iterator current = modules.begin(); current != modules.end(); current++)
	{
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


	for (list<shared_ptr<Module>>::iterator current = modules.begin(); current != modules.end(); current++)
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

	for (list<shared_ptr<Module>>::iterator current = modules.begin(); current != modules.end(); current++)
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
