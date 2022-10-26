#pragma once
#include "Panel.h"
#define FPS_ON_PANEL 120
class FPSGraph : public Panel
{
	
	public:

		FPSGraph(int _id, bool isActive);
		~FPSGraph();
		bool Init();
		bool PreUpdate();
		bool Update();
		bool PostUpdate();
		bool CleanUp();
	

		float averageFPS;
		float lines[FPS_ON_PANEL] = { 0 };


};

