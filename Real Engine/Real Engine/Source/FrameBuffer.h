#pragma once
#include "glew.h"
#include "Defs.h"

class FrameBuffer
{
	FrameBuffer();
	~FrameBuffer();

	void GenerateBuffer(int &width,int &height);

	unsigned int FBO = NULL;
	unsigned int framebufferTexture = NULL;
	unsigned int RBO = NULL;
};

