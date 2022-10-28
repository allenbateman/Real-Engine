#include "Inspector.h"
#include "Tag.h"
#include "Camera.h"
#include "Transform.h"
#include "glmath.h"


Inspector::Inspector(int _id, bool active) : Panel(_id, active)
{
	name.Create("Inspector");
}

Inspector::~Inspector()
{
}

void Inspector::Init()
{

}

void Inspector::Update()
{
	if (!active)
		return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(2.0f, 2.0f));
	ImGui::SetNextWindowSize(ImVec2{ 720,720 }, ImGuiCond_FirstUseEver);
	if (ImGui::Begin(name.GetString(), &active))
	{
		OnHovered();
		DrawComponents(context);
	}
	ImGui::End();
	ImGui::PopStyleVar();
}

void Inspector::DrawComponents(Entity entity)
{
	if (entity == -1) return;

	if (app->entityComponentSystem.HasComponent<TagComponent>(entity))
	{
		auto& tag = app->entityComponentSystem.GetComponent<TagComponent>(entity);
		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, tag.c_str());
		if (ImGui::InputText("Name", buffer, sizeof(buffer)))
		{
			tag = std::string(buffer);
		}
	}
	if (app->entityComponentSystem.HasComponent<Transform>(entity))
	{
		if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
		{
			auto& transform = app->entityComponentSystem.GetComponent<Transform>(entity);
		
			float p[] = { transform.position.x,transform.position.y,transform.position.z };
		
			if (ImGui::DragFloat3("Position", p, 0.5f));

			ImGui::TreePop();
		}


	}
	if (app->entityComponentSystem.HasComponent<Camera>(entity))
	{
		if (ImGui::TreeNodeEx((void*)typeid(Camera).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
		{
			auto& cam = app->entityComponentSystem.GetComponent<Camera>(entity);
			auto& fov = cam.fieldOfView;

			if (ImGui::DragFloat("Fov", &fov, 0.1f, cam.minFieldOfView, cam.maxFieldOfView));
			{
				app->eventSystem->PostEvent(&fovChange);
			}

			ImGui::TreePop();
		}
	}

}
