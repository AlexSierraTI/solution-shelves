#include "Player.h"

#include "Core/EntityManager.h"

namespace PokerSS
{
	Player::Player(const std::string& name,
		const SolutionShelves::Ref<SolutionShelves::Texture2D>& playerTextureLeft,
		const SolutionShelves::Ref<SolutionShelves::Texture2D>& playerTextureRight,
		const SolutionShelves::Ref<SolutionShelves::Texture2D>& dealerChip,
		const SolutionShelves::Ref<SolutionShelves::Texture2D>& chipStackTexture)
		: m_Name(name), m_PlayerTextureLeft(playerTextureLeft), m_PlayerTextureRight(playerTextureRight),
		m_DealerChip(dealerChip), m_ChipStackTexture(chipStackTexture)
	{
		m_Position = { 0.0f, 0.0f };
		m_GridPosition = { 0.0f, 0.0f };
		m_Orientation = Orientation::DOWN;
		m_DealerChipPosition = { 0.0f, 0.0f, 0.1f };
		m_DealerChipSize = { 0.155f, 0.155f };
		m_PlayerSize = { 0.35f, 0.35f };
		m_CardSize = 0.25f;

		m_Points = 0;
		m_InGame = false;
		m_Points = 0;
		m_HandDescription = "";
		m_Chips = 0;
		m_Bet = 0;
		m_InAction = false;
		m_Folded = false;
		m_FlatCalled = false;

		LoadAssets();
	}

	Player::~Player()
	{
	}

	void Player::LoadAssets()
	{
		m_PlayerDrawTexture = m_PlayerTextureLeft;
		m_ChipStack = SolutionShelves::CreateRef<ChipStack>(m_ChipStackTexture);
		m_ChipStackBet = SolutionShelves::CreateRef<ChipStack>(m_ChipStackTexture);
		m_ChipStack->EnableRender();
		m_ChipStackBet->EnableRender();
		EntityManager::Get().PushEntity(m_ChipStack);
		EntityManager::Get().PushEntity(m_ChipStackBet);
	}
	
	void Player::OnUpdate(SolutionShelves::Timestep ts)
	{
		if (m_Bet > 0)
		{
			float chipStackBetOffset = 0.5f;
			float chipStackSize = 0.2f;
			switch (m_Orientation)
			{
			case Orientation::LEFT:
				m_ChipStackBet->SetRenderPosition({ m_Position.x - chipStackBetOffset, m_Position.y });
				break;
			case Orientation::RIGHT:
				m_ChipStackBet->SetRenderPosition({ m_Position.x + chipStackBetOffset, m_Position.y });
				break;
			case Orientation::UP:
				m_ChipStackBet->SetRenderPosition({ m_Position.x, m_Position.y + chipStackBetOffset });
				break;
			case Orientation::DOWN:
				m_ChipStackBet->SetRenderPosition({ m_Position.x, m_Position.y - chipStackBetOffset });
				break;
			}
			m_ChipStackBet->SetRenderSize(chipStackSize);
		}
		else
		{
			CalculateRenderPositions();
			m_ChipStackBet->SetRenderPosition(m_ChipStack->GetRenderPosition());
			m_ChipStackBet->SetRenderSize(0.0f);
		}

	}

	void Player::OnRender()
	{
		const float playerSize = 0.1f;

		// Dealer Chip
		if (m_Dealer) SolutionShelves::Renderer2D::DrawQuad(m_DealerChipPosition, m_DealerChipSize, m_DealerChip);

		// Player
		if (!m_InAction && !m_Folded)
			SolutionShelves::Renderer2D::DrawQuad({ m_Position.x, m_Position.y, 0.1f }, m_PlayerSize, m_PlayerDrawTexture);
		else if (m_Folded)
			SolutionShelves::Renderer2D::DrawQuad({ m_Position.x, m_Position.y, 0.1f }, m_PlayerSize, m_PlayerDrawTexture, 1.0f, { 0.5f, 0.5f, 0.5f, 0.5f });
		else
			SolutionShelves::Renderer2D::DrawQuad({ m_Position.x, m_Position.y, 0.1f }, m_PlayerSize, m_PlayerDrawTexture, 1.0f, { 1.0f, 1.0f, 0.0f, 1.0f });
	}

