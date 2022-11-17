#pragma once
#include "Module.h"
#include "System.h"
#include "glmath.h"
#include "FrameBuffer.h"
#include <bitflags/bitflags.hpp>
#include "Shader.h"
#include "Camera.h"

#define MAX_LIGHTS 8

BEGIN_BITFLAGS(Flags)
FLAG(r_BackCulling)
END_BITFLAGS(Flags)

class Renderer : public Module, public System
{
public:
	Renderer() {};
	Renderer(bool isActive);
	~Renderer();

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

	void OnResize(int xPos,int yPos, int width, int height);
	//void ChangeFieldOfView(float fieldOfView, int width, int height);
	void DrawDirectCube(vec3 position, float size);
	void HandleEvent(Event* e);

	Entity currentCamera;

	FrameBuffer buffer;
	mat4x4 ProjectionMatrix;
	Shader* defaultShader;
	Shader* colorShader;

	//last renderer resize;
	vec2 lastSize;

	bool onFocus;
private:
	//refernce of the current camera camera
	Camera camera;
};

