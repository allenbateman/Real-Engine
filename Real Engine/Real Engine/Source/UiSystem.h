#pragma once
#include "Application.h"
#include "Module.h"
#include "Panel.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_glfw.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"

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

private:
	vector<Panel*> panelList;
};

