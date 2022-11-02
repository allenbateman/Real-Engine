#pragma once
#include "Module.h"
#include "System.h"
#include "ObjectLoader.h"
#include "Scene.h"
class SceneManager : public Module, public System
{
public:
	SceneManager() {};
	~SceneManager();

	bool Awake();
	bool Start();
	bool Updte(float dt);
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();
	void HandleEvent(Event* e);

	Scene sampleScene;

	std::vector<Scene> sceneList;

	Scene currentSecene;

	bool ChangeScene(Scene newScene);

};

