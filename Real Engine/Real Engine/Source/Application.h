#ifndef __APPLICATION_H__
#define __APPLICATION_H__


#include "glew.h"
#include "glfw3.h"

#include "Log.h"
#include "Defs.h"
#include "Module.h"
#include "Timer.h"
#include <list>
#include <string>
#include <vector>
#include <cstdlib>
#include "EntityComponentSystem.h"

using namespace std;

// Modules
class Window;
class Input;
class EventSystem;
class UiSystem;
class Renderer;
class CameraController;

class Application
{
public:

	Application(int argc, char* args[]);
	virtual ~Application();
	bool Awake();
	bool Start();
	bool Update();
	bool CleanUp();

	// Add a new module to handle
	void AddModule(shared_ptr<Module> module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	// methods to request Load / Save
	void LoadGameRequest();
	void SaveGameRequest() const;

	list<shared_ptr<Module>>* GetModuleList() ;

	void BroadcastEvents();
private:

	// Call modules iteration
	void PrepareUpdate();
	void FinishUpdate();
	bool PreUpdate();
	bool DoUpdate();
	bool PostUpdate();
	// Load / Save
	bool LoadGame();
	bool SaveGame() const;

public:
	EntityComponentSystem entityComponentSystem;
	// Modules
	shared_ptr<Window> window;
	shared_ptr<Input> input;
	shared_ptr<EventSystem> eventSystem;
	shared_ptr<UiSystem> uiSystem;
	shared_ptr<Renderer> renderer;
	shared_ptr<CameraController> cameraController;

	bool exit = false;
private:

	int argc;
	char** args;

	SString appName;
	SString title;
	SString organization;

	list <shared_ptr<Module>> modules;

	mutable bool saveGameRequested;
	bool loadGameRequested;
	Timer	timer;
	float	dt;
	float timeCount;
	
	uint32 maxFrameRate = 0;
	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;
	bool FPSCapTo30 = false;
	float averageFps = 0.0f;
};
extern Application* app;

#endif	// __APP_H__