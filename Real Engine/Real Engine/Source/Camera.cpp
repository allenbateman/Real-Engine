#include "Application.h"
#include "Camera.h"
#include "Input.h"
#include "Window.h"


Camera::Camera(bool isActive) : Module(isActive)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
	
}

Camera::~Camera()
{}

// -----------------------------------------------------------------
bool Camera::Start()
{
	
	bool ret = true;

	freecam = false;

	return ret;
}

// -----------------------------------------------------------------
bool Camera::CleanUp()
{
	

	return true;
}

// -----------------------------------------------------------------
bool Camera::Update(float dt)
{
	if (app->input->GetKey(GLFW_KEY_C) == KEY_DOWN)
	{
		freecam = !freecam;
	}
	
	if (app->input->GetKey(GLFW_KEY_J) == KEY_REPEAT)
	{
		cview = right;
	}
	else if (app->input->GetKey(GLFW_KEY_H) == KEY_REPEAT)
	{
		cview = behind;
	}
	else if (app->input->GetKey(GLFW_KEY_G) == KEY_REPEAT)
	{
		cview = left;
	}
	else
	{
		cview = normal;
	}
	cview = normal;
	
	DebugMode(dt);
	
		

	// Recalculate matrix -------------
	CalculateViewMatrix();
	

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

// -----------------------------------------------------------------
float* Camera::GetViewMatrix()
{
	return &ViewMatrix;
}



void Camera::DebugMode(float dt)
{
	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	vec3 newPos(0, 0, 0);
	float speed = 100.0f * dt;
	
	if (app->input->GetKey(GLFW_KEY_LEFT_SHIFT) == KEY_REPEAT)
		speed = 12.0f * dt;

	if (app->input->GetKey(GLFW_KEY_R) == KEY_REPEAT) newPos.y += speed;
	if (app->input->GetKey(GLFW_KEY_F) == KEY_REPEAT) newPos.y -= speed;

	if (app->input->GetKey(GLFW_KEY_W) == KEY_REPEAT) newPos -= Z * speed;
	if (app->input->GetKey(GLFW_KEY_S) == KEY_REPEAT) newPos += Z * speed;


	if (app->input->GetKey(GLFW_KEY_A) == KEY_REPEAT) newPos -= X * speed;
	if (app->input->GetKey(GLFW_KEY_D) == KEY_REPEAT) newPos += X * speed;

	Position += newPos;
	Reference += newPos;

	// Mouse motion ----------------
	
	if(app->input->GetMouseButtonDown(GLFW_MOUSE_BUTTON_1) == KEY_REPEAT)
	{
		int dx = 0;
		int dy = 0;
		app->input->GetMousePosition(dx, dy);
			

		float Sensitivity = 0.25f;
		
		Position -= Reference;

		if (dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;

			X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		}

		if (dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;

			Y = rotate(Y, DeltaY, X);
			Z = rotate(Z, DeltaY, X);

			if (Y.y < 0.0f)
			{
				Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = cross(Z, X);
			}
		}

		Position = Reference + Z * length(Position);
	}

}

// -----------------------------------------------------------------
void Camera::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}