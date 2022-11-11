#pragma once
#include <GL/glew.h>
#include "Defs.h"

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	 void GenerateBuffer(int width ,int height);
	 void ClearBuffer();
	GLuint framebufferTexture = NULL;
	GLuint FBO = NULL;
	GLuint RBO = NULL;
};

