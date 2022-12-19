#pragma once
#include "Camera.h"
#include "FrameBuffer.h"
enum RenderSpaceType
{
	noSpace = 0,
	eEditor = 1,
	eGame = 2,
};
struct RenderSpace
{
	Camera* camera;
	FrameBuffer buffer;
	mat4x4 ProjectionMatrix;
	RenderSpaceType type = noSpace;
	vec2 lastSize;

	void OnResize(int xPos = 0, int yPos = 0, int width = 0, int height = 0)
	{
		if (camera == nullptr) return;
		buffer.GenerateBuffer(width, height);

		glViewport(xPos, yPos, width, height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		ProjectionMatrix = perspective(camera->GetFieldOfView(), (float)width / (float)height, 0.125f, 512.0f);
		glLoadMatrixf(&ProjectionMatrix);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		lastSize.x = width;
		lastSize.y = height;

		cout << "id :"<<type << " x : " << width << " y : " << height << endl;
	}

	void OnFovChange()
	{
		if (camera == nullptr) return;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		ProjectionMatrix = perspective(camera->GetFieldOfView(), (float)lastSize.x / (float)lastSize.y, 0.125f, 512.0f);
		glLoadMatrixf(&ProjectionMatrix);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void SetCamera(Camera* _camera)
	{
		camera = _camera;
	}
};