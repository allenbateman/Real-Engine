#include "ResourcesPanel.h"
#include "Resource.h"


ResourcesPanel::ResourcesPanel(int _id, bool isActive) : Panel( _id, isActive)
{
	name.Create("Resources");
}


ResourcesPanel::~ResourcesPanel()
{
}

void ResourcesPanel::Begin()
{
}

void ResourcesPanel::End()
{
}

void ResourcesPanel::Init()
{
	window_flags = ImGuiConfigFlags_DockingEnable;
	borderOffset = 0;
}

void ResourcesPanel::Update()
{
	if (!active) return;
	// render your GUI
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2{ 250,350 }, ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Resources"), NULL, window_flags)
	{
		OnHovered();
		OnResize();
		for (const auto& r : app->resourceManager->GetResourcesList())
		{
			ImGui::Text("resource:");
			ImGui::Text("\t name: "); ImGui::SameLine(); ImGui::Text(r.second.second.get()->name.c_str());
			ImGui::Text("\t type: "); ImGui::SameLine(); ImGui::Text(r.second.second.get()->GetTypeChar());
			ImGui::Text("\t count: "); ImGui::SameLine(); ImGui::Text(std::to_string(r.second.second.use_count()).c_str());
			ImGui::Text("\t path: "); ImGui::SameLine(); ImGui::Text(r.first.c_str()); 
		}
	}
	ImGui::End();
	ImGui::PopStyleVar();
}

bool ResourcesPanel::CleanUp()
{
	return false;
}

void ResourcesPanel::ResfreshList(std::map<UID, std::shared_ptr<Resource>>* resources)
{
	resourcesToDisplay = resources;
}
