#include "Application.h"
#include "Camera.h"
#include "Input.h"
#include "Window.h"
#include "EventSystem.h"
#include "PanelIDs.h"

Camera::Camera(bool isActive) : Module(isActive)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 5.0f, 30.0f);
	Reference = vec3(0.0f, 5.0f, 0.0f);
	
}

Camera::~Camera()
{}

// -----------------------------------------------------------------
bool Camera::Start()
{
	
	bool ret = true;

	freecam = false;

	app->eventSystem->SubcribeModule(this, KEY_INPUT);
	app->eventSystem->SubcribeModule(this, MOUSE_INPUT);
	app->eventSystem->SubcribeModule(this, MOUSE_POSITION);
	app->eventSystem->SubcribeModule(this, ON_PANEL_FOCUS);

	return ret;
}

// -----------------------------------------------------------------
bool Camera::CleanUp()
{
	

	return true;
}

bool Camera::HandleEvent(Event* e)
{
	switch (e->type)
	{
	case ON_PANEL_FOCUS:
	{
		OnPanelFocus* Pf = dynamic_cast<OnPanelFocus*>(e);
		if (Pf->id == eViewport)
		{
			//cout << "viewpor focus: "<<Pf->focused<<endl;
			onFocus = Pf->focused;
		}
	}
		break;
	case KEY_INPUT:
	{
		if (!onFocus)
			break;
		vec3 newPos(0, 0, 0);
		KeyInput* ki = dynamic_cast<KeyInput*>(e);

		if (ki->key == GLFW_KEY_F && ki->keyState == KEY_REPEAT)newPos -= Y * cameraSpeed;
		if (ki->key == GLFW_KEY_R && ki->keyState == KEY_REPEAT)newPos += Y * cameraSpeed;
		if (ki->key == GLFW_KEY_W && ki->keyState == KEY_REPEAT)newPos -= Z * cameraSpeed;
		if (ki->key == GLFW_KEY_S && ki->keyState == KEY_REPEAT)newPos += Z * cameraSpeed;
		if (ki->key == GLFW_KEY_A && ki->keyState == KEY_REPEAT)newPos -= X * cameraSpeed;
		if (ki->key == GLFW_KEY_D && ki->keyState == KEY_REPEAT)newPos += X * cameraSpeed;

		if (ki->key == GLFW_KEY_T && ki->keyState == KEY_REPEAT) ResetCameraRotation();
		if (ki->key == GLFW_KEY_G && ki->keyState == KEY_REPEAT) ResetCameraPosition();


		Move(newPos);
	}
		break;
	case MOUSE_INPUT:
	{
		if (!onFocus)
			break;
		mouseLeft = false;
		mouseRight = false;
		MouseInput* mo = dynamic_cast<MouseInput*>(e);

		if (mo->key == GLFW_MOUSE_BUTTON_1 && mo->keyState == KEY_DOWN)mouseLeft = true;
		if (mo->key == GLFW_MOUSE_BUTTON_2 && mo->keyState == KEY_DOWN)mouseRight = true;

		if (mo->key == GLFW_MOUSE_BUTTON_1 && mo->keyState == KEY_UP);
		if (mo->key == GLFW_MOUSE_BUTTON_2 && mo->keyState == KEY_UP);
			
	}

		break;
	case MOUSE_POSITION:
	{
		if (!onFocus)
			break;
		MousePosition* mo = dynamic_cast<MousePosition*>(e);
		
		if (mouseLeft)
		{

			float rotationX = 0.0f;	
			rotationX = mo->dx * rotationSpeed.x;
		
			X = rotate(X, rotationX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, rotationX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, rotationX, vec3(0.0f, 1.0f, 0.0f));
			
			
			
			float rotationY = 0.0f;
			rotationY = mo->dy * rotationSpeed.y;

			
			Y = rotate(Y, rotationY, X);
			Z = rotate(Z, rotationY, X);

			if (Y.y < 0.0f)
			{
				if (Z.y > 0.0f) Z.y = 1.0f;
				if (Z.y > 0.0f) Z.y = -1.0f;
				Y = cross(Z, X);
			}
			

			CalculateViewMatrix();

		}

		
		if (mouseRight)
		{
			float rotationX = 0.0f;
			rotationX = mo->dx * -rotationSpeed.x;

			Position -= Reference;

			X = rotate(X, rotationX, vec3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, rotationX, vec3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, rotationX, vec3(0.0f, 1.0f, 0.0f));



			float rotationY = 0.0f;
			rotationY = mo->dy * -rotationSpeed.y;


			Y = rotate(Y, rotationY, X);
			Z = rotate(Z, rotationY, X);

			if (Y.y < 0.0f)
			{
				if (Z.y > 0.0f) Z.y = 1.0f;
				if (Z.y > 0.0f) Z.y = -1.0f;
				Y = cross(Z, X);
			}


			Position = Reference + Z * length(Position);

			CalculateViewMatrix();
		}
	}
		break;
	default:
		break;
	}
	return true;
}

// -----------------------------------------------------------------
bool Camera::Update(float dt)
{
	
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
void Camera::SetReference(vec3 myReference)
{
	Reference = myReference;
}
// -----------------------------------------------------------------
float* Camera::GetViewMatrix()
{
	return &ViewMatrix;
}

float* Camera::GetProjectionMatrix()
{
	return nullptr;
}



void Camera::DebugMode(float dt)
{
	
	
}

// -----------------------------------------------------------------
void Camera::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}