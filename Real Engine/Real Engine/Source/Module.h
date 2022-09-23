#ifndef __MODULE_H__
#define __MODULE_H__

#include <iostream>
#include "SString.h"


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

public:
	SString name;
	bool active;
	bool DEBUG = false;
};

#endif // __MODULE_H__