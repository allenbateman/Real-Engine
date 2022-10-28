#pragma once
#include "Panel.h"
class RendererPanel : public Panel
{
public:
	RendererPanel(int _id, bool isActive);
	~RendererPanel();

	void Begin();
	void End();
	void Init();
	void Update();
	bool CleanUp();

	bool BackCullFacing = true;
	bool DepthTest = true;
	bool Lightning = true;
	bool ColorMaterial = true;
};

