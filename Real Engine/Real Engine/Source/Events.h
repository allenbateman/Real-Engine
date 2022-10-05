#pragma once

#include "Event.h"
#include "InputEnums.h"

struct KeyInput : public Event
{
	KeyInput() { type = EventType::KEY_INPUT; };
	~KeyInput() {};
	KeyState keyState = KEY_IDLE;
	int key = NULL;
	int scancode = NULL;
	void DisplayData() {
		cout << "Key event." << endl;
		cout << "Key pressed = " << key << endl;
		cout << "key state ="  << keyState << endl;
	}
};

struct MouseInput : public Event
{
	MouseInput() { type = EventType::MOUSE_HOLE_MOUSE; };
	~MouseInput() {};
	KeyState keyState = KEY_IDLE;
	int key = NULL;
	void DisplayData(){
		cout << "Mouse input key:" << key << ", state: " << keyState << "\n";
	}
};

struct MousePosition : Event
{
	MousePosition() { type = EventType::MOUSE_POSITION;};
	~MousePosition() {};
	int x = 0, y = 0;

	void DisplayData()
	{
		cout << "Mouse position x: " << x << " y:" << y << "\n";
	}

};