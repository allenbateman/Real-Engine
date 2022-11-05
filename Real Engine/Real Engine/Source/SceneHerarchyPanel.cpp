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

	ImGui::Begin("Hierarchy");

	std::vector<GameObject> gameObjects = app->sceneManager->currentScene->gameObejects;

	for(auto& go : gameObjects)
	{
		DrawGONode(go);
	}
	ImGui::End();
	//wait until all data updated to delete
	if (DeletedEntity)
	{
		app->entityComponentSystem.DestroyEntity(toDelete);
	}
}

void SceneHerarchyPanel::DrawGONode(GameObject go)
{
	Entity entity = go.id;

	auto& tagComponent = app->entityComponentSystem.GetComponent<TagComponent>(entity);
	ImGuiTreeNodeFlags flags = ((entitySelectionContext == entity) ? ImGuiTreeNodeFlags_OpenOnArrow : 0) | ImGuiTreeNodeFlags_Selected;
	bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tagComponent.c_str());
	
	
	
	if (ImGui::IsItemClicked())
	{
		entitySelectionContext = entity;
		inspector->context = entitySelectionContext;
	}
	if (ImGui::BeginDragDropSource()) {
		ImGui::SetDragDropPayload(payloadDragDrop, &entity, sizeof(entity));
		ImGui::Text(go.name.c_str());
		ImGui::EndDragDropSource();
	}
	if (ImGui::BeginDragDropTarget()) {
		const ImGuiPayload* obj = ImGui::AcceptDragDropPayload(payloadDragDrop);
		if (obj != nullptr)
		{
			
			std::cout << "Drop recived from: "<< obj->Data;
		}

		ImGui::EndDragDropTarget();
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
