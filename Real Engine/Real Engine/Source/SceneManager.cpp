#include "SceneManager.h"


SceneManager::~SceneManager()
{
}

bool SceneManager::Awake()
{
	return true;
}

bool SceneManager::Start()
{

	sampleScene = new Scene();
	sampleScene->Start();
	sceneList.push_back(*sampleScene);

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
	for (auto& scene : sceneList)
	{
		scene.CleanUp();
	}
	return true;
}

void SceneManager::HandleEvent(Event* e)
{
}

bool SceneManager::ChangeScene(Scene newScene)
{
	return false;
}
