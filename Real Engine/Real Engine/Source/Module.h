#ifndef __MODULE_H__
#define __MODULE_H__

#include <iostream>
#include "SString.h"
#include "Event.h"
#include <list>
class Application;

class Module
{ 
public:
	Module(bool isActive) : active(isActive) {}

	void Init() {}

	virtual bool Awake()
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual bool PreUpdate()
	{
		return true;
	}

	virtual bool Update(float dt)
	{
		return true;
	}

	virtual bool PostUpdate()
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool OnGuiMouseClickEvent()
	{
		return true;
	}

	void Enable()
	{
		if (!active)
		{
			active = true;
			Start();
		}
	}

	void Disable()
	{
		if (active)
		{
			active = false;
			CleanUp();
		}
	}

	virtual bool HandleEvent(Event* singleEvent)
	{
		return true; 
	}

public:

	SString name;
	bool active;
	bool DEBUG = false;
	list<EventType> subscribedEvents;
};

#endif // __MODULE_H__