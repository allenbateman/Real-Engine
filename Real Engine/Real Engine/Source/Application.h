#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "External/Glfw/include/GLFW/glfw3.h"
#include "Log.h"
#include "Module.h"
#include <list>
#include <cstdlib>
using namespace std;

// Modules
class Window;
class Input;


class Application
{
public:

	// Constructor
	Application(int argc, char* args[]);

	// Destructor
	virtual ~Application();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
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



private:

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();


	// Load / Save
	bool LoadGame();
	bool SaveGame() const;

public:

	// Modules
	Window *window;
	Input *input;

	float dt;
	bool exit = false;
private:
	int argc;
	char** args;
	SString title;
	SString organization;

	list <Module*> modules;

	uint frames;


	mutable bool saveGameRequested;
	bool loadGameRequested;

	//PerfTimer ptimer;
	//PerfTimer frameDuration;

	//Timer startupTime;
	//Timer frameTime;
	//Timer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;
	bool FPSCapTo30 = false;
	float averageFps = 0.0f;

	uint32 maxFrameRate = 0;

	SString appName;
};
extern Application* app;

#endif	// __APP_H__