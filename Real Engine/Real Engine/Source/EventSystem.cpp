#include "EventSystem.h"
#include "Application.h"
#include "Window.h"
#include "Log.h"
EventSystem::EventSystem(bool isActive) : Module(isActive)
{

}

EventSystem::~EventSystem()
{
}

bool EventSystem::Awake()
{
	return true;
}

bool EventSystem::Start()
{

	return true;
}

bool EventSystem::PreUpdate()
{

	return true;
}

bool EventSystem::Update(float dt)
{
	return true;
}

bool EventSystem::PostUpdate()
{
	return true;
}

bool EventSystem::CleanUp()
{
	eventList.clear();
	return true;
}

void EventSystem::SubcribeModule(Module* _module, EventType _event)
{
	obs[_module].push_back(_event);
}

void EventSystem::Unsubscribe(Module* _module, Event* _event)
{
}

void EventSystem::PostEvent(Event* _event)
{
	for (typename std::map<Module*, vector<EventType>>::const_iterator i = obs.begin(); i != obs.end(); ++i)
	{

		for (typename vector<EventType>::const_iterator e = i->second.begin(); e != i->second.end(); e++)
			if ((*e) == _event->type)
			{
				i->first->HandleEvent(_event);
			}
	}
		
}

void EventSystem::BroadcastEvents()
{



	//if (eventList.empty())
	//	return;

	//list<Event*>::iterator event1 = eventList.begin();

	//if ((*event1) == nullptr)
	//	return;
	//
	//for (list<Module*>::iterator currentModule = app->GetModuleList()->begin(); currentModule != app->GetModuleList()->end(); currentModule++)
	//{
	//	//check if module has any subscription
	//	if (!(*currentModule)->subscribedEvents.empty())
	//	{
	//		//check for all subscriptions available and send the event of that sub type
	//		if ((*currentModule)->subscribedEvents.front() == (*event1)->GetType())
	//		{
	//			//send event to be filtered by the module
	//			(*currentModule)->HandleEvent(*event1);
	//			//remove the event sent from list
	//			eventList.remove(*event1);
	//		}
	//	}
	//}
}

void EventSystem::PrintMapping()
{
	/*for (typename std::map<Module*, vector<EventType>>::const_iterator i = obs.begin(); i != obs.end(); ++i)
	{

		string name = i->first->name.GetString();
		cout << "Module " << name << " subscribed to:"<<endl;

		for (typename vector<EventType>::const_iterator e = i->second.begin(); e != i->second.end(); e++)
			 cout<<(*e);
	}*/
}
