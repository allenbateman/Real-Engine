#pragma once
#include "Module.h"
#include "glmath.h"
#include "FrameBuffer.h"
#include "External/bitflags/bitflags.hpp"
#include "ObjectLoader.h"

#define MAX_LIGHTS 8

BEGIN_BITFLAGS(Flags)
FLAG(r_BackCulling)
END_BITFLAGS(Flags)

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
	bool HandleEvent(Event* e);

	FrameBuffer buffer;
	//Shader shader("C:/Users/allen/Documents/GitHub/Real-Engine/RealEngine/RealEngine/Source/testVertexShader.vs","C:/Users/allen/Documents/GitHub/Real-Engine/RealEngine/RealEngine/Source/testFragShader.frag");
	ObjectLoader objLoader;
	
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
};

