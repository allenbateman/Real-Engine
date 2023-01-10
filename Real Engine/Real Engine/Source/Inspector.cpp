#include "Inspector.h"

#include "glmath.h"
#include "Application.h"

#include "Tag.h"
#include "Camera.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"

#include "GameObject.h"
#include "UiSystem.h"

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
			//vec3 pos = transform.localPosition;
			//vec3 rot = transform.localRotation;
			//vec3 scale = transform.localScale;
				
			float* p[] = { &pos.x,&pos.y,&pos.z };
			float* r[] = { &rot.x,&rot.y,&rot.z };
			float* s[] = { &scale.x,&scale.y,&scale.z };


		//translate matrix * rotation matrix * scale matrix = final matrix
			
			if (ImGui::DragFloat3("Position", (*p), 0.1f) )
			{
				transform.Translate(pos.x, pos.y, pos.z);
			}
			if (ImGui::DragFloat3("Rotation", (*r), 0.1f))
			{
				//transform.Rotate(rot.x,rot.y,rot.z);
				if (*r[0] != rot.x)
					transform.Rotate(rot.x, vec3(1, 0, 0));
				else if(*r[1] != rot.y)
					transform.Rotate(rot.y, vec3(0, 1, 0));
				else if(*r[2] != rot.z)
					transform.Rotate(rot.z, vec3(0, 0, 1));
			}
			if (ImGui::DragFloat3("Scale", (*s), 0.1f))
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

			if (mesh.resource.get() == nullptr)
			{
				ImGui::Text("Pointer to resource is empty"); 
				ListAvailableResources(Resource::Type::Mesh, mesh.resource);

			}

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
			if (material.resource.get() == nullptr)
			{
				ImGui::Text("Pointer to resource is empty");

				ListAvailableResources(Resource::Type::Material, material.resource);
			}
			else
			{
				if (material.textures.size() == 0)
				{
					ImGui::Text("Material has no textue assigned");
					//auto tex = app->resourceManager->GetResourceListOfType(Resource::Type::Texture);
					SelectTexture(material);
				}
			}
			ImGui::TreePop();
		}
	}
	if (ImGui::Button("Add component"))
	{
		SearchTabOpen = true;
	}
	if (SearchTabOpen)
		ShowSearchField(entity);
}

void Inspector::ShowSearchField(Entity entity)
{

	const char* items[] = { "Mesh","Material","Texture" };
	const char* current_item =NULL;

	if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < IM_ARRAYSIZE(items); n++)
		{
			bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
			if (ImGui::Selectable(items[n], is_selected))
			{
				current_item = items[n];
				
				ImGui::SetItemDefaultFocus();
				SearchTabOpen = false;
				switch (n)
				{
				case 0:
					if (!app->entityComponentSystem.HasComponent<Mesh>(entity))
					{
						app->entityComponentSystem.AddComponent(entity, Mesh{});
						Debug::Log("Added component");
					}
					else
					{
						Debug::Log("Game object already has a Mesh");
					}
					break;
				case 1:
					if (!app->entityComponentSystem.HasComponent<Material>(entity))
					{
						app->entityComponentSystem.AddComponent(entity, Material{});
						Debug::Log("Added component");
					}
					else
					{
						Debug::Log("Game object already has a Material");
					}
					break;	
				//case 2:
				//	if (!app->entityComponentSystem.HasComponent<Texture>(entity))
				//	{
				//		app->entityComponentSystem.AddComponent(entity, Texture());
				//		Debug::Log("Added component");
				//	}
				//	else {
				//		Debug::Log("Game object already has a Texture");
				//	}
				//	break;

				}
				
			}   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
		}
		ImGui::EndCombo();
	}

}

void Inspector::ListAvailableResources(Resource::Type type, shared_ptr<Resource>& resource)
{
	const auto  listBoxSize = ImVec2(310, 260);
	auto result = app->resourceManager->GetResourceListOfType(type);
	const char** items = new const char*[result.size()];
	int currentItem = 0;
	const char* current_item = NULL;
	for (int i = 0; i< result.size(); i++)
	{
		items[i] = result.at(i)->name.c_str();
	}

	if (ImGui::BeginCombo("##Resources", current_item)) {

		if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_DownArrow))) {
			if (currentItem < result.size() - 1) { ++currentItem; }
		}
		if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_UpArrow))) {
			if (currentItem > 0) { --currentItem; }
		}

		for (int n = 0; n < result.size(); ++n) {
			const bool is_selected = (currentItem == n);
			if (ImGui::Selectable(items[n], is_selected)) 
			{ 
				currentItem = n; 
				ImGui::SetItemDefaultFocus();
				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected) {

					resource = result.at(n);
				}
			}
		}
		ImGui::EndCombo();
	}
}

void Inspector::SelectTexture(Material& material)
{
	auto result = app->resourceManager->GetResourceListOfType(Resource::Type::Texture);
	const char** items = new const char* [result.size()];
	int currentItem = 0;
	const char* current_item = NULL;
	for (int i = 0; i < result.size(); i++)
	{
		items[i] = result.at(i)->name.c_str();
	}

	if (ImGui::BeginCombo("##Texture", current_item)) {

		for (int n = 0; n < result.size(); ++n) {
			const bool is_selected = (currentItem == n);
			if (ImGui::Selectable(items[n], is_selected))
			{
				currentItem = n;
				ImGui::SetItemDefaultFocus();
				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected) {

					auto resource = result.at(n); resource->GetAssetPath();
					shared_ptr<ResourceMaterial> rm = dynamic_pointer_cast<ResourceMaterial>(material.resource);
					shared_ptr<ResourceTexture> rt = dynamic_pointer_cast<ResourceTexture>(resource);
					rt->Load();
					material.textures.push_back(rt->texture);
					std::pair<std::string, shared_ptr<ResourceTexture> > t{ resource->GetAssetPath().string(), rt };
					rm->resourcesTexture.push_back(t);
		
				}
			}


		}
		ImGui::EndCombo();

	}

}
