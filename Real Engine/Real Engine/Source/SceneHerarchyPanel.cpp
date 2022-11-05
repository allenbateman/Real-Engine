#include "SceneHerarchyPanel.h"
#include "Application.h"
#include "UiSystem.h"
#include "Tag.h"
#include "SceneManager.h"
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
	DeletedEntity = false;

	ImGui::Begin("Herarchy");
	for(auto& go : app->sceneManager->currentScene->gameObejects)
	{
		DrawEntityNode(go.id);
	}
	ImGui::End();
	//wait until all data updated to delete
	if (DeletedEntity)
	{
		app->entityComponentSystem.DestroyEntity(toDelete);
	}
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
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("Delete Entity"))
		{
			DeletedEntity = true;
			toDelete = entity;
		}
		ImGui::EndPopup();
	}
	if (opened)
	{
		ImGui::TreePop();
	}
}
