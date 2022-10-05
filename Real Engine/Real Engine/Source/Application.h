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
using namespace std;

// Modules
class Window;
class Input;
class EventSystem;
class UiSystem;
class Renderer;
class Camera;

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
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	// methods to request Load / Save
	void LoadGameRequest();
	void SaveGameRequest() const;

	list<Module*>* GetModuleList() ;

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

	// Modules
	Window *window;
	Input *input;
	EventSystem* eventSystem;
	UiSystem* uiSystem;
	Renderer* renderer;
	Camera* camera;

	
	bool exit = false;
private:

	int argc;
	char** args;

	SString appName;
	SString title;
	SString organization;

	list <Module*> modules;

	mutable bool saveGameRequested;
	bool loadGameRequested;

	//PerfTimer ptimer;
	//PerfTimer frameDuration;

	//Timer startupTime;
	//Timer frameTime;
	//Timer lastSecFrameTime;
	Timer	timer;
	float	dt;

	uint frames;
	uint32 maxFrameRate = 0;
	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;
	bool FPSCapTo30 = false;
	float averageFps = 0.0f;
};
extern Application* app;

#endif	// __APP_H__