	void Player::OnImGuiRender()
	{
		float playerNameOffSet = (float)m_Name.length() * 20.0f;
		float playerPositionOffsetX = 0.0f;
		float playerPositionOffsetY = 0.0f;

		float playerStackOffsetX = 0.0f;
		float playerStackOffsetY = 0.0f;

		float playerBetStackOffsetX = 0.0f;
		float playerBetStackOffsetY = 0.0f;
		switch (m_Orientation)
		{
		case Orientation::UP:
			playerPositionOffsetX = -playerNameOffSet;
			playerPositionOffsetY = -120.0f;

			playerStackOffsetX = -200.0f;
			playerStackOffsetY = -110.0f;

			playerBetStackOffsetX = -230.0f;
			playerBetStackOffsetY =  -140.0f;
			break;
		case Orientation::DOWN:
			playerPositionOffsetX = -playerNameOffSet;
			playerPositionOffsetY = 0.0f;

			playerStackOffsetX = 0.0f;
			playerStackOffsetY = 0.0f;

			playerBetStackOffsetX = 60.0f;
			playerBetStackOffsetY = 45.0f;
			break;
		case Orientation::LEFT:
			playerPositionOffsetX = -100.0f;
			playerPositionOffsetY = +25.0f;

			playerStackOffsetX = -200.0f;
			playerStackOffsetY = +100.0f;

			playerBetStackOffsetX = -250.0f;
			playerBetStackOffsetY = 100.0f;
			break;
		case Orientation::RIGHT:
			playerPositionOffsetX = -70.0f;
			playerPositionOffsetY = +20.0f;

			playerStackOffsetX = 20.0f;
			playerStackOffsetY = -200.0f;

			playerBetStackOffsetX = 70.0f;
			playerBetStackOffsetY = -160.0f;
			break;
		}

		auto posNome = ImGui::GetWindowPos();
		posNome.x += m_GridPosition.x + playerPositionOffsetX;
		posNome.y += m_GridPosition.y + playerPositionOffsetY;
		auto fonts = ImGui::GetIO().Fonts;
		ImGui::GetForegroundDrawList()->AddText(fonts->Fonts[1], 36.0f, posNome, 0xffffffff, m_Name.c_str());

		auto posStack = ImGui::GetWindowPos();
		posStack.x += m_GridPosition.x + playerStackOffsetX;
		posStack.y += m_GridPosition.y + playerStackOffsetY;
		char stackChips[10];
		sprintf_s(stackChips, "[%d]", m_Chips - m_Bet);
		ImGui::GetForegroundDrawList()->AddText(fonts->Fonts[2], 18.0f, posStack, 0xff0f0e0e, stackChips);

		auto posBetStack = ImGui::GetWindowPos();
		posBetStack.x += m_GridPosition.x + playerBetStackOffsetX;
		posBetStack.y += m_GridPosition.y + playerBetStackOffsetY;
		char betStackChips[10];
		sprintf_s(betStackChips, "[%d]", m_Bet);
		ImGui::GetForegroundDrawList()->AddText(fonts->Fonts[2], 16.0f, posBetStack, 0xff1e1eaf, betStackChips);
	}

	bool Player::GetIsAllIn()
	{
		return (m_Bet  == m_Chips);
	}

	void Player::SetPosition(const glm::vec2& position)
	{
		m_Position = position;
		CalculateRenderPositions();
	}

	void Player::SetLayoutPosition(const glm::vec2& position)
	{
		m_GridPosition = position;
	}

	void Player::SetOrientation(Orientation orientation)
	{
		m_Orientation = orientation;
		CalculateRenderPositions();
	}

	void Player::SetDealer(bool isDealer)
	{
		m_Dealer = isDealer;
		CalculateRenderPositions();
	}

	void Player::AddCard(const SolutionShelves::Ref<Card> card)
	{
		m_Hand.push_back(card);
		CalculateRenderPositions();
		card->EnableRender();
	}

	void Player::RemoveCard(const SolutionShelves::Ref<Card> card)
	{
		uint32_t cardIndex = 0;
		bool cardFound = false;
		for (auto& it : m_Hand)
		{
			if (it->GetEntityID() == card->GetEntityID()) 
			{
				cardFound = true;
				break;
			}
			cardIndex++;
		}

		if (cardFound)
		{
			m_Hand.erase(m_Hand.begin() + cardIndex);
			CalculateRenderPositions();
			card->DisableRender();
		}
	}

	void Player::ClearHand()
	{
		while (!m_Hand.empty())
		{
			RemoveCard(m_Hand.front());
		}
	}

	void Player::AddChips(uint32_t value)
	{
		m_Chips += value;
		m_ChipStack->SetChipAmount(m_Chips);
	}

	void Player::RemoveChips(uint32_t value)
	{
		if (value >= m_Chips)
			m_Chips = 0;
		else
			m_Chips -= value;

		m_ChipStack->SetChipAmount(m_Chips);
	}

	void Player::AddBet(uint32_t value)
	{
		m_Bet += value;
		m_ChipStackBet->SetChipAmount(m_Bet);
	}

