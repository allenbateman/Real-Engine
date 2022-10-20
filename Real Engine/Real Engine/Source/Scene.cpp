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

bool Scene::HandleEvent(Event* singleEvent)
{
	return true;
}

GameObject* Scene::CreateGameObject()
{
	return nullptr;
}
