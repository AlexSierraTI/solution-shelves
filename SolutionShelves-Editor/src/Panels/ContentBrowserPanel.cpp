#include "sspch.h"
#include "ContentBrowserPanel.h"

#include <ImGui/imgui.h>

namespace SolutionShelves
{
	extern const std::filesystem::path g_AssetsPath = "assets";

	ContentBrowserPanel::ContentBrowserPanel()
		: m_CurrentDirectory(g_AssetsPath)
	{
		m_DirectoryIcon = Texture2D::Create("Resources/Icons/ContentBrowser/DirectoryIcon.png");
		m_FileIcon = Texture2D::Create("Resources/Icons/ContentBrowser/FileIcon.png");
	}

	void SolutionShelves::ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Content Browser");

		if (m_CurrentDirectory != std::filesystem::path(g_AssetsPath))
		{
			if (ImGui::Button("<-"))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		static float padding = 8.0f;
		static float thumbNailSize = 128.0f;
		float cellSize = thumbNailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1) columnCount = 1;
		ImGui::Columns(columnCount, 0, false);

				for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directoryEntry.path();
			auto relativePath = std::filesystem::relative(path, g_AssetsPath);
			std::string fileNameString = relativePath.filename().string();
			
			ImGui::PushID(fileNameString.c_str());

			Ref<Texture2D> icon = directoryEntry.is_directory() ? m_DirectoryIcon : m_FileIcon;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbNailSize, thumbNailSize }, { 0, 1 }, { 1, 0 });

			if (ImGui::BeginDragDropSource())
			{
				std::string extensao = path.extension().string();
				std::transform(extensao.begin(), extensao.end(), extensao.begin(), ::toupper);
				if (extensao == ".PNG" || extensao == ".JPG" || extensao == ".BMP" || extensao == ".GIF" || extensao == ".TIFF" || extensao == ".JPEG")
				{
					extensao = ".IMG";
				}
				std::string payloadType = "CONTENT_BROWSER_ITEM" + extensao;
				
				const wchar_t* itemPath = relativePath.c_str();
				ImGui::SetDragDropPayload(payloadType.c_str(), itemPath, (wcslen(itemPath) + 1)* sizeof(wchar_t), ImGuiCond_Once);
				ImGui::EndDragDropSource();
			}
			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (directoryEntry.is_directory())
				{
					m_CurrentDirectory /= path.filename();
				}
			}
			ImGui::TextWrapped(fileNameString.c_str());
			ImGui::NextColumn();
			ImGui::PopID();
		}

		ImGui::Columns(1);

		ImGui::SliderFloat("Thumbnail Size", &thumbNailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);
		// TODO: status bar
		ImGui::End();
	}
}
