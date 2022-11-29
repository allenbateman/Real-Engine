#pragma once
#include "Application.h"
#include "EntityComponentSystem.h"
#include "Camera.h"
#include "Module.h"
#include "System.h"
#include "EditorComponent.h"


class CameraUpdater : public Module, public System
{
public:
	CameraUpdater() {};
	~CameraUpdater() {};

	bool Update(float dt)
	{

		for (auto& ent : entities)
		{
			if (app->entityComponentSystem.HasComponent<EditorComponent>(ent)) return true;
			auto& camera = app->entityComponentSystem.GetComponent<Camera>(ent);
			auto& transform = app->entityComponentSystem.GetComponent<Transform>(ent);

			camera.Position = transform.position;
			
			
		}
		return true;
	}
};