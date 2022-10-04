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
	~MouseInput();
	KeyState keyState;
	int key;
	int x, y;
};