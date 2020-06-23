#include "OldWest.h"

const uint32_t s_MapWidth = 10;
const char* s_MapTiles =
"##########" // 9 
"##########" // 8      
"##########" // 7
"##########" // 6
"##########" // 5
"##########" // 4
"##########" // 3     
"##########" // 2
"##########" // 1
"##########" // 0
;

namespace PokerSS
{
	OldWest::OldWest()
		: m_DefaultPos({ 0.0f, 0.0f }, Orientation::DOWN)
	{
		m_LevelSize = { 3.6f, 1.97f };
		LoadAssets();
		
		m_PlayersData.push_back(PlayerData({ 5.0f, 9.0f }, Orientation::UP));
		m_PlayersData.push_back(PlayerData({ 0.5f, 5.0f }, Orientation::RIGHT));
		m_PlayersData.push_back(PlayerData({ 5.0f, 1.0f }, Orientation::DOWN));
		m_PlayersData.push_back(PlayerData({ 9.5f, 5.0f }, Orientation::LEFT));

		m_MapLayoutSize = { (float)s_MapWidth, (float)strlen(s_MapTiles) / (float)s_MapWidth };
	}

	OldWest::~OldWest()
	{
	}

	void OldWest::LoadAssets()
	{
		m_LevelTexture = SolutionShelves::Texture2D::Create("assets/textures/velcro.png");
	}

	void OldWest::OnUpdate(SolutionShelves::Timestep ts)
	{

	}

	void OldWest::OnRender()
	{
		SolutionShelves::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, m_LevelSize, m_LevelTexture);
	}

	void OldWest::OnImGuiRender()
	{
		//ImGui::DragFloat2("Level Size", glm::value_ptr(m_LevelSize), 0.01f);
	}
	const PlayerData& OldWest::GetPlayerData(uint32_t pos)
	{
		if (pos > m_PlayersData.size())
			return m_DefaultPos;
		else
			return m_PlayersData[pos];
	}
}