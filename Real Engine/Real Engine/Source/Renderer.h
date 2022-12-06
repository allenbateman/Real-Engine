#pragma once
#include "Module.h"
#include "System.h"
#include "glmath.h"
#include "FrameBuffer.h"
#include <bitflags/bitflags.hpp>
#include "Shader.h"
#include "Camera.h"
#include "BuffCam.h"
#include "PickingTexture.h"

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
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void OnResize(int xPos,int yPos, int width, int height);
	
	void HandleEvent(Event* e);

	void AddCamera(Camera camera, BuffCamType type = eDefault);

	Entity currentCamera;

	BuffCam editor;
	BuffCam game;

	
	Shader* defaultShader;
	Shader* colorShader;

	//last renderer resize;
	vec2 lastSize;

	bool onFocus; 

	Camera editorCamera;
	Camera gameCamera;

	FrameBuffer editorBuffer;
	FrameBuffer gameBuffer;

	PickingTexture pickingTex;
	

	
private:
	//refernce of the current camera camera
	vector<BuffCam*> buffCams;

	

	
};

