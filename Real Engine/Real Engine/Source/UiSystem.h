#pragma once
#include "Application.h"
#include "Module.h"
#include "Panel.h"




#include "Viewport.h"
#include "RendererPanel.h"

// Variables to configure the Dockspace example.
static bool opt_fullscreen = true; // Is the Dockspace full-screen?
static bool opt_padding = false; // Is there padding (a blank space) between the window edge and the Dockspace?
static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None; // Config flags for the Dockspace

class UiSystem :  public Module
{
public:
	UiSystem(bool isActive);
	~UiSystem();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();

	void PrepareFrame();
	void UpdatePanels();
	void RenderUi();
	void MainAppDockSpace(bool* p_open);
private:
	vector<Panel*> panelList;

	Viewport* camViewport;
	RendererPanel* mainRenderer;

	bool OpenMainWindow;
	ImGuiIO* io = nullptr;
};
