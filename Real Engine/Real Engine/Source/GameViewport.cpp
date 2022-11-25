#include "GameViewport.h"

#include "Application.h"
#include "FrameBuffer.h"
#include "EventSystem.h"

GameViewport::GameViewport(int _id, bool isActive)
{
	name.Create("Game Viewport");
}

GameViewport::~GameViewport()
{
}

void GameViewport::Init()
{
	active = true;
	window_flags = ImGuiWindowFlags_NoDocking;
	borderOffset = 0;
}

void GameViewport::Update()
{
	// render your GUI
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2{ 720,720 }, ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Game"), NULL, window_flags)
	{

		OnHovered();
		OnResize();
		ImGui::Image((ImTextureID)app->renderer->buffer.framebufferTexture, availableSize, ImVec2(0, 1), ImVec2(1, 0));

	}
	ImGui::End();
	ImGui::PopStyleVar();
}

bool GameViewport::CleanUp()
{
	Panel::CleanUp();
	return true;
}
