#include "Panel.h"
#include "Events.h"
#include "Application.h"


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

void Panel::Init()
{
}
void Panel::Update()
{
}

bool Panel::CleanUp()
{
	ePanelFocus.~OnPanelFocus();
	ePanelResize.~OnPanelResize();

	return true;
}

bool Panel::OnHovered()
{
	bool focus = false;
	if (ImGui::IsWindowHovered(0))
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();
		vMin.x += ImGui::GetWindowPos().x - borderOffset;
		//vMin.y += ImGui::GetWindowPos().y - borderOffset;
		vMax.x += ImGui::GetWindowPos().x + borderOffset;
		vMax.y += ImGui::GetWindowPos().y + borderOffset;
		ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, borderColor, 0, 0, borderOffset);
		
		focus = true;
	}
	else {
		focus = false;
	}
	if (LastPanelFocus != focus)
	{
		LastPanelFocus = focus;
		ePanelFocus.focused = focus;
		app->eventSystem->PostEvent(&ePanelFocus);
	}
	return focus;
}

bool Panel::OnResize()
{
	bool Resized = false;
	availableSize = ImGui::GetContentRegionAvail();
	if (LastSize.x != availableSize.x || LastSize.y != availableSize.y)
	{
		LastSize = availableSize;
		ePanelResize.x = LastSize.x;
		ePanelResize.y = LastSize.y;


		Resized =  true;
		PanelResize = true;
	}
	if ((PanelResize != Resized))
	{
		BroadCastEvent(&ePanelResize);
		PanelResize = false;
	}
	Resized = false;


	return Resized;
}

void Panel::BroadCastEvent(Event* e)
{
	app->eventSystem->PostEvent(e);
}

void Panel::HandleEvents(Event* e)
{
	switch (e->type)
	{
	case MOUSE_SCROLL:
	{
		MouseScroll* ms = dynamic_cast<MouseScroll*>(e);
		scrollDisplacement += ms->dy;
	}	
	break;
	default:
		break;
	}
}

ImVec2 Panel::GetPanelSize()
{
	return LastSize;
}

