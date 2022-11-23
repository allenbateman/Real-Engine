#pragma once
#include "Panel.h"

class ConsolePanel : public Panel
{

public :

	ConsolePanel(int _id, bool isActive);
	~ConsolePanel();

	void Init();
	void Update();
	bool CleanUp();

	void AddLog(const char* log); 
	
	void ClearConsole();
	
	

	ImGuiTextBuffer     buffer;
	ImGuiTextFilter     filter;
	ImVector<int>       lineOffsets;        
	bool                scrollToBottom;


};

