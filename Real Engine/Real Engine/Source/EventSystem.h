#pragma once
#include "Module.h"
#include "System.h"
#include <list>
#include <vector>
#include <map>
#include <functional>
#include "Event.h"



class EventSystem : public Module
{
public:
	EventSystem() {};
	EventSystem(bool isActive);
	~EventSystem();

	bool CleanUp();

	void SubscribeModule(Module* _observer, EventType _event);
	void Unsubscribe(Module* _observer);

	void PostEvent(Event* _event);

	void BroadcastEvents();
	void PrintMapping();

//--------------new

	void AddListener(EventType type, std::function<void(Event&)> listener);
	//void SendEvent(Event& event);
	//void SendEvent(EventType type);

private:
	std::map<Module*, vector<EventType>> obs;
	std::map<EventType, std::list<std::function<void(Event&)>>> listeners{ };
	list<Event*> eventList;
};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
	return stream << static_cast<typename std::underlying_type<T>::type>(e);
}
