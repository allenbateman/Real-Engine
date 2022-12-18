#pragma once
#include "Module.h"
#include "System.h"
#include "glmath.h"
#include "FrameBuffer.h"
#include <bitflags/bitflags.hpp>
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

	void SetGameSpaceCamera(Camera* camera, RenderSpaceType type = noSpace);
	Entity editorCam;
	RenderSpace editor{};
	RenderSpace game{};
	bool onFocus = false;
	PickingTexture pickingTex;
private:
	//refernce of the current camera camera
	vector<RenderSpace*> renderers;
};

