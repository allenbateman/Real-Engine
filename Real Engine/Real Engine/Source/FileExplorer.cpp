#include "FileExplorer.h"
#include "TextureLoader.h"
#include "UiSystem.h"


extern const fs::path assetPath = "../Output/Assets";

FileExplorer::FileExplorer(int _id, bool isActive) : Panel(_id, isActive)
{
	name.Create("File Explorer");

	
	currentDirectory = assetPath;
}

FileExplorer::~FileExplorer()
{
}

void FileExplorer::Init()
{
	directoryIcon = LoadTexture("../Output/SystemFiles/folder.png");
	fileIcon = LoadTexture("../Output/SystemFiles/file.png");
}

void FileExplorer::Update()
{
	if (ImGui::Begin("Files"));

		if (currentDirectory != fs::path(assetPath))
		{
			if (ImGui::Button("<-") || (ImGui::IsItemHovered() && ImGui::IsMouseDragging(0)))
			{
				currentDirectory = currentDirectory.parent_path();
			}
		}

		static float padding = 16.0f;
		static float thumbnailSize = 128.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (auto& directoryEntry : fs::directory_iterator(currentDirectory))
		{

			const auto& path = directoryEntry.path();
			if (path.extension() == ".meta")
			{
				continue;
			}
			std::string filenameString = path.filename().string();

			ImGui::PushID(filenameString.c_str());
			int icon = directoryEntry.is_directory() ? directoryIcon : fileIcon;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1,1, 0.5));
			ImGui::ImageButton((ImTextureID)icon, { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });

			if (ImGui::BeginDragDropSource())
			{
				const wchar_t* itemPath = path.c_str();
				ImGui::SetDragDropPayload(payload_fileContent, itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
				ImGui::EndDragDropSource();
			}
			if (ImGui::BeginDragDropTarget())
			{

				const ImGuiPayload* itemDrop = ImGui::AcceptDragDropPayload(payload_fileContent);
				if (itemDrop != nullptr && directoryEntry.is_directory())
				{
					fs::path cpath = (wchar_t*)itemDrop->Data;
					fs::path newPath = path.string() + '/' + cpath.filename().string();
					fs::rename(cpath, newPath);
				}
			}
			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (directoryEntry.is_directory())
					currentDirectory /= path.filename();

			}
			ImGui::TextWrapped(filenameString.c_str());

			ImGui::NextColumn();

			ImGui::PopID();
		}

		ImGui::Columns(1);

		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);

		// TODO: status bar
	
	ImGui::End();
}

bool FileExplorer::CleanUp()
{
	return true;
}
