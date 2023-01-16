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
				
			float* p[] = { &pos.x,&pos.y,&pos.z };
			float* r[] = { &rot.x,&rot.y,&rot.z };
			float* s[] = { &scale.x,&scale.y,&scale.z };


		//translate matrix * rotation matrix * scale matrix = final matrix
			vec3 tmp = rot;
			if (ImGui::DragFloat3("Position", (*p), 0.1f) )
			{
				transform.Translate(pos.x, pos.y, pos.z);
			}
			if (ImGui::DragFloat3("Rotation", (*r), 0.1f))
			{
				if (*r[0] != tmp.x)
					transform.Rotate(rot.x, vec3(1, 0, 0));
				else if(*r[1] != tmp.y)
					transform.Rotate(rot.y, vec3(0, 1, 0));
				else if(*r[2] != tmp.z)
					transform.Rotate(rot.z, vec3(0, 0, 1));
			}
			if (ImGui::DragFloat3("Scale", (*s), 0.1f))
			{
				transform.Scale(scale.x, scale.y, scale.z);
			}
			
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
			if (mesh.resource.get() == nullptr)
			{
				ImGui::Text("Pointer to resource is empty");
				auto resource = SelectResource("select mesh",Resource::Type::Mesh);
				if (resource != nullptr)
				{
					mesh.resource = std::static_pointer_cast<ResourceMesh>(resource);
					mesh.resource->Load();
				}
				
			}
			else {
				ImGui::Text("Name: %s", mesh.resource->name.c_str());
				auto resource = SelectResource("change mesh", Resource::Type::Mesh);
				if (resource != nullptr)
				{
					mesh.resource = std::static_pointer_cast<ResourceMesh>(resource);
					mesh.resource->Load();
				}
				ImGui::Text("Vertices %d", mesh.resource->vertices.size());
				ImGui::Text("Indices %d", mesh.resource->indices.size());
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

			if (material.resource.get() == nullptr)
			{
				ImGui::Text("Pointer to resource is empty");
				auto resource = SelectResource("select material",Resource::Type::Material);
				if (resource != nullptr)
				{
					material.resource = static_pointer_cast<ResourceMaterial>(resource);
					material.resource->Load();
				}
				
			}
			else
			{
				ImGui::Text("material: %s", material.resource->name.c_str());
				auto resource = SelectResource("change material", Resource::Type::Material);
				if (resource != nullptr)
				{
					material.resource = static_pointer_cast<ResourceMaterial>(resource);
					material.resource->Load();
				}
				ImGui::Dummy(ImVec2(0.0f, 20.0f));
				if (material.resource->shader == nullptr)
				{
					auto resource = SelectResource("select shader", Resource::Type::Shader);
					if (resource != nullptr)
					{
						material.resource->shader = static_pointer_cast<ResourceShader>(resource);
						material.resource->shader->Load();
						material.resource->shader->LoadActiveUniforms();
					}
				}
				else {
					ImGui::Text("shader: %s", material.resource->shader->name.c_str());
					auto resource = SelectResource("change shader", Resource::Type::Shader);
					if (resource != nullptr)
					{
						material.resource->shader = static_pointer_cast<ResourceShader>(resource);
						material.resource->shader->Load();
						material.resource->shader->LoadActiveUniforms();
					}
					material.resource->shader->UpdateUniformValues();
				}
				ImGui::Dummy(ImVec2(0.0f, 20.0f));
				if (material.resource->textures.empty())
				{
					ImGui::Text("Material has no textures...");
					SelectTexture(material, 0);
				}	
				for (unsigned int i = 0; i < material.resource->textures.size(); i++)
				{
					//draw the textures
					std::string number;
					std::string name = material.resource->textures[i].second->type;
					if (name == "texture_diffuse")
						number = std::to_string(diffuseNr++);
					else if (name == "texture_specular")
						number = std::to_string(specularNr++);

					ImGui::Text((name + number).c_str());
					SelectTexture(material, i);
					ImGui::Image((ImTextureID)material.resource->textures.at(i).second->id, ImVec2{ 250,250 });

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
	const char* current_item = "components...";

	if (ImGui::BeginCombo("##Resources", current_item)) // The second parameter is the label previewed before opening the combo.
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
					

				}
				
			}
		}
		ImGui::EndCombo();
	}

}

shared_ptr<Resource> Inspector::SelectResource(const char* text,Resource::Type type)
{
	const auto  listBoxSize = ImVec2(310, 260);
	auto result = app->resourceManager->GetResourceListOfType(type);
	const char** items = new const char* [result.size()];
	int currentItem = -1;
	for (int i = 0; i < result.size(); i++)
	{
		items[i] = result.at(i)->name.c_str();
	}

	if (ImGui::BeginCombo(text, text)) {

		for (int n = 0; n < result.size(); ++n) {
			bool is_selected = false;
			if (ImGui::Selectable(items[n], is_selected))
			{
				currentItem = n;
			}
			is_selected = (currentItem == n);
			if (is_selected) {
				ImGui::SetItemDefaultFocus();
				ImGui::EndCombo();
				return result.at(n);
			}
		}
		ImGui::EndCombo();
	}
	return nullptr;
}

void Inspector::SelectTexture(Material& material, unsigned int id)
{
	auto result = app->resourceManager->GetResourceListOfType(Resource::Type::Texture);
	const char** items = new const char* [result.size()];
	int currentItem = -1;
	for (unsigned int i = 0; i < result.size(); i++)
	{
		items[i] = result.at(i)->name.c_str();
	}

	if (ImGui::BeginCombo("##Texture", "change texture")) {

		for (unsigned int n = 0; n < result.size(); ++n) {
			bool is_selected = false;
			if (ImGui::Selectable(items[n], is_selected))
			{
				currentItem = n;
			}

			is_selected = (currentItem == n);
			if (is_selected) {
				ImGui::SetItemDefaultFocus();
				auto resource = result.at(n);

				if (material.resource->textures.empty())
				{
					shared_ptr<ResourceTexture> rt = dynamic_pointer_cast<ResourceTexture>(resource);
					rt->Load();
					pair<std::string, shared_ptr<ResourceTexture>> texture(rt->GetAssetPath().string(),rt);
					material.resource->textures.push_back(texture);
				}
				else {
					shared_ptr<ResourceTexture> rt = dynamic_pointer_cast<ResourceTexture>(resource);
					rt->Load();
					pair<std::string, shared_ptr<ResourceTexture>> texture(rt->GetAssetPath().string(), rt);
					material.resource->textures.at(id) = texture;
				}
			}
		}
		ImGui::EndCombo();
	}
}

