#include "SceneManager.h"
#include"Tag.h"
#include "Events.h"
#include "EventSystem.h"


SceneManager::~SceneManager()
{
}

bool SceneManager::Awake()
{
	return true;
}

bool SceneManager::Start()
{

	Scene* sampleScene = CreateScene("Sample Scene");
	sampleScene->LoadGameObject("../Output/Assets/BakerHouse.fbx");

	currentScene = sampleScene;

	app->eventSystem->SubscribeModule(this, ON_GO_CREATION);

	return true;
}

bool SceneManager::Updte(float dt)
{

	return true;
}

bool SceneManager::PreUpdate()
{
	return true;
}

bool SceneManager::PostUpdate()
{
	return true;
}

bool SceneManager::CleanUp()
{
	return true;
}

void SceneManager::HandleEvent(Event* e)
{
	switch (e->type)
	{
	case ON_GO_CREATION:
	{
		OnGameObjectCreation* go = dynamic_cast<OnGameObjectCreation*>(e);

		switch (go->goType)
		{
		case gameObjectType::EMPTY: currentScene->CreateGameObject(go->goType); break;
		default:
			break;
		}
	}break;
	default:
		break;
	}
}

bool SceneManager::ChangeScene(Scene newScene)
{
	return false;
}

Scene* SceneManager::CreateScene(std::string name)
{
	if (sceneCount < MAX_SCENES)
	{

		cout << "Max scene reached";
		return nullptr;
	}
	else {
		Scene* newScene = new Scene(name.c_str());
		newScene->id = sceneCount;
		newScene->origin.GetComponent<TagComponent>() = name.c_str();

		sceneList.push_back(*newScene);
		sceneCount++;
		return newScene;
	}
}

Scene& SceneManager::GetScene(unsigned int id)
{
	for (auto& scene : sceneList)
	{
		if (scene.id == id)
			return scene;
	}
	cout << "Scene " << id  << " not found!";
}

Scene& SceneManager::GetScene(std::string name)
{
	for (auto& scene : sceneList)
	{
		if (scene.name == name)
			return scene;
	}
	cout << "Scene "<<name << " not found!";
}
