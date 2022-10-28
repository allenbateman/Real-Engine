#include "SceneHerarchyPanel.h"
#include "Application.h"
#include "Transform.h"
#include "Tag.h"
SceneHerarchyPanel::SceneHerarchyPanel(int _id, bool active)
{
}

SceneHerarchyPanel::~SceneHerarchyPanel()
{
}

void SceneHerarchyPanel::Init()
{

}

void SceneHerarchyPanel::Update()
{
	ImGui::Begin("Herarchy");
	
	Entity entities = app->entityComponentSystem.GetEntities();
	ComponentType ct = 1;
	for(Entity i = 0; i < entities; i++)
	{
		DrawEntityNode(i);
	}
	ImGui::End();
}

void SceneHerarchyPanel::DrawEntityNode(Entity entity)
{
	auto& tagComponent = app->entityComponentSystem.GetComponent<TagComponent>(entity);
	ImGuiTreeNodeFlags flags = ((entitySelectionContext == entity) ? ImGuiTreeNodeFlags_OpenOnArrow : 0) | ImGuiTreeNodeFlags_Selected;
	bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tagComponent.c_str());
	if (ImGui::IsItemClicked())
	{
		entitySelectionContext = entity;
		inspector->context = entitySelectionContext;
	}
	if (opened)
	{
		ImGui::TreePop();
	}
}
