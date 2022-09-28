#include "EventSystem.h"
#include "Application.h"
#include "Window.h"
EventSystem::EventSystem(bool isActive) : Module(isActive)
{

}

EventSystem::~EventSystem()
{
}

bool EventSystem::Awake()
{
	moduleList = app->GetModuleList();
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

bool EventSystem::Update()
{
	return true;
}

bool EventSystem::PostUpdate()
{
	return true;
}

bool EventSystem::CleanUp()
{
	return true;
}

void EventSystem::SubcribeModule(Module* _module, Event* _event)
{
}

void EventSystem::Unsubscribe(Module* _module, Event* _event)
{
}


void EventSystem::AddEvent(Event* newEvent)
{
	eventList.push_back(newEvent);


	// mover esto de abajo a otro lado?
	//para controlar cuando mandar los eventos

	list<Event*>::iterator event1 = eventList.begin();

	for (list<Module*>::iterator currentModule = (*moduleList).begin(); currentModule != (*moduleList).end(); currentModule++)
	{
		//check if module has any subscription
		if (!(*currentModule)->subscribedEvents.empty())
		{
			//check for all subscriptions available and send the event of that sub type
			if ((*currentModule)->subscribedEvents.front() == (*event1)->GetType())
			{
				//send event to be filtered by the module
				(*currentModule)->HandleEvent(*event1);
				//remove the event sent from list
				//eventList.pop_front();
				//Add event pending to delete
				//no se donde se borran todos los obj event que creamos
				//eventsToDelete.push_back(*event1);
			}
		}
	}


}
