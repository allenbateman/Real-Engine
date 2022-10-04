#pragma once
#include "Module.h"
#include "External/MathGeoLib/MathGeoLib.h"
#include "glmath.h"


class Camera : public Module
{
public:
	Camera(bool isActive);
	~Camera();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	float* GetViewMatrix();

private:
	
	void DebugMode(float dt);
	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;
	
	
private:
	enum view
	{
		normal = 0,
		left,
		behind,
		right

	};

	view cview = normal;
	mat4x4 ViewMatrix, ViewMatrixInverse;
	bool freecam;
};