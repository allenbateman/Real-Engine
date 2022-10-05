#pragma once
#include "Module.h"
#include <list>
#include <vector>
#include "Event.h"
#include <map>
#include <functional>


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

	void SubcribeModule(Module* _observer,Event* _event);
	void Unsubscribe(Module* _observer, Event* _event);

	void PostEvent(Event* _event);

	void BroadcastEvents();
	void PrintMapping();

private:
	using SlotType = std::function< void(const Event&) >;
	std::map<Module*, vector<Event*>> obs;
	list<Event*> eventList;
};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
	return stream << static_cast<typename std::underlying_type<T>::type>(e);
}