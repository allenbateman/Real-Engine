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

	bool HandleEvent(Event* e);

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);

	void ResetCameraRotation();
	void ResetCameraPosition();

	void SetReference(vec3 myReference);

	float* GetViewMatrix();
	float* GetProjectionMatrix();

private:
	
	void DebugMode(float dt);
	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;
	float cameraSpeed = 2.5f;
	
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

	vec2 rotationSpeed{ 0.1f, 0.1f };

	bool mouseLeft;
	bool mouseRight;
	bool onFocus;
};