#include "ShaderEditorPanel.h"
#include "FileExplorer.h"
#include "ResourcesManagement.h"

ShaderEditorPanel::ShaderEditorPanel(int _id, bool isActive) : Panel( _id,  isActive)
{
}

ShaderEditorPanel::~ShaderEditorPanel()
{
}

void ShaderEditorPanel::Init()
{
	window_flags = ImGuiWindowFlags_NoDocking;
	borderOffset = 0;
}

void ShaderEditorPanel::Update()
{
	if (!active)
		return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2{ 720,720 }, ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Shader Editor", &active), NULL, window_flags)
	{
		OnHovered();
		OnResize();


		auto shader = SelectShader();
		if (shader != nullptr)
		{
			currentShader = shader;
			Editing = false;
		}
		if (currentShader == nullptr)
		{
			ImGui::End();
			ImGui::PopStyleVar();
			return;
		}

		ImGui::Text("Editing: "); ImGui::SameLine();
		if (editVertex)
			ImGui::TextColored(ImVec4(0.4f, 0.8f, 0, 1), "Vertex Program: %s", currentShader->name.c_str());
		else
			ImGui::TextColored(ImVec4(0.8f, 0.3f, 0.0f, 1), "Fragment Program: %s", currentShader->name.c_str());

		if (ImGui::Button("Edit Vertex Program"))
		{
			editVertex = true;
			Editing = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Edit Fragment Program"))
		{
			editVertex = false;
			Editing = false;
		}

		if(!currentShader->IsLoaded)
			ImGui::TextColored(ImVec4(0.8f, 0.3f, 0.0f, 1), "Shader not loaded, there might be a compliation error...");
		ImGui::Text("File: ");
		ImGui::SameLine();

		if (editVertex)
		{
			ShowTextEditor(currentShader->vertex.string().c_str());
		}
		else
		{
			ShowTextEditor(currentShader->fragment.string().c_str());

		}
		ImGui::End();
		ImGui::PopStyleVar();
	}
}

bool ShaderEditorPanel::CleanUp()
{
	return true;
}

shared_ptr<ResourceShader> ShaderEditorPanel::SelectShader()
{
	const auto  listBoxSize = ImVec2(310, 260);
	auto result = app->resourceManager->GetResourceListOfType(Resource::Type::Shader);
	const char** items = new const char* [result.size()];
	int currentItem = -1;
	for (int i = 0; i < result.size(); i++)
	{
		items[i] = result.at(i)->name.c_str();
	}

	if (ImGui::BeginCombo("##Resources", "select shader")) {

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
				auto resource = result.at(n);
				if (resource != nullptr)
					return static_pointer_cast<ResourceShader>(resource);
				return nullptr;
			}
		}
		ImGui::EndCombo();
	}
	return nullptr;
}

void ShaderEditorPanel::ShowTextEditor(const char* filepath)
{
	// Load the file content into a string
	if (!Editing)
	{
		std::ifstream file(filepath);
		if (!file.is_open())return;
		std::stringstream buffer;
		buffer << file.rdbuf();
		content = buffer.str();
		Editing = true;
	}

	// Create a text edit box to edit the file content
	ImGui::InputTextMultiline("##source", &content[0], MAX_SHADER_LENGTH,ImVec2(550,600));

	if (ImGui::Button("Save")) {
		// Open the file and write the new content
		std::ofstream file(filepath);
		if (file.is_open())
		{
			file << content;
			file.close();
			content = "";
			currentShader->IsLoaded = false;
			currentShader->Load();
			Editing = false;
		}
	}
}
