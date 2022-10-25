#pragma once

#include "Event.h"
#include "InputEnums.h"

struct KeyInput : public Event
{
	KeyInput() {type = EventType::KEY_INPUT; };
	~KeyInput() {};
	//KeyState keyState = KEY_IDLE;
	//int key = NULL;
	KeyState* keys = NULL;
	//int scancode = NULL;
	/*void DisplayData() {
		cout << "Key event: ";
		cout << "Key pressed = " << key;
		cout << " key state ="  << keyState << endl;
	}*/
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
	OnPanelResize(int _id, int _x, int _y) { id = _id; x = _x; y = _y; type = EventType::PANEL_RESIZE; };
	~OnPanelResize() {};
	int x, y,id;
};

struct OnPanelFocus :Event {
	OnPanelFocus(int _id, bool isFocused) { id = _id; focused = isFocused; type = EventType::ON_PANEL_FOCUS; };
	~OnPanelFocus() {};
	int id;
	bool focused = false;
};