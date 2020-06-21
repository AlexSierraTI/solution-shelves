#include "Player.h"

namespace PokerSS
{
	Player::Player(const std::string& name, const glm::vec2& position, Orientation orientation)
		: m_Name(name), m_Position(position), m_Orientation(orientation)
	{
		m_DealerChipPosition = { 0.0f, 0.0f, 0.1f };
		m_DealerChipSize = { 0.155f, 0.155f };
		m_PlayerSize = { 0.35f, 0.35f };
		m_CardSize = 0.25f;
		LoadAssets();
	}

	Player::~Player()
	{
	}

	void Player::LoadAssets()
	{
		m_PlayerTextureLeft = SolutionShelves::Texture2D::Create("assets/textures/player_1.png");
		m_PlayerTextureRight = SolutionShelves::Texture2D::Create("assets/textures/player_2.png");

		m_PlayerDrawTexture = m_PlayerTextureLeft;
		
		m_DealerChip = SolutionShelves::Texture2D::Create("assets/textures/dealer-chip.png");
	}
	
	void Player::OnUpdate(SolutionShelves::Timestep ts)
	{

	}

	void Player::OnRender()
	{
		const float playerSize = 0.1f;

		// Dealer Chip
		if (m_Dealer) SolutionShelves::Renderer2D::DrawQuad(m_DealerChipPosition, m_DealerChipSize, m_DealerChip);

		// Player
		SolutionShelves::Renderer2D::DrawQuad({ m_Position.x, m_Position.y, 0.1f }, m_PlayerSize, m_PlayerTextureLeft);
	}

	void Player::OnImGuiRender()
	{
		char dealerChipPositionDescription[50];
		char dealerChipSizeDescription[50];
		char playerPositionDescription[50];
		char playerSizeDescription[50];

		sprintf_s(dealerChipPositionDescription, ": Dealer Chip Position %s", m_Name.c_str());
		sprintf_s(dealerChipSizeDescription, ": Dealer Chip Size %s", m_Name.c_str());
		sprintf_s(playerPositionDescription, ": Player Position %s", m_Name.c_str());
		sprintf_s(playerSizeDescription, ": Player Size %s", m_Name.c_str());
		sprintf_s(playerSizeDescription, ": Player Size %s", m_Name.c_str());

		// ImGui::DragFloat(": Card Size", &m_CardSize, 0.01f);

		// ImGui::DragFloat3(dealerChipPositionDescription, glm::value_ptr(m_DealerChipPosition), 0.01f);
		// ImGui::DragFloat2(dealerChipSizeDescription, glm::value_ptr(m_DealerChipSize), 0.01f);

		// ImGui::DragFloat2(playerPositionDescription, glm::value_ptr(m_Position), 0.01f);
		// ImGui::DragFloat2(playerSizeDescription, glm::value_ptr(m_PlayerSize), 0.01f);
	}

	void Player::SetPosition(const glm::vec2& position)
	{
		m_Position = position;
	}

	void Player::SetDealer(bool isDealer)
	{
		m_Dealer = isDealer;
	}

	void Player::AddCard(const SolutionShelves::Ref<Card> card)
	{
		m_Hand[card->GetEntityID()] = card;
		CalculateRenderPositions();
		card->EnableRender();
	}

	void Player::RemoveCard(const SolutionShelves::Ref<Card> card)
	{
		m_Hand.erase(card->GetEntityID());
		CalculateRenderPositions();
		card->DisableRender();
	}

	void Player::ClearHand()
	{
		m_Hand.clear();
		CalculateRenderPositions();
	}

