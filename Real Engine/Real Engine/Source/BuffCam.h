#pragma once
#include "Camera.h"
#include "FrameBuffer.h"
enum BuffCamType
{
	eDefault = 0,
	eEditor = 1,
	eGame = 2,


};
struct BuffCam
{
	Camera camera;
	FrameBuffer buffer;
	BuffCamType type;
};