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



	//attach detach from docking
	virtual void OnAttach();
	virtual void OnDetach();
	//Begin end new windows
	virtual void Begin();
	virtual void End();
	// start panel
	virtual bool Init();
	//update panel
	virtual bool Update();
	//clean panel
	virtual bool CleanUp();
	virtual void HandleEvents(Event* e);
	SString name;
	bool active;
};

