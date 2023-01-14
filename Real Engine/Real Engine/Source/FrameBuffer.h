#pragma once
#include <GL/glew.h>
#include "Defs.h"
#include "glmath.h"

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void GenerateBuffer(int width ,int height);
	void ClearBuffer();
	vec2 GetTextureSize();
	GLuint textureID = NULL;
	GLuint FBO = NULL;
	GLuint RBO = NULL;
};

