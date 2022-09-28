#pragma once
#include "Module.h"
#include "DemoEvent.h"

#define MAX_KEYS 300
#define NUM_MOUSE_BUTTONS 5
//#define LAST_KEYS_PRESSED_BUFFER 50

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};



class Input : public Module
{

public:
	Input(bool isActive);

	// Destructor
	virtual ~Input();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called before quitting
	bool CleanUp();

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void windowCloseCallback(GLFWwindow* window);
	int GetKey(int key);

	KeyState GetMouseButtonDown(int id) const
	{
		return mouseButtons[id - 1];
	}

	// Check if a certain window event happened
	bool GetWindowEvent(EventWindow ev);

	// Get mouse / axis position
	void GetMousePosition(int& x, int& y);
	void GetMouseMotion(int& x, int& y);

	DemoEvent* event1;

private:
	static bool windowEvents[WE_COUNT];
	static KeyState keyboard[sizeof(KeyState) * MAX_KEYS];
	KeyState mouseButtons[NUM_MOUSE_BUTTONS];
	int	mouseMotionX;
	int mouseMotionY;  
	int mouseX;
	int mouseY;
};

