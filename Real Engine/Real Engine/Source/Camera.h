#pragma once
#include "Module.h"
#include "System.h"
#include "External/MathGeoLib/MathGeoLib.h"
#include "glmath.h"
#include "Transform.h"
#include "Events.h"


class Camera : public Module,public System
{
public:
	Camera();
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
	void Focus(Transform target);

	void SetTarget(Transform myTarget);
	Transform GetTarget();

	float* GetViewMatrix();
	float* GetProjectionMatrix();

private:
	
	void DebugMode(float dt);
	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;
	Transform target;
	
	float cameraSpeed = 1.0f;

	MouseScroll mouseScrollEvent;

	
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

	bool altKey;
	bool mouseLeft;
	bool mouseRight;
	bool onFocus;
};