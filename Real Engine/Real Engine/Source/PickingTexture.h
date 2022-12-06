#pragma once
#include "Application.h"
#include <iostream>
#include "GL/glew.h"

struct PixelInfo {
	int ObjectId = 0;
	int DrawId = 0;
	int PrimId = 0;

	void Print()
	{
		std::cout << "Object " << ObjectId << " draw " << DrawId << " prim " << PrimId << std::endl;
	}
};

class PickingTexture
{
public: 
	PickingTexture();
	~PickingTexture();

	void Init(int widowWidth, int windowHeight);
	void EnableWriting();
	void DisableWriting();

	

	PixelInfo ReadPixel(int x, int y);

private:
	GLuint m_fbo = 0;
	GLuint m_pickingTexture = 0;
	GLuint m_depthTexture = 0;

	
};


