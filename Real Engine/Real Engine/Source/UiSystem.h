#pragma once
#include "Application.h"
#include "Module.h"
#include "Panel.h"




#include "Viewport.h"

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

	bool OpenMainWindow;
	ImGuiIO* io = nullptr;
};

