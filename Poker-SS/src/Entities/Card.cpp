#include "Card.h"

namespace PokerSS
{
	Card::Card(const SolutionShelves::Ref<SolutionShelves::Texture2D>& cardSpriteSheet,
		       const SolutionShelves::Ref<SolutionShelves::Texture2D>& cardBackSpriteSheet, 
		       CardBack cardBack, FaceValue faceValue, Suit suit)
		: m_CardBack(cardBack), m_FaceValue(faceValue), m_Suit(suit)
	{
		m_CardSpriteSheet = cardSpriteSheet;
		m_CardBackSpriteSheet = cardBackSpriteSheet;
		m_RenderPosition = { 0.0f, 0.0f };
		m_TargetPosition = { 0.0f, 0.0f };
		m_RenderSize = 0.0f;
		m_Rotation = 0.0f;
		m_Revealed = false;

		LoadAssets();
	}

	Card::~Card()
	{
	}

	void Card::LoadAssets()
	{
		CalculateTexture();
	}

	void Card::OnUpdate(SolutionShelves::Timestep ts)
	{
		const float cardAnimationSpeed = 0.5f;
		const float offsetTolerance = 0.005f;
		
		if (glm::abs(m_TargetPosition.x - m_RenderPosition.x) <= offsetTolerance) m_RenderPosition.x = m_TargetPosition.x;
		if (glm::abs(m_TargetPosition.y - m_RenderPosition.y) <= offsetTolerance) m_RenderPosition.y = m_TargetPosition.y;

		if      (m_TargetPosition.x > m_RenderPosition.x) m_RenderPosition.x += cardAnimationSpeed * ts;
		else if (m_TargetPosition.x < m_RenderPosition.x) m_RenderPosition.x -= cardAnimationSpeed * ts;
		if      (m_TargetPosition.y > m_RenderPosition.y) m_RenderPosition.y += cardAnimationSpeed * ts;
		else if (m_TargetPosition.y < m_RenderPosition.y) m_RenderPosition.y -= cardAnimationSpeed * ts;
		
		CalculateTexture();
	}

	void Card::OnRender()
	{
		if (m_RenderSize)
		{
			SolutionShelves::Renderer2D::DrawRotatedQuad({ m_RenderPosition.x, m_RenderPosition.y, 0.1f }, { m_RenderSize, m_RenderSize }, m_Rotation, m_CardTexture);
		}
	}

	void Card::OnImGuiRender()
	{
		// ImGui::DragFloat2(GetCardDescription().c_str(), glm::value_ptr(m_TargetPosition), 0.01f);
	}

	void Card::SetCardValue(FaceValue faceValue, Suit suit)
	{
		m_FaceValue = faceValue;
		m_Suit = suit;
		CalculateTexture();
	}

	std::string Card::GetCardDescription()
	{
		const char* const faceValue[] = { 
			"Unknown", "Deuce", "Tray", "Four", "Five", "Six", "Seven", 
			"Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
		};

		const char* const suit[] = {
			"Unknown", "Clubs", "Hearts", "Spades", "Diamonds"
		};

		std::string strRetorno = "";
		strRetorno.append(faceValue[(uint32_t)m_FaceValue]);
		strRetorno.append(" of ");
		strRetorno.append(suit[(uint32_t)m_Suit]);

		return strRetorno;
	}

	void Card::CalculateTexture()
	{
		uint32_t posXCardBack = (uint32_t)m_CardBack % 3;
		uint32_t posYCardBack = (uint32_t)m_CardBack / 3;

		if ((m_RenderPosition != m_TargetPosition) || !m_Revealed) 
		{
			m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardBackSpriteSheet, { (float)posXCardBack, (float)posYCardBack }, { 140.0f, 190.0f });
			return;
		}

		switch (m_Suit)
		{
		case Suit::Spades:
			switch (m_FaceValue)
			{
			case FaceValue::Deuce:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 4.0f, 2.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Tray:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 4.0f, 1.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Four:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 4.0f, 4.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Five:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 5.0f, 9.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Six:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 5.0f, 8.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Seven:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 5.0f, 7.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Eight:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 5.0f, 6.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Nine:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 5.0f, 5.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Ten:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 5.0f, 4.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Jack:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 5.0f, 2.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Queen:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 5.0f, 0.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::King:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 5.0f, 1.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Ace:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 5.0f, 3.0f }, { 140.0f, 190.0f });
				break;
			}
			break;
		case Suit::Hearts:
			switch (m_FaceValue)
			{
			case FaceValue::Deuce:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 0.0f, 2.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Tray:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 3.0f, 5.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Four:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 3.0f, 4.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Five:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 3.0f, 3.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Six:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 3.0f, 2.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Seven:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 3.0f, 1.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Eight:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 3.0f, 0.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Nine:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 4.0f, 9.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Ten:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 4.0f, 8.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Jack:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 4.0f, 6.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Queen:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 4.0f, 4.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::King:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 4.0f, 5.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Ace:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 4.0f, 7.0f }, { 140.0f, 190.0f });
				break;
			}
			break;
		case Suit::Diamonds:
			switch (m_FaceValue)
			{
			case FaceValue::Deuce:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 2.0f, 9.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Tray:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 2.0f, 8.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Four:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 2.0f, 7.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Five:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 2.0f, 6.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Six:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 2.0f, 5.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Seven:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 2.0f, 4.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Eight:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 2.0f, 3.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Nine:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 2.0f, 2.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Ten:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 2.0f, 1.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Jack:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 3.0f, 9.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Queen:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 3.0f, 7.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::King:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 3.0f, 8.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Ace:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 2.0f, 0.0f }, { 140.0f, 190.0f });
				break;
			}
			break;
		case Suit::Clubs:
			switch (m_FaceValue)
			{
			case FaceValue::Deuce:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 3.0f, 6.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Tray:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 0.0f, 1.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Four:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 0.0f, 0.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Five:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 1.0f, 9.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Six:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 1.0f, 8.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Seven:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 1.0f, 7.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Eight:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 1.0f, 6.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Nine:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 1.0f, 5.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Ten:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 1.0f, 4.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Jack:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 1.0f, 2.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Queen:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 1.0f, 0.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::King:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 1.0f, 1.0f }, { 140.0f, 190.0f });
				break;
			case FaceValue::Ace:
				m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardSpriteSheet, { 1.0f, 3.0f }, { 140.0f, 190.0f });
				break;
			}
			break;
		case Suit::Unknown:
			m_CardTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_CardBackSpriteSheet, { (float)posXCardBack, (float)posYCardBack }, { 140.0f, 190.0f });
			break;
		}
	}

}