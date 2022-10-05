#pragma once
#include "Event.h"

class Panel
{
	Panel(bool startActive);
	~Panel();

	virtual bool Init();
	virtual bool Update();
	virtual void HandleEvents(Event* e);

	bool active;
	
};

