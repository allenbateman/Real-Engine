#pragma once

#include "Event.h"
#include "InputEnums.h"
#include "GameObjectTypes.h"

struct KeyInput : public Event
{
	KeyInput() {type = EventType::KEY_INPUT; };
	~KeyInput() {};
	KeyState* keys = NULL;

};

struct MouseInput : public Event
{
	MouseInput() { type = EventType::MOUSE_INPUT; };
	~MouseInput() {};
	KeyState keyState = KEY_IDLE;
	int key = NULL;
	int x = 0, y = 0;
	void DisplayData(){
		cout << "Mouse input key:" << key << ", state: " << keyState << "\n";
	}
};

struct MousePosition : Event
{
	MousePosition() { type = EventType::MOUSE_POSITION;};
	~MousePosition() {};
	int x = 0, y = 0;
	int dx = 0, dy = 0;

	void DisplayData()
	{
		cout << "Mouse position x: " << x << " y:" << y << "\n";
	}

};
struct MouseScroll : Event
{
	MouseScroll() { type = EventType::MOUSE_SCROLL; }
	~MouseScroll() {};

	int dx = 0, dy = 0;

	void DisplayData()
	{
		cout << "Mouse scroll x: " << dx << " y: " << dy << "\n";
	}
};

struct  OnPanelResize : Event
{
public:
	OnPanelResize() {  type = EventType::PANEL_RESIZE; };
	~OnPanelResize() {};
	int x = 0, y = 0,id = 0;
};

struct OnPanelFocus :Event {
public:
	OnPanelFocus() {type = EventType::ON_PANEL_FOCUS; };
	~OnPanelFocus() {};
	int id = 0;
	bool focused = false;
};

struct OnFOVChange : Event
{
	OnFOVChange() { type = EventType::ON_FOV_CHANGE; };
	OnFOVChange(float changeValue) { this->changeValue = changeValue; type = EventType::ON_FOV_CHANGE; };
	~OnFOVChange() {};

	float changeValue = 0;
};

struct OnFileDrop : Event
{
	OnFileDrop() {  type = ON_FILE_DROP; }
	~OnFileDrop() {};
	
	const char* path = nullptr;

	void Displaydata()
	{
		cout << "File dropped with path: " << endl;
		cout << path << endl;
	}
};

struct OnGameObjectCreation : Event
{
	OnGameObjectCreation() { type = ON_GO_CREATION; }
	OnGameObjectCreation(gameObjectType goType) { this->goType = goType; type = ON_GO_CREATION; }

	~OnGameObjectCreation() {};

	gameObjectType goType = EMPTY;
};
