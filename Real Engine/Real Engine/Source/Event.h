#pragma once
#include <iostream>
using namespace std;

enum EventType {
	NONE = 0,
	INPUT_MOUSE_BUTTON,
	INPUT_KEY
};

class Event {

public:
	Event() {};
	virtual ~Event() {};
	EventType GetType() { return type; };
	EventType type;

};