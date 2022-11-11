#pragma once
#include "Application.h"
#include "Module.h"
#include "System.h"
#include "Panel.h"


#include "PanelIDs.h"

#include "Viewport.h"
#include "RendererPanel.h"
#include "FPSGraph.h"
#include "Inspector.h"
#include "SceneHerarchyPanel.h"
#include "FileExplorer.h"

// Variables to configure the Dockspace example.
static bool opt_fullscreen = true; // Is the Dockspace full-screen?
static bool opt_padding = false; // Is there padding (a blank space) between the window edge and the Dockspace?
static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None; // Config flags for the Dockspace

class UiSystem :  public Module, public System
{
public:
	UiSystem() {};
	UiSystem(bool isActive);
	~UiSystem();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();
	void HandleEvent(Event* event);

	void PrepareFrame();
	void UpdatePanels();
	void RenderUi();
	void MainAppDockSpace(bool* p_open);
	
	void SetStyle();

	ImVec2 GetPanelSize(PanelID id);
private:
	vector<Panel*> panelList;

	Viewport* camViewport;
	RendererPanel* mainRenderer;
	FPSGraph* fpsGraph;
	Inspector* inspector;
	SceneHerarchyPanel* herarchyPanel;
	FileExplorer* fileExplorer;

	bool OpenMainWindow;
	ImGuiIO* io = nullptr;
};
