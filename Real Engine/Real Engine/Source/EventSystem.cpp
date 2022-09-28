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

	list<Event*>::iterator event1 = eventList.begin();
	//SubcribeModule(app->window, (*event1));
	return true;
}

bool EventSystem::PreUpdate()
{
	
	for (list<Module*>::iterator currentModule = (*moduleList).begin(); currentModule != (*moduleList).end(); currentModule++)
	{
		
		(*currentModule)->HandleEvent(&eventList);

	}
	
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
}
