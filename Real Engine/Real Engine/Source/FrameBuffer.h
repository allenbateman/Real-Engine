#pragma once
#include "glew.h"
#include "Defs.h"

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	 void GenerateBuffer(int width ,int height);
	GLuint framebufferTexture = NULL;
	GLuint FBO = NULL;
	GLuint RBO = NULL;
};

