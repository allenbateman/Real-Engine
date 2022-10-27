#pragma once
#include "Module.h"
#include "System.h"
class CameraController : public Module, public System
{
public:
	CameraController();
	~CameraController();
	bool Start();
	bool Update(float dt);
	void HandleEvent(Event* e);
};

