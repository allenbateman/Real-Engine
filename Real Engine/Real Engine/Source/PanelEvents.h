#pragma once

#include "Event.h"
struct PanelResize : public Event
{
	PanelResize() { type = EventType::PANEL_RESIZE; };
	~PanelResize() {};
	int xSize, ySize, xPos, yPos;

	void DisplayData() {
		cout << "Panel resize." << endl;
	}
};
