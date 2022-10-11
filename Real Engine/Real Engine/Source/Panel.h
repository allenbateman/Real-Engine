#pragma once
#include "Event.h"
#include "SString.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_glfw.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"
class Panel
{
public:
	Panel(bool startActive);
	~Panel();

	virtual bool Init();
	virtual bool Update();
	virtual bool PostUpdate();
	virtual bool CleanUp();
	virtual void HandleEvents(Event* e);
	SString name;
	bool active;
};

