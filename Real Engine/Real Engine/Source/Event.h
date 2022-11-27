#pragma once
#include <iostream>
using namespace std;

enum EventType {
	NONE = 0,
	MOUSE_INPUT,
	MOUSE_POSITION,
	MOUSE_SCROLL,
	KEY_INPUT,
	MOUSE_HOLE_MOUSE,
	PANEL_RESIZE,
	ON_PANEL_FOCUS,
	ON_FOV_CHANGE,
	ON_FILE_DROP,
	ON_FILE_DROP_VIEWPORT,
	ON_GO_CREATION,
};

class Event {

public:
	Event() {};
	virtual ~Event() {};
	EventType GetType() const { return type; };
	EventType type = NONE;
	void BaseDisplay() { DisplayData(); };
	virtual void DisplayData() {};
};
