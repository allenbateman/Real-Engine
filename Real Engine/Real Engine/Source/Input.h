#pragma once
#include "Module.h"
#include "InputEnums.h"
#include "Events.h"
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

class Input : public Module
{

public:
	Input(bool isActive);
	virtual ~Input();
	bool Awake();
	bool Start();
	bool PreUpdate();
	bool CleanUp();

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void RetriveKeyCallBack(int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
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

	MouseInput mouseEvent;
	KeyInput keyEvent;

private:
	static bool windowEvents[WE_COUNT];
	static KeyState keyboard[sizeof(KeyState) * MAX_KEYS];
	static KeyState mouseButtons[sizeof(KeyState) * NUM_MOUSE_BUTTONS];
	int	mouseMotionX;
	int mouseMotionY;  
	static int mouseX;
	static int mouseY;
};

