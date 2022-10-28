#pragma once
#include "Panel.h"
#define FPS_ON_PANEL 120
class FPSGraph : public Panel
{
	
	public:

		FPSGraph(int _id, bool isActive);
		~FPSGraph();
		void Init();
		void Update();
		bool CleanUp();
	

		float averageFPS;
		float lines[FPS_ON_PANEL] = { 0 };


};

