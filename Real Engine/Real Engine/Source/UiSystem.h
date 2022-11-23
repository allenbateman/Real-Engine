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
#include "AboutPanel.h"
#include "ConsolePanel.h"

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
	ConsolePanel* GetConsole() { return consolePanel; }
private:
	vector<Panel*> panelList;

	Viewport* camViewport;
	RendererPanel* mainRenderer;
	FPSGraph* fpsGraph;
	Inspector* inspector;
	SceneHerarchyPanel* herarchyPanel;
	FileExplorer* fileExplorer;
	AboutPanel* aboutPanel;
	ConsolePanel* consolePanel;

	bool OpenMainWindow;
	ImGuiIO* io = nullptr;

};

namespace Debug {

	 void Log(const string text);
	 void Warning(const string text);
	 void Error(const string text);
}