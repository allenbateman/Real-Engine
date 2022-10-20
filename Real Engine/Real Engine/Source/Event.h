#pragma once
#include <iostream>
using namespace std;

enum EventType {
	NONE = 0,
	MOUSE_INPUT,
	MOUSE_POSITION,
	KEY_INPUT,
	MOUSE_HOLE_MOUSE,
	PANEL_RESIZE
};

class Event {

public:
	Event() {};
	virtual ~Event() {};
	EventType GetType() const { return type; };
	EventType type;
	void BaseDisplay() { DisplayData(); };
	virtual void DisplayData() {};
};
