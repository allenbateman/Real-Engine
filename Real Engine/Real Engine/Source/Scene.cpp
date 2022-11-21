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
		Material cubeMaterial;
		cubeMaterial.textures.push_back(app->sceneManager->objLoader.loadedtextures[0]);

		origin.GetComponent<Transform>().childs.push_back(&go->GetComponent<Transform>());
		go->GetComponent<Transform>().parent = &origin.GetComponent<Transform>();
		//go->AddComponent < Mesh(primitive.vertices, primitive.indices) >();
		go->AddComponent<Mesh>(cubeMesh);
		//go->AddComponent<Material>(cubeMaterial);
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
	//if its a root go find it and destroy it
	for (auto& go : gameObejects)
	{
		if (go.id == id)
		{
			go.Destroy();
			return;
		}
	}
	//if its a child of a root 
	// for each root find the child
	for (auto& go : gameObejects)
	{
		GameObject* toDestroy = go.FindChild(id);
		if (toDestroy != nullptr)
		{
			toDestroy->Destroy();
			return;
		}
	}

}
