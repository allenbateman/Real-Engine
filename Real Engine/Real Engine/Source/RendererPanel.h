#pragma once
#include "Panel.h"
class RendererPanel : public Panel
{
public:
	RendererPanel(bool isActive);
	~RendererPanel();

	void Begin();
	void End();
	bool Init();
	bool Update();
	bool CleanUp();

	bool BackCullFacing = true;
	bool DepthTest = true;
	bool Lightning = true;
	bool ColorMaterial = true;
};

