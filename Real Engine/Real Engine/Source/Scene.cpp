#include "Scene.h"
#include "SceneManager.h"
#include "Primitives.h"

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

void Scene::CreateGameObject(gameObjectType goType)
{
	switch (goType)
	{
	case EMPTY: 
	{
		GameObject* go = new GameObject("Empty Object");
		

		origin.GetComponent<Transform>().childs.push_back(&go->GetComponent<Transform>());
		go->GetComponent<Transform>().parent = &origin.GetComponent<Transform>();
		gameObejects.push_back(*go);
	}break;

	case CUBE:
	{
		GameObject* go = new GameObject("Cube");

		Cube cubeInfo;
		Mesh cubeMesh (cubeInfo.vertices, cubeInfo.indices);

		origin.GetComponent<Transform>().childs.push_back(&go->GetComponent<Transform>());
		go->GetComponent<Transform>().parent = &origin.GetComponent<Transform>();
		//go->AddComponent < Mesh(primitive.vertices, primitive.indices) >();
		go->AddComponent<Mesh>(cubeMesh);
		gameObejects.push_back(*go);
	}break;
	default:
		break;
	}
	
}

void Scene::LoadGameObject(const std::string file_path)
{
	
	std::vector<GameObject*> obj = app->sceneManager->objLoader.LoadObject(file_path);

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
