#pragma once
#include <iostream>
using namespace std;

enum EventType {
	NONE = 0,
	MOUSE_BUTTON

};

class Event {

public:
	Event() {};
	~Event() {};
	EventType GetType() { return type; };
	EventType type;
};