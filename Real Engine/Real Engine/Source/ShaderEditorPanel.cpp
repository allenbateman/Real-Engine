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

		ImGui::Text("Editing: "); ImGui::SameLine();
		if (editVertex)
			ImGui::TextColored(ImVec4(0.4f, 0.8f, 0, 1), "Vertex Program");
		else
			ImGui::TextColored(ImVec4(0.8f, 0.3f, 0.0f, 1), "Fragment Program");

		if (ImGui::Button("Edit Vertex Program"))
		{
			editVertex = true;
		}
		//ImGui::SameLine();
		if (ImGui::Button("Edit Fragment Program"))
		{
			editVertex = false;
		}

		ImGui::Text("File: ");
		ImGui::SameLine();

		if (editVertex)
		{
			string vertex_name = vertexPath + "###vertex_title_edit";
			if (ImGui::BeginMenu(vertex_name.data()))
			{
				vector<std::filesystem::path> vertex_list;
				
				vertex_list = app->resourceManager->SearchForFileType(ASSETS_DIR, ".vertex");

				for (vector<std::filesystem::path>::iterator ver = vertex_list.begin(); ver != vertex_list.end(); ver++)
				{
					if (ImGui::MenuItem((*ver).filename().string().data()))
					{
						vertexPath = (*ver).filename().string().data();
						//app->fileSystem->Load(vertexPath.data(), &program);

					}
				}

				ImGui::EndMenu();
			}
		}
		else
		{
			string fragment_name = fragmentPath + "###fragment_title_edit";
			if (ImGui::BeginMenu(fragment_name.data()))
			{
				vector<std::filesystem::path> fragment_list;
				
				fragment_list = app->resourceManager->SearchForFileType(ASSETS_DIR, ".fragment");

				for (vector<std::filesystem::path>::iterator fra = fragment_list.begin(); fra != fragment_list.end(); fra++)
				{
					if (ImGui::MenuItem((*fra).filename().string().data()))
					{
						fragmentPath = (*fra).filename().string().data();
					}
				}

				ImGui::EndMenu();
			}

		}
		ImGui::End();
		ImGui::PopStyleVar();
	}
}

bool ShaderEditorPanel::CleanUp()
{
	return true;
}
