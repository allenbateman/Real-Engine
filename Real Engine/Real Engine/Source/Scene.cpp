#include "Scene.h"
Scene::Scene()
{
}
Scene::Scene(const char* name)
{
	this->name = name;
	origin.name = name;
}
Scene::~Scene()
{
}
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

	GameObject* go = obj.back();
	origin.GetComponent<Transform>().childs.push_back(&go->GetComponent<Transform>());
	go->GetComponent<Transform>().parent = &origin.GetComponent<Transform>();
	gameObejects.push_back(*go);
	//for (auto ob : obj)
	//	gameObejects.push_back(*ob);
}

void Scene::RemoveEntity(Entity id)
{
	for (auto& go : gameObejects)
	{
		if (go.id == id)
			go.Destroy();
		else
		{
			GameObject* toDestroy =	go.FindChild(id);
			if (toDestroy != nullptr)
				toDestroy->Destroy();
		}
	}
}
