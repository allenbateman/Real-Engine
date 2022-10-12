#pragma once
#include "Module.h"
#include "glmath.h"


#define MAX_LIGHTS 8

class Renderer : public Module
{
public:
	Renderer(bool isActive);
	~Renderer();

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

	void OnResize(int xPos,int yPos, int width, int height);
	void DrawDirectCube(vec3 position, float size);

	unsigned int FBO = NULL;
	unsigned int framebufferTexture = NULL;
	unsigned int RBO = NULL;

	void GenerateBuffer();

	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
};

