#pragma once
#include "Panel.h"
#include "Application.h"
#include <string>

class ShaderEditorPanel : public Panel
{
public:
	ShaderEditorPanel(int _id, bool isActive);
	~ShaderEditorPanel();

	void Init();
	void Update();
	bool CleanUp();

private:
	bool editVertex = true;
	std::string vertexPath = "";
	std::string fragmentPath = "";

	char* program = nullptr;
	
	int id = 0;
};

