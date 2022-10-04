#pragma once
#include <iostream>
using namespace std;

enum EventType {
	NONE = 0,
	MOUSE_INPUT,
	MOUSE_POSITION,
	MOUSE_HOLE_MOUSE,
	KEY_INPUT
};

class Event {

public:
	Event() {};
	virtual ~Event() {};
	EventType GetType() { return type; };
	EventType type;
};