	void Player::CalculateRenderPositions()
	{
		// Dealer Chip
		const float dealerChipOffsetX = 0.25f;
		const float dealerChipOffsetY = 0.25f;

		float dealerChipOffsetOrientationX = 0.0f;
		float dealerChipOffsetOrientationY = 0.0f;
		
		// Cards
		const float cardSpaceAspectRatio = m_CardSize / 0.05f;

		const float cardSpacePlayerY = 0.065f * cardSpaceAspectRatio;
		const float cardSpacePlayerX = 0.065f * cardSpaceAspectRatio;

		const float cardSpaceOffsetX = 0.03f * cardSpaceAspectRatio;
		const float cardSpaceOffsetXDisplace = 0.001f * cardSpaceAspectRatio;

		const float cardSpaceOffsetY = 0.03f * cardSpaceAspectRatio;
		const float cardSpaceOffsetYDisplace = 0.001f * cardSpaceAspectRatio;

		uint32_t iCount = 0;
		uint64_t iCountRemaining = 0;

		switch (m_Orientation)
		{
		case Orientation::LEFT:
			dealerChipOffsetOrientationX = m_Position.x;
			dealerChipOffsetOrientationY = m_Position.y - dealerChipOffsetY;

			m_PlayerDrawTexture = m_PlayerTextureLeft;
			for (auto& it : m_Hand)
			{
				iCount++;
				iCountRemaining = m_Hand.size() - iCount;
				it.second->SetRenderPosition({ m_Position.x - cardSpacePlayerX,
											   m_Position.y - (cardSpaceOffsetY * iCountRemaining) + ((iCount - 1) * (cardSpaceOffsetY + cardSpaceOffsetYDisplace)) });
				it.second->SetRenderSize(m_CardSize);
				it.second->SetRenderRotation(glm::radians(90.0f));
			}
			break;
		case Orientation::RIGHT:
			dealerChipOffsetOrientationX = m_Position.x;
			dealerChipOffsetOrientationY = m_Position.y + dealerChipOffsetY;


			m_PlayerDrawTexture = m_PlayerTextureRight;
			for (auto& it : m_Hand)
			{
				iCount++;
				iCountRemaining = m_Hand.size() - iCount;
				it.second->SetRenderPosition({ m_Position.x + cardSpacePlayerX,
											   m_Position.y + (cardSpaceOffsetY * iCountRemaining) - ((iCount - 1) * (cardSpaceOffsetY + cardSpaceOffsetYDisplace)) });
				it.second->SetRenderSize(m_CardSize);
				it.second->SetRenderRotation(glm::radians(-90.0f));
			}
			break;
		case Orientation::DOWN:
			dealerChipOffsetOrientationX = m_Position.x - dealerChipOffsetX;
			dealerChipOffsetOrientationY = m_Position.y;

			m_PlayerDrawTexture = m_PlayerTextureRight;
			for (auto& it : m_Hand)
			{
				iCount++;
				iCountRemaining = m_Hand.size() - iCount;
				it.second->SetRenderPosition({ m_Position.x + (cardSpaceOffsetX * iCountRemaining) - ((iCount - 1) * (cardSpaceOffsetX + cardSpaceOffsetXDisplace)),
							                   m_Position.y - cardSpacePlayerY });
				it.second->SetRenderSize(m_CardSize);
				it.second->SetRenderRotation(glm::radians(180.0f));
			}
			break;
		case Orientation::UP:
			dealerChipOffsetOrientationX = m_Position.x + dealerChipOffsetX;
			dealerChipOffsetOrientationY = m_Position.y;

			m_PlayerDrawTexture = m_PlayerTextureLeft;
			for (auto& it : m_Hand)
			{
				iCount++;
				iCountRemaining = m_Hand.size() - iCount;
				it.second->SetRenderPosition({ m_Position.x - (cardSpaceOffsetX * iCountRemaining) + ((iCount - 1) * (cardSpaceOffsetX  + cardSpaceOffsetXDisplace)), 
					                           m_Position.y + cardSpacePlayerY });
				it.second->SetRenderSize(m_CardSize);
				it.second->SetRenderRotation(glm::radians(0.0f));
				
			}
			break;
		}

		m_DealerChipPosition = { dealerChipOffsetOrientationX, dealerChipOffsetOrientationY, 0.1f };
	}

}
