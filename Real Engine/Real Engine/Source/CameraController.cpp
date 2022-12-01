#include "CameraController.h"
#include "Application.h"
#include "Input.h"
#include "Transform.h"
#include "Camera.h"
#include "PanelIDs.h"
#include "UiSystem.h"
CameraController::CameraController()
{
}
CameraController::~CameraController()
{
}

bool CameraController::Start()
{

	app->eventSystem->SubscribeModule(this, KEY_INPUT);
	app->eventSystem->SubscribeModule(this, MOUSE_INPUT);
	app->eventSystem->SubscribeModule(this, MOUSE_POSITION);
	app->eventSystem->SubscribeModule(this, ON_PANEL_FOCUS);
	app->eventSystem->SubscribeModule(this, MOUSE_SCROLL);

	return true;
}

bool CameraController::Update(float dt)
{
	for (auto& ent : entities)
	{
		auto& transform = app->entityComponentSystem.GetComponent<Transform>(ent);
		auto& camera = app->entityComponentSystem.GetComponent<Camera>(ent);
	}
	return true;
}

void CameraController::HandleEvent(Event* e)
{
	for (auto& ent : entities)
	{
		auto& transform = app->entityComponentSystem.GetComponent<Transform>(ent);
		auto& camera = app->entityComponentSystem.GetComponent<Camera>(ent);
		switch (e->type)
		{
		case KEY_INPUT:
		{
			
		
			if (!camera.GetFocus())
			{
				camera.altKey = false;
				break;
			}

			vec3 newPos(0, 0, 0);
			KeyInput* ki = dynamic_cast<KeyInput*>(e);

			if (ki->keys[GLFW_KEY_LEFT_ALT] == KEY_DOWN) camera.altKey = true;

			if (camera.mouseRight)
			{

				int speedMulti = 1;
				if (ki->keys[GLFW_KEY_LEFT_SHIFT] == KEY_REPEAT) speedMulti = 2;

				if (ki->keys[GLFW_KEY_W] == KEY_REPEAT)newPos -= camera.Z * camera.cameraSpeed * speedMulti;
				if (ki->keys[GLFW_KEY_S] == KEY_REPEAT)newPos += camera.Z * camera.cameraSpeed * speedMulti;				
				if (ki->keys[GLFW_KEY_A] == KEY_REPEAT)newPos -= camera.X * camera.cameraSpeed * speedMulti;
				if (ki->keys[GLFW_KEY_D] == KEY_REPEAT)newPos += camera.X * camera.cameraSpeed * speedMulti;
			}

			if (ki->keys[GLFW_KEY_LEFT_ALT] == KEY_UP) camera.altKey = false;

			if (ki->keys[GLFW_KEY_T] == KEY_REPEAT) camera.ResetCameraRotation();
			if (ki->keys[GLFW_KEY_G] == KEY_REPEAT)	camera.ResetCameraPosition();

			if (ki->keys[GLFW_KEY_F] == KEY_DOWN) camera.Focus(camera.target);

			camera.Move(newPos);
			
		}
		break;
		case MOUSE_INPUT:
		{
			camera.mouseLeft = false;
			camera.mouseRight = false;
			if (!camera.GetFocus())
			{
				camera.mouseRight = false;
				break;
			}

			MouseInput* mo = dynamic_cast<MouseInput*>(e);

			if (mo->key == GLFW_MOUSE_BUTTON_1 && mo->keyState == KEY_DOWN)camera.mouseLeft = true;
			if (mo->key == GLFW_MOUSE_BUTTON_2 && mo->keyState == KEY_DOWN)camera.mouseRight = true;

		}

		break;
		case MOUSE_POSITION:
		{
			if (!camera.GetFocus())
				break;
			MousePosition* mo = dynamic_cast<MousePosition*>(e);

			if (camera.mouseRight)
			{

				float rotationX = 0.0f;
				rotationX = mo->dx * -camera.rotationSpeed.x;

				camera.X = rotate(camera.X, rotationX, vec3(0.0f, 1.0f, 0.0f));
				camera.Y = rotate(camera.Y, rotationX, vec3(0.0f, 1.0f, 0.0f));
				camera.Z = rotate(camera.Z, rotationX, vec3(0.0f, 1.0f, 0.0f));

				float rotationY = 0.0f;
				rotationY = mo->dy * -camera.rotationSpeed.y;

				camera.Y = rotate(camera.Y, rotationY, camera.X);
				camera.Z = rotate(camera.Z, rotationY, camera.X);

				if (camera.Y.y < 0.0f)
				{
					if (camera.Z.y > 0.0f) camera.Z.y = 1.0f;
					if (camera.Z.y > 0.0f) camera.Z.y = -1.0f;
					camera.Y = cross(camera.Z, camera.X);
				}

				camera.CalculateViewMatrix();
			}

			if (camera.altKey && camera.mouseLeft)
			{
				float rotationX = 0.0f;
				rotationX = mo->dx * -camera.rotationSpeed.x;

				camera.Position -= camera.Reference;

				camera.X = rotate(camera.X, rotationX, vec3(0.0f, 1.0f, 0.0f));
				camera.Y = rotate(camera.Y, rotationX, vec3(0.0f, 1.0f, 0.0f));
				camera.Z = rotate(camera.Z, rotationX, vec3(0.0f, 1.0f, 0.0f));

				float rotationY = 0.0f;
				rotationY = mo->dy * -camera.rotationSpeed.y;

				camera.Y = rotate(camera.Y, rotationY, camera.X);
				camera.Z = rotate(camera.Z, rotationY, camera.X);

				if (camera.Y.y < 0.0f)
				{
					if (camera.Z.y > 0.0f) camera.Z.y = 1.0f;
					if (camera.Z.y > 0.0f) camera.Z.y = -1.0f;
					camera.Y = cross(camera.Z, camera.X);
				}

				camera.Position = camera.Reference + camera.Z * length(camera.Position);

				camera.CalculateViewMatrix();
			}
		}
		break;
		case MOUSE_SCROLL:
		{
			if (!camera.GetFocus())
				break;
			MouseScroll* ms = dynamic_cast<MouseScroll*>(e);
			camera.ChangeFieldOfView(ms->dy);
			
		}break;

		default:
			break;
		}
	}
}
