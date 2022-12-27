#include "Inspector.h"

#include "glmath.h"
#include "Application.h"

#include "Tag.h"
#include "Camera.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"

#include "GameObject.h"


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
			

			mat4x4 currentTransformation = transform.localMatrix;


			vec3 pos = transform.LocalPosition();
			vec3 rot = transform.LocalRotation();
			vec3 scale = transform.LocalScale();
				
			float* p[] = { &pos.x,&pos.y,&pos.z };
			float* r[] = { &rot.x,&rot.y,&rot.z };
			float* s[] = { &scale.x,&scale.y,&scale.z };


		//translate matrix * rotation matrix * scale matrix = final matrix
			
			if (ImGui::DragFloat3("Position", (*p), 0.1f) )
			{
				transform.Translate(pos.x, pos.y, pos.z);
			}
			else if (ImGui::DragFloat3("Rotation", (*r), 0.1f))
			{
			//	transform.Rotate(rot.x,rot.y,rot.z);
				//if (*r[0] != rot.x)
				//	transform.Rotate(rot.x, vec3(1, 0, 0));
				//if(*r[1] != rot.y)
				//	transform.Rotate(rot.y, vec3(0, 1, 0));
				//if(*r[2] != rot.z)
				//	transform.Rotate(rot.z, vec3(0, 0, 1));
			}
			else if (ImGui::DragFloat3("Scale", (*s), 0.1f))
			{
				transform.Scale(scale.x, scale.y, scale.z);
			}

			//mat4x4 newTransformation;
			//bool OnChange = false;
			//if (ImGui::DragFloat3("Position", (*p), 0.1f) || ImGui::DragFloat3("Rotation", (*r), 0.1f) || ImGui::DragFloat3("Scale", (*s), 0.1f))
			//{
			//	newTransformation = newTransformation.GetMatrixFromTransform(pos, rot, scale);
			//	OnChange = true;
			//}

			//if(OnChange)
			//	transform.ApplyTransformation(newTransformation);
			
			if (transform.parent != nullptr)
			{
				GameObject* parent = transform.parent->owner;
				TagComponent pt = app->entityComponentSystem.GetComponent<TagComponent>(parent->id);
				ImGui::Text(pt.c_str());
			}
			
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
	if (app->entityComponentSystem.HasComponent<Mesh>(entity))
	{
		if (ImGui::TreeNodeEx((void*)typeid(Mesh).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Mesh"))
		{
			auto& mesh = app->entityComponentSystem.GetComponent<Mesh>(entity);
			ImGui::Text("Vertices %d", mesh.vertices.size());
			ImGui::Text("Indices %d", mesh.indices.size());
			

			ImGui::TreePop();
		}
	}
	if (app->entityComponentSystem.HasComponent<Material>(entity))
	{
		if (ImGui::TreeNodeEx((void*)typeid(Material).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Material"))
		{
			auto& material = app->entityComponentSystem.GetComponent<Material>(entity);
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			for (unsigned int i = 0; i < material.textures.size(); i++) 
			{

				std::string number;

				std::string name = material.textures[i].type;
				if (name == "texture_diffuse")
					number = std::to_string(diffuseNr++);
				else if (name == "texture_specular")
					number = std::to_string(specularNr++);

				ImGui::Text((name + number).c_str());
				ImGui::Image((ImTextureID)material.textures.at(i).id, ImVec2{ 250,250 });			
			}
		
			ImGui::TreePop();
		}
	}
}
