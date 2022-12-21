#pragma once
#include "Panel.h"
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
	char* vertexPath;
	char* fragmentPath;

	char* program = nullptr;
	
	int id = 0;
};

