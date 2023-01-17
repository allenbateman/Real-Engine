#pragma once
#include "Panel.h"
#include "Application.h"
#include <string>
#include "ResourceShader.h"
#define MAX_SHADER_LENGTH 5000
class ShaderEditorPanel : public Panel
{
public:
	ShaderEditorPanel(int _id, bool isActive);
	~ShaderEditorPanel();

	void Init();
	void Update();
	bool CleanUp();
	shared_ptr<ResourceShader> SelectShader();
	void ShowTextEditor(const char* filepath);
private:
	bool editVertex = true;
	std::string vertexPath = "";
	std::string fragmentPath = "";
	shared_ptr<ResourceShader> currentShader;
	char* program = nullptr;
	int id = 0;
	bool Editing = false;
	std::string content;

};

