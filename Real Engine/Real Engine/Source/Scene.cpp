#include "Scene.h"
#include "SceneManager.h"
#include "Primitives.h"
#include "Camera.h"
#include "Renderer.h"

Scene::Scene()
{
}
Scene::Scene(const char* name)
{
	this->name = name;
	origin.name = name;
	cout << "Creating new scene: " << name << "\n";
}
Scene::~Scene()
{
}
void Scene::Init()
{
	mainCamera = new GameObject("Main Camera");
	mainCamera->AddComponent(Camera{});
	origin.GetComponent<Transform>().AddChild(&mainCamera->GetComponent<Transform>());
	mainCamera->GetComponent<Transform>().SetParent(&origin.GetComponent<Transform>());
	gameObejects.push_back(*mainCamera);
	mainCamera->GetComponent<Camera>().Start();
	mainCamera->GetComponent<Transform>().Translate(0.0f, 2.0f, 10.0f);

	app->renderer->SetGameSpaceCamera(&mainCamera->GetComponent<Camera>());
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
		
		go->AddComponent<Mesh>(cubeMesh);
		go->AddComponent<Material>(cubeMaterial);
		gameObejects.push_back(*go);
	}break;
	case SPHERE:
	{
		GameObject* go = new GameObject("Sphere");

		Sphere spherereInfo;
		Mesh shpereMesh(spherereInfo.vertices, spherereInfo.indices);
		Material sphereMaterial;
		sphereMaterial.textures.push_back(app->sceneManager->objLoader.loadedtextures[0]);

		origin.GetComponent<Transform>().childs.push_back(&go->GetComponent<Transform>());
		go->GetComponent<Transform>().parent = &origin.GetComponent<Transform>();
		
		go->AddComponent<Mesh>(shpereMesh);
		go->AddComponent<Material>(sphereMaterial);
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
