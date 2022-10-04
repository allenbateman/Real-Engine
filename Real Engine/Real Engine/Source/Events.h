#pragma once

#include "Event.h"
#include "InputEnums.h"

struct KeyInput : public Event
{
	KeyInput() { type = EventType::KEY_INPUT; };
	~KeyInput() {};
	KeyState keyState;
	int key;
};

struct MouseInput : public Event
{
	MouseInput() { type = EventType::MOUSE_HOLE_MOUSE; };
	~MouseInput() {};
	KeyState keyState;
	int key;
	int x, y;

	void DisplayData(){
		cout << "Mouse event." << endl;
		cout << "mose x = " << x << endl;
		cout << "mose y = " << y << endl;
	}
};