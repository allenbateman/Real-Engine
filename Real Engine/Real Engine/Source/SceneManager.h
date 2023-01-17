#pragma once
#include "Module.h"
#include "System.h"
#include "ObjectLoader.h"
#include "Scene.h"

#define MAX_SCENES 25
class SceneManager : public Module, public System
{
public:
	SceneManager() {};
	~SceneManager();

	bool Awake();
	bool Start();
	bool Update(float dt);
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();
	void HandleEvent(Event* e);

	unsigned int sceneCount = 0;

	Scene* currentScene = nullptr;
	std::vector<Scene> sceneList{};
	bool ChangeScene(Scene newScene);
	Scene* CreateScene(std::string name);
	//ObjectLoader objLoader;

	//GetScene by id
	Scene& GetScene(unsigned int id);
	//Get Scene by name
	Scene& GetScene(std::string name);
};

