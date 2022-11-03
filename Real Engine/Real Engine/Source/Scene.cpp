#include "Scene.h"

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


bool Scene::Awake()
{
	return true;
}

bool Scene::Start()
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);


	//load house  TODO move to scene
	auto obj = objLoader.LoadObject("../Output/Assets/BakerHouse.fbx");
	gameObejects.push_back(*obj);

	return true;
}

bool Scene::PreUpdate()
{
	return true;
}

bool Scene::Update(float dt)
{
	return true;
}

bool Scene::PostUpdate()
{
	return true;
}

bool Scene::CleanUp()
{
	aiDetachAllLogStreams();
	return true;
}

void Scene::HandleEvent(Event* singleEvent)
{

}

void Scene::CreateGameObject()
{
}
