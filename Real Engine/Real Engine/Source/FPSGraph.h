#pragma once
#include "Panel.h"
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


};

