#include "Application.h"
#include "Camera.h"
#include "Input.h"
#include "Window.h"
#include "EventSystem.h"
#include "PanelIDs.h"
#include "UiSystem.h"

Camera::Camera()
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 5.0f, 30.0f);
	Reference = vec3(0.0f, 5.0f, 0.0f);
	target.position = Reference;

	freecam = false;
	maxFieldOfView = 120.0f;
	fieldOfView = 60.0f;
	minFieldOfView = 40.0f;
	zoomSpeed = 4.0f;

}

Camera::~Camera()
{}

// -----------------------------------------------------------------
bool Camera::Start()
{
	
	bool ret = true;

	freecam = false;
	maxFieldOfView = 120.0f;
	fieldOfView = 60.0f;
	minFieldOfView = 40.0f;
	zoomSpeed = 4.0f;
	return ret;
}

// -----------------------------------------------------------------
bool Camera::CleanUp()
{
	return true;
}

// -----------------------------------------------------------------
void Camera::Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void Camera::LookAt( const vec3 &Spot)
{
	Reference = Spot;
	
	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void Camera::Move(const vec3 &Movement)
{
	Position += Movement;
	Reference += Movement;
	CalculateViewMatrix();
}

void Camera::ChangeFieldOfView(float fov)
{
	float fieldOfViewValue = fieldOfView - fov;

	if (minFieldOfView > fieldOfViewValue || fieldOfViewValue > maxFieldOfView)
	{
		if (fieldOfViewValue > maxFieldOfView) fieldOfView = maxFieldOfView;
		if (fieldOfViewValue < minFieldOfView) fieldOfView = minFieldOfView;
		return;
	}

	fieldOfView -= fov * zoomSpeed;
}

void Camera::ResetCameraRotation()
{
	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	CalculateViewMatrix();
}
void Camera::ResetCameraPosition()
{
	Position = vec3(0.0f, 5.0f, 30.0f);
	Reference = vec3(0.0f, 5.0f, 0.0f);
}
void Camera::SetTarget(Transform myTarget)
{
	target = myTarget;
}
Transform Camera::GetTarget()
{
	return target;
}
void Camera::Focus(Transform target)
{
	
	LookAt(target.position);
	Position = vec3(target.position.x, target.position.y + 5.0f, target.position.z - 10.0f);

	CalculateViewMatrix();
}
// -----------------------------------------------------------------
float* Camera::GetViewMatrix()
{
	return &ViewMatrix;
}

// -----------------------------------------------------------------
void Camera::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}