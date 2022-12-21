#include "ShaderEditorPanel.h"

ShaderEditorPanel::ShaderEditorPanel(int _id, bool isActive) : Panel( _id,  isActive)
{
}

ShaderEditorPanel::~ShaderEditorPanel()
{
}

void ShaderEditorPanel::Init()
{
	window_flags = ImGuiWindowFlags_NoDocking;
	borderOffset = 0;
}

void ShaderEditorPanel::Update()
{
	if (!active)
		return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2{ 720,720 }, ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Shader Editor", &active), NULL, window_flags)
    {
        OnHovered();
        OnResize();
        

    }
    ImGui::End();
    ImGui::PopStyleVar();
}

bool ShaderEditorPanel::CleanUp()
{
	return true;
}
