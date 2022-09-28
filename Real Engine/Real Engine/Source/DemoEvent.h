#pragma once
#include "Event.h"
class DemoEvent : public Event
{
public:
	DemoEvent() { type = EventType::NONE; };
	~DemoEvent() {};

	//if this were a input event type
	const char* msg = "input event data";

};