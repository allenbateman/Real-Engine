#include "Viewport.h"

#include "Application.h"
#include "FrameBuffer.h"
#include "EventSystem.h"
#include "UiSystem.h"


Viewport::Viewport(int _id,bool isActive) : Panel(_id,isActive)
{
	name.Create("Camera Viewport");
}

Viewport::~Viewport()
{
}

void Viewport::Init()
{
	active = true;
	window_flags = ImGuiWindowFlags_NoDocking;
	borderOffset = 0;
}

void Viewport::Update()
{
	// render your GUI
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2{ 720,720 }, ImGuiCond_FirstUseEver);
	
	if (ImGui::Begin("Viewport"),NULL,window_flags)
	{
		OnHovered();
		OnResize();
		ImGui::Image((ImTextureID)app->renderer->editor.buffer.textureID, availableSize, ImVec2(0, 1), ImVec2(1, 0));
	
		//vec2 size = app->renderer->editor.buffer.GetTextureSize();
		//cout << "id: " << id << "Tex: " << app->renderer->editor.buffer.FBO << " x : " << size.x << " y : " << size.y << endl;
		//if (ImGui::BeginDragDropTarget()) {
		//	const ImGuiPayload* itemDrop = ImGui::AcceptDragDropPayload(payload_fileContent);
		//	if (itemDrop != nullptr)
		//	{
		//		//fs::path cpath = (wchar_t*)itemDrop->Data;

		//		Debug::Log("File dropped to scene...");
		//		//app->
		//		//fs::path newPath = path.string() + '/' + cpath.filename().string();
		//		//fs::rename(cpath, newPath);
		//	}
		//	ImGui::EndDragDropSource();
		//}
		ImGui::End();
	}

	ImGui::PopStyleVar();
}

bool Viewport::CleanUp()
{
	Panel::CleanUp();
	return true;
}
