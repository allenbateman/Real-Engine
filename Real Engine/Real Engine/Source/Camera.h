#pragma once
#include "Module.h"
#include "System.h"
#include "External/MathGeoLib/MathGeoLib.h"
#include "glmath.h"
#include "Transform.h"
#include "Events.h"


class Camera
{
public:
	Camera();
	~Camera();

	bool Start();

	bool CleanUp();

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	void ChangeFieldOfView(float fieldOfView);

	void ResetCameraRotation();
	void ResetCameraPosition();
	void Focus(Transform target);

	void SetTarget(Transform myTarget);
	Transform GetTarget();

	float* GetViewMatrix();
	float& GetFieldOfView() { return fieldOfView; };
	void CalculateViewMatrix();

	void SetFocus(bool focus) { onFocus = focus; };
	bool GetFocus() { return onFocus; };
	
public:
	vec3 X, Y, Z, Position, Reference;
	Transform target;
	float cameraSpeed = 1.0f;
	MouseScroll mouseScrollEvent;
	bool altKey;
	bool mouseLeft;
	bool mouseRight;
	vec2 rotationSpeed{ 0.1f, 0.1f };
	float fieldOfView;

	float maxFieldOfView;
	float minFieldOfView;
	float zoomSpeed;
	mat4x4 projectioMatrix;
private:
	enum view
	{
		normal = 0,
		left,
		behind,
		right

	};
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ViewMatrixInverse;



	view cview = normal;
	bool freecam;
	bool onFocus;
};