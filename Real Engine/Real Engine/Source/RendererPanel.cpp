#include "RendererPanel.h"
#include "Application.h"
#include "Renderer.h"

RendererPanel::RendererPanel(int _id,bool isActive) : Panel(_id, isActive)
{
	name.Create("Render Settings");
}

RendererPanel::~RendererPanel()
{
}

void RendererPanel::Begin()
{
}

void RendererPanel::End()
{
}

void RendererPanel::Init()
{
	window_flags = ImGuiConfigFlags_DockingEnable;
}

void RendererPanel::Update()
{
	if (!active)
		return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(2.0f, 2.0f));
	ImGui::SetNextWindowSize(ImVec2{ 720,720 }, ImGuiCond_FirstUseEver);
	if (ImGui::Begin(name.GetString(), &active))
	{
		OnHovered();
		OnResize();
		if (ImGui::MenuItem("Back culling", "", (BackCullFacing) != 1)) { BackCullFacing = !BackCullFacing;  BackCullFacing ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE); }
		if (ImGui::MenuItem("Depth test", "", (DepthTest) != 1)) { DepthTest = !DepthTest;  DepthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST); }
		if (ImGui::MenuItem("Lighting", "", (Lightning) != 1)) { Lightning = !Lightning;  Lightning ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING); }
		if (ImGui::MenuItem("Color material", "", (ColorMaterial) != 1)) { ColorMaterial = !ColorMaterial;  ColorMaterial ? glEnable(GL_COLOR_MATERIAL) : glDisable(GL_COLOR_MATERIAL); }
	}
	ImGui::End();
	ImGui::PopStyleVar();
}

bool RendererPanel::CleanUp()
{
	Panel::CleanUp();
	return true;
}
