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

	bool webPage = false;
	bool showInfo = false;
	string githubWebPage = "https://github.com/allenbateman/Real-Engine";

	ifstream file;
	string line;
};

