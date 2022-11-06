#include "Scene.h"
void Scene::Init()
{
	
}

void Scene::Enable()
{
}

void Scene::Disable()
{
}

void Scene::CreateGameObject()
{
	GameObject goToAdd;
	gameObejects.push_back(goToAdd);
}

void Scene::LoadGameObject(const std::string file_path)
{
	std::vector<GameObject*> obj = objLoader.LoadObject(file_path);
	gameObejects.push_back(*obj.back());
	//for (auto ob : obj)
	//	gameObejects.push_back(*ob);
}