	void Player::ClearBet()
	{
		m_Bet = 0;
		m_ChipStackBet->SetChipAmount(m_Bet);
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

		// ChipStacks
		const float chipStackStackOffsetX = 0.25f;
		const float chipStackStackOffsetY = 0.25f;
		const float chipStackStackSize = 0.3f;


		uint32_t iCount = 0;
		uint64_t iCountRemaining = 0;

		switch (m_Orientation)
		{
		case Orientation::LEFT:
			dealerChipOffsetOrientationX = m_Position.x;
			dealerChipOffsetOrientationY = m_Position.y - dealerChipOffsetY;

			m_ChipStack->SetRenderPosition(
				{
					m_Position.x - chipStackStackOffsetX,
					m_Position.y - chipStackStackOffsetY
				});
			m_ChipStack->SetRenderSize(chipStackStackSize);
			m_ChipStack->SetRenderRotation(glm::radians(90.0f));


			m_PlayerDrawTexture = m_PlayerTextureLeft;
			for (auto& it : m_Hand)
			{
				iCount++;
				iCountRemaining = m_Hand.size() - iCount;
				it->SetRenderPosition({ m_Position.x - cardSpacePlayerX,
									    m_Position.y - (cardSpaceOffsetY * iCountRemaining) + ((iCount - 1) * (cardSpaceOffsetY + cardSpaceOffsetYDisplace)) });
				it->SetRenderSize(m_CardSize);
				it->SetRenderRotation(glm::radians(90.0f));
			}
			break;
		case Orientation::RIGHT:
			dealerChipOffsetOrientationX = m_Position.x;
			dealerChipOffsetOrientationY = m_Position.y + dealerChipOffsetY;

			m_ChipStack->SetRenderPosition(
				{
					m_Position.x + chipStackStackOffsetX,
					m_Position.y + chipStackStackOffsetY
				});
			m_ChipStack->SetRenderSize(chipStackStackSize);
			m_ChipStack->SetRenderRotation(glm::radians(-90.0f));

			m_PlayerDrawTexture = m_PlayerTextureRight;
			for (auto& it : m_Hand)
			{
				iCount++;
				iCountRemaining = m_Hand.size() - iCount;
				it->SetRenderPosition({ m_Position.x + cardSpacePlayerX,
											   m_Position.y + (cardSpaceOffsetY * iCountRemaining) - ((iCount - 1) * (cardSpaceOffsetY + cardSpaceOffsetYDisplace)) });
				it->SetRenderSize(m_CardSize);
				it->SetRenderRotation(glm::radians(-90.0f));
			}
			break;
		case Orientation::DOWN:
			dealerChipOffsetOrientationX = m_Position.x - dealerChipOffsetX;
			dealerChipOffsetOrientationY = m_Position.y;

			m_ChipStack->SetRenderPosition(
				{
					m_Position.x + chipStackStackOffsetX,
					m_Position.y - chipStackStackOffsetY
				});
			m_ChipStack->SetRenderSize(chipStackStackSize);
			m_ChipStack->SetRenderRotation(glm::radians(180.0f));

			m_PlayerDrawTexture = m_PlayerTextureRight;
			for (auto& it : m_Hand)
			{
				iCount++;
				iCountRemaining = m_Hand.size() - iCount;
				it->SetRenderPosition({ m_Position.x + (cardSpaceOffsetX * iCountRemaining) - ((iCount - 1) * (cardSpaceOffsetX + cardSpaceOffsetXDisplace)),
							                   m_Position.y - cardSpacePlayerY });
				it->SetRenderSize(m_CardSize);
				it->SetRenderRotation(glm::radians(180.0f));
			}
			break;
		case Orientation::UP:
			dealerChipOffsetOrientationX = m_Position.x + dealerChipOffsetX;
			dealerChipOffsetOrientationY = m_Position.y;

			m_ChipStack->SetRenderPosition(
				{
					m_Position.x - chipStackStackOffsetX,
					m_Position.y + chipStackStackOffsetY
				});
			m_ChipStack->SetRenderSize(chipStackStackSize);
			m_ChipStack->SetRenderRotation(glm::radians(0.0f));

			m_PlayerDrawTexture = m_PlayerTextureLeft;
			for (auto& it : m_Hand)
			{
				iCount++;
				iCountRemaining = m_Hand.size() - iCount;
				it->SetRenderPosition({ m_Position.x - (cardSpaceOffsetX * iCountRemaining) + ((iCount - 1) * (cardSpaceOffsetX  + cardSpaceOffsetXDisplace)), 
					                           m_Position.y + cardSpacePlayerY });
				it->SetRenderSize(m_CardSize);
				it->SetRenderRotation(glm::radians(0.0f));
				
			}
			break;
		}

		m_DealerChipPosition = { dealerChipOffsetOrientationX, dealerChipOffsetOrientationY, 0.1f };
	}

}
