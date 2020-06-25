#include "ChipStack.h"

namespace PokerSS
{
	ChipStack::ChipStack(const SolutionShelves::Ref<SolutionShelves::Texture2D>& chipsSpriteSheet)
	{
		m_ChipsSpriteSheet = chipsSpriteSheet;
		m_RenderPosition = { 0.0f, 0.0f };
		m_TargetPosition = { 0.0f, 0.0f };
		m_RenderSize = 0.0f;
		m_Rotation = 0.0f;
		m_ChipAmount = 0;

		LoadAssets();

	}
	ChipStack::~ChipStack()
	{
	}
	void ChipStack::LoadAssets()
	{
		CalculateTexture();
	}

	void ChipStack::OnUpdate(SolutionShelves::Timestep ts)
	{
		const float chipAnimationSpeed = 0.5f;
		const float offsetTolerance = 0.005f;

		if (glm::abs(m_TargetPosition.x - m_RenderPosition.x) <= offsetTolerance) m_RenderPosition.x = m_TargetPosition.x;
		if (glm::abs(m_TargetPosition.y - m_RenderPosition.y) <= offsetTolerance) m_RenderPosition.y = m_TargetPosition.y;

		if (m_TargetPosition.x > m_RenderPosition.x) m_RenderPosition.x += chipAnimationSpeed * ts;
		else if (m_TargetPosition.x < m_RenderPosition.x) m_RenderPosition.x -= chipAnimationSpeed * ts;
		if (m_TargetPosition.y > m_RenderPosition.y) m_RenderPosition.y += chipAnimationSpeed * ts;
		else if (m_TargetPosition.y < m_RenderPosition.y) m_RenderPosition.y -= chipAnimationSpeed * ts;

		CalculateTexture();
	}

	void ChipStack::OnRender()
	{
		if (m_ChipAmount > 0 && m_RenderSize > 0.0f)
		{
			SolutionShelves::Renderer2D::DrawRotatedQuad({ m_RenderPosition.x, m_RenderPosition.y, 0.1f }, { m_RenderSize, m_RenderSize }, m_Rotation, m_ChipStackTexture);
		}
	}

	void ChipStack::OnImGuiRender()
	{
	}

	void ChipStack::CalculateTexture()
	{
		if ((m_RenderPosition != m_TargetPosition))
		{
			// Chips animation
			m_ChipStackTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_ChipsSpriteSheet, { 0.0f, 1.0f }, { 120.0f, 120.0f });
			return;
		}

		if (m_ChipAmount == 1)
		{
			// Single chip
			m_ChipStackTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_ChipsSpriteSheet, { 1.0f, 1.0f }, { 120.0f, 120.0f });
			return;
		}

		if (m_ChipAmount > 1 && m_ChipAmount <= 50)
		{
			// Very Few chips
			m_ChipStackTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_ChipsSpriteSheet, { 2.0f, 1.0f }, { 120.0f, 120.0f });
			return;
		}

		if (m_ChipAmount > 50 && m_ChipAmount <= 500)
		{
			// Few Chips
			m_ChipStackTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_ChipsSpriteSheet, { 3.0f, 1.0f }, { 120.0f, 120.0f });
			return;
		}

		if (m_ChipAmount > 500 && m_ChipAmount <= 5000)
		{
			// Normal Chips
			m_ChipStackTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_ChipsSpriteSheet, { 4.0f, 1.0f }, { 120.0f, 120.0f });
			return;
		}

		if (m_ChipAmount > 5000 && m_ChipAmount <= 15000)
		{
			// Lots Chips
			m_ChipStackTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_ChipsSpriteSheet, { 0.0f, 0.0f }, { 120.0f, 120.0f });
			return;
		}

		if (m_ChipAmount > 15000)
		{
			// Very Lots Chips
			m_ChipStackTexture = SolutionShelves::SubTexture2D::CreateFromCoords(m_ChipsSpriteSheet, { 1.0f, 0.0f }, { 120.0f, 120.0f });
			return;
		}

	}
}
