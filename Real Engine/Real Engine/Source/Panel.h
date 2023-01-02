#pragma once
#include "Event.h"
#include "EventSystem.h"
#include "Events.h"
#include <filesystem>
#include <ImGui/imgui.h>
#include <ImGui/backends/imgui_impl_glfw.h>
#include <ImGui/backends/imgui_impl_opengl3.h>


namespace fs = std::filesystem;
class Panel
{
public:
	Panel();
	Panel(int _id, bool startActive);
	virtual ~Panel();

	// start panel
	virtual void Init();
	//update panel
	virtual void Update();
	//clean panel
	virtual bool CleanUp();

	virtual bool OnHovered();
	virtual bool OnResize();

	virtual void BroadCastEvent(Event* e);
	virtual void HandleEvents(Event* e);

	ImVec2 GetPanelSize();
	SString name;
	int id;
	bool active;
	ImGuiWindowFlags window_flags;
	//store the border offset of available space in each panel
	int borderOffset = 2;
	ImColor borderColor = { 125, 125, 125, 200 };
	ImVec2 availableSize;
	ImVec2 LastSize;

	OnPanelResize ePanelResize;
	OnPanelFocus ePanelFocus;

	int scrollDisplacement = 0;

	bool LastPanelFocus = false;
	bool PanelResize = false;
	
};


//Panel ImGuiPayload events
static const char* payload_fileContent = "file_scene_drop";
static const char* payload_objectHierarchy = "SceneHierarchy";