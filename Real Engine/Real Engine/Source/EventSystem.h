#pragma once
#include "Module.h"
#include <list>
#include <vector>
#include "Event.h"
#include <map>

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

	void SubcribeModule(Module* _observer, Event* _event);
	void Unsubscribe(Module* _observer, Event* _event);
	void AddEvent(Event* newEvent);
	void BroadcastEvents();

private:
	//std::map<EventType type, std::vector<SlotType> > _observers;
	list<Event*> eventList;
};

