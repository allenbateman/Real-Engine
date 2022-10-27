#pragma once
#include "Module.h"
#include "System.h"
#include <list>
#include <vector>
#include "Event.h"
#include <map>
#include <functional>


class EventSystem : public Module, public System
{
public:
	EventSystem() {};
	EventSystem(bool isActive);
	~EventSystem();

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void SubscribeModule(Module* _observer, EventType _event);
	void Unsubscribe(Module* _observer);

	void PostEvent(Event* _event);

	void BroadcastEvents();
	void PrintMapping();

private:
	std::map<Module*, vector<EventType>> obs;
	list<Event*> eventList;
};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
	return stream << static_cast<typename std::underlying_type<T>::type>(e);
}
