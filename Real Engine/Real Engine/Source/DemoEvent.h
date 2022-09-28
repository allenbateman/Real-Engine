#pragma once
#include "Event.h"
class DemoEvent : public Event
{
public:
	DemoEvent() { type = EventType::NONE; };

	string msg = "Hola soy event none";
};