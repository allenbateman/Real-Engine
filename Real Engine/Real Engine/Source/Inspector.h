#pragma once
#include "Panel.h"
class Inspector : public Panel
{

	Inspector(int _id,bool isActive);
	~Inspector();
	bool Init();
	bool Update();



};

