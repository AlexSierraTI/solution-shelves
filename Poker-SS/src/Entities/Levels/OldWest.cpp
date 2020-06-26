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
		
		m_PlayersData.push_back(PlayerData({ 5.0f, 9.0f }, Orientation::UP));    // CENTRO BAIXO 						  0
		m_PlayersData.push_back(PlayerData({ 5.0f, 1.0f }, Orientation::DOWN));  // CENTRO CIMA							  1
																														  
		m_PlayersData.push_back(PlayerData({ 1.0f, 1.0f }, Orientation::RIGHT));  // DIAGONAL ESQUERDA					  2
		m_PlayersData.push_back(PlayerData({ 9.0f, 1.0f }, Orientation::LEFT));   // DIAGONAL DIREITA					  3
																														  
		m_PlayersData.push_back(PlayerData({ 1.0f, 5.0f }, Orientation::RIGHT));  // ESQUERDA							  4
		m_PlayersData.push_back(PlayerData({ 9.0f, 5.0f }, Orientation::LEFT));   // DIREITA							  5
																														  
		m_PlayersData.push_back(PlayerData({ 3.0f, 1.0f }, Orientation::DOWN));   // DIAGONAL ESQUERDA MAIS AO CENTRO	  6
		m_PlayersData.push_back(PlayerData({ 7.0f, 1.0f }, Orientation::DOWN));   // DIAGONAL DIREITA MAIS AO CENTRO	  7
																														  
		m_PlayersData.push_back(PlayerData({ 1.0f, 7.0f }, Orientation::RIGHT));  // ESQUERDA MAIS A CIMA				  8
		m_PlayersData.push_back(PlayerData({ 1.0f, 3.0f }, Orientation::RIGHT));  // ESQUERDA MAIS A BAIXO				  9
																														  
		m_PlayersData.push_back(PlayerData({ 9.0f, 7.0f }, Orientation::LEFT));  // DIREITA MAIS A CIMA					  10
		m_PlayersData.push_back(PlayerData({ 9.0f, 3.0f }, Orientation::LEFT));  // DIREITA MAIS A BAIXO				  11
																														  
		m_PlayersData.push_back(PlayerData({ 3.0f, 9.0f }, Orientation::UP));    // BAIXO MAIS PRA ESQUERDA				  12
		m_PlayersData.push_back(PlayerData({ 7.0f, 9.0f }, Orientation::UP));    // BAIXO MAIS PRA DIREITA				  13

		//m_PlayersData.push_back(PlayerData({ 6.0f, 9.0f }, Orientation::UP));
		//m_PlayersData.push_back(PlayerData({ 4.0f, 9.0f }, Orientation::UP));
		//m_PlayersData.push_back(PlayerData({ 0.5f, 3.0f }, Orientation::RIGHT));
		//m_PlayersData.push_back(PlayerData({ 0.5f, 7.0f }, Orientation::RIGHT));
		//m_PlayersData.push_back(PlayerData({ 2.5f, 1.0f }, Orientation::DOWN));
		//m_PlayersData.push_back(PlayerData({ 5.0f, 1.0f }, Orientation::DOWN));
		//m_PlayersData.push_back(PlayerData({ 7.5f, 1.0f }, Orientation::DOWN));
		//m_PlayersData.push_back(PlayerData({ 9.5f, 6.0f }, Orientation::LEFT));
		//m_PlayersData.push_back(PlayerData({ 9.5f, 3.0f }, Orientation::LEFT));

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
	}
	PlayerData& OldWest::GetPlayerData(uint32_t pos)
	{
		if (pos > m_PlayersData.size())
			return m_DefaultPos;
		else
			return m_PlayersData[pos];
	}
}