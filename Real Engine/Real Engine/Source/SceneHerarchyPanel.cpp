#include "SceneHerarchyPanel.h"
#include "Application.h"
#include "UiSystem.h"
#include "Tag.h"
#include "SceneManager.h"
#include "Transform.h"
#include "ImGui/imgui_internal.h"
#include "EventSystem.h"

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
	ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

	if (ImGui::BeginPopupContextWindow())
		{

			if (ImGui::BeginMenu("Create"))
			{

				if (ImGui::MenuItem("Empty"))
				{
					goCreationEvent.goType = gameObjectType::EMPTY;
					app->eventSystem->PostEvent(&goCreationEvent);
				}

				if (ImGui::MenuItem("Cube"))
				{
					goCreationEvent.goType = gameObjectType::CUBE;
					app->eventSystem->PostEvent(&goCreationEvent);
				}

				if (ImGui::MenuItem("Sphere"))
				{
					goCreationEvent.goType = gameObjectType::SPHERE;
					app->eventSystem->PostEvent(&goCreationEvent);
				}

				ImGui::EndMenu();
			}
				
			ImGui::EndPopup();
		}
		ImGui::PopItemFlag();


	Scene* currentScene = app->sceneManager->currentScene;
	std::vector<GameObject> gameObjects = currentScene->gameObejects;
	DrawGONode(currentScene->origin);

	

	ImGui::End();
	//wait until all data updated to delete
	if (DeletedEntity)
	{
		currentScene->RemoveEntity(toDelete);
	}
}

void SceneHerarchyPanel::DrawGONode(GameObject go)
{
	Transform* t = go.GetComponent<Transform>().parent;
	Transform test = go.GetComponent<Transform>();
	
	Entity entity = go.id;

	auto& tagComponent = app->entityComponentSystem.GetComponent<TagComponent>(entity);
	ImGuiTreeNodeFlags flags = ((entitySelectionContext == entity) ? ImGuiTreeNodeFlags_OpenOnArrow : 0) |((entity == 0) ? 0: ImGuiTreeNodeFlags_Selected );
	
	if (entity == 0)
		ImGui::SetNextItemOpen(true);
	
	bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tagComponent.c_str());

	
	if (ImGui::IsItemClicked())
	{
		entitySelectionContext = entity;
		inspector->context = entitySelectionContext;
	}
	if (ImGui::BeginDragDropSource()) {
		ImGui::SetDragDropPayload(payloadDragDrop, &go, sizeof(GameObject));
		ImGui::Text(go.name.c_str());
		ImGui::EndDragDropSource();
	}
	if (ImGui::BeginDragDropTarget()) {
		const ImGuiPayload* obj = ImGui::AcceptDragDropPayload(payloadDragDrop);
		if (obj != nullptr)
		{
			//get go dragged to the new parent
			GameObject drop = *(const GameObject*)obj->Data; 
			

			//check that the parent is the scene root
			Transform* tScene = go.GetComponent<Transform>().parent;
			if (tScene == nullptr)
			{
				// add droped go as a child of the target go
				if (go.GetComponent<Transform>().AddChild(&drop.GetComponent<Transform>()))
				{
					//get dragged parent and remove dragged go as child
					Transform* p = drop.GetComponent<Transform>().parent;
					p->RemoveChild(drop.GetComponent<Transform>());
					//Set droped go new parent
					drop.GetComponent<Transform>().SetParent(&go.GetComponent<Transform>());
				}
			}
			else
			{
				//other parent 
				GameObject myparent = *go.GetComponent<Transform>().parent->owner;

				//check that that the dragged obj os not the parent of the target
				if (myparent != drop)
				{
					// add droped go as a child of the target go
					if (go.GetComponent<Transform>().AddChild(&drop.GetComponent<Transform>()))
					{
						//get dragged parent and remove dragged go as child
						Transform* p = drop.GetComponent<Transform>().parent;
						p->RemoveChild(drop.GetComponent<Transform>());
						//Set droped go new parent
						drop.GetComponent<Transform>().SetParent(&go.GetComponent<Transform>());
					}
				}
			}
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
		if (go.GetComponent<Transform>().childs.size() > 0)
		{
			vector<Transform*> childs = go.GetComponent<Transform>().childs;

			for (Transform* i : childs)
			{
				DrawGONode(*i->owner);
			}		
		}
		ImGui::TreePop();
	}
}
