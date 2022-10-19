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

	//Begin end new windows
	virtual void Begin();
	virtual void End();
	// start panel
	virtual bool Init();
	//update panel
	virtual bool Update();
	//clean panel
	virtual bool CleanUp();

	virtual bool OnPanelHovered();

	virtual void BroadCastEvent(Event* e);
	virtual void HandleEvents(Event* e);
	SString name;
	bool active;
	ImGuiWindowFlags window_flags;
	//store the border offset of available space in each panel
	int borderOffset = 2;
	ImColor borderColor = { 125, 125, 125, 200 };
};


