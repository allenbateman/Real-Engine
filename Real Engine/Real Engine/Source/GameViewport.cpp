#include "GameViewport.h"

#include "Application.h"
#include "FrameBuffer.h"
#include "EventSystem.h"

GameViewport::GameViewport(int _id, bool isActive) : Panel(_id, isActive)
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
		ImGui::Image((ImTextureID)app->renderer->game.buffer.textureID, availableSize, ImVec2(0, 1), ImVec2(1, 0));

		//vec2 size = app->renderer->game.buffer.GetTextureSize();
		//cout << "id: " << id <<"Tex: "<< app->renderer->game.buffer.FBO << " x : " << size.x << " y : " << size.y << endl;
	}
	ImGui::End();
	ImGui::PopStyleVar();
}

bool GameViewport::CleanUp()
{
	Panel::CleanUp();
	return true;
}
