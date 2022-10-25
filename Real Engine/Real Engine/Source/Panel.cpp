#include "Panel.h"
#include "Events.h"


Panel::Panel()
{

}

Panel::Panel(int _id, bool startActive)
{
	active = startActive;
	id = _id;
	ePanelResize.id = id;
	ePanelFocus.id = id;
}

Panel::~Panel()
{
}

void Panel::Begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

}

void Panel::End()
{
}

bool Panel::Init()
{
	return true;
}
bool Panel::Update()
{
	return true;
}

bool Panel::CleanUp()
{
	ePanelFocus.~OnPanelFocus();
	ePanelResize.~OnPanelResize();

	return true;
}

bool Panel::OnHovered()
{
	if (ImGui::IsWindowHovered(0))
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();

		vMin.x += ImGui::GetWindowPos().x - borderOffset;
		vMin.y += ImGui::GetWindowPos().y - borderOffset;
		vMax.x += ImGui::GetWindowPos().x + borderOffset;
		vMax.y += ImGui::GetWindowPos().y + borderOffset;

		ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, borderColor, 0, 0, borderOffset);
		ePanelFocus.focused = true;
		app->eventSystem->PostEvent(&ePanelFocus);
		return true;
	}
	ePanelFocus.focused = false;
	app->eventSystem->PostEvent(&ePanelFocus);
	return false;
}

bool Panel::OnResize()
{
	availableSize = ImGui::GetContentRegionAvail();
	if (LastSize.x != availableSize.x || LastSize.y != availableSize.y)
	{
		LastSize = availableSize;
		ePanelResize.x = LastSize.x;
		ePanelResize.y = LastSize.y;

		BroadCastEvent(&ePanelResize);
		return true;
	}
	return false;
}

void Panel::BroadCastEvent(Event* e)
{
	app->eventSystem->PostEvent(e);
}

void Panel::HandleEvents(Event* e)
{
}

