#pragma once
#include "Module.h"
#include <list>
#include "Event.h"


class EventSystem : public Module
{
public:
	EventSystem(bool isActive);
	~EventSystem();

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void SubcribeModule(Module* _module, Event* _event);
	void Unsubscribe(Module* _module, Event* _event);
	void AddEvent(Event* newEvent);
	void BroadcastEvents();

private:
	list<Event*> eventList;
};

