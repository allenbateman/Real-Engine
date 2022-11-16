#pragma once

#include "Panel.h"
class AboutPanel : public Panel
{
public:
	AboutPanel(int _id, bool isActive);
	~AboutPanel();

	void Init();
	void Update();
	bool CleanUp();

	bool opened = false;
	string githubWebPage = "https://github.com/allenbateman/Real-Engine";
};

