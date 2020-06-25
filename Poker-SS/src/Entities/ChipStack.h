#pragma once

#include "Entity.h"

namespace PokerSS
{
	class ChipStack : public Entity
	{
	public:
		ChipStack(const SolutionShelves::Ref<SolutionShelves::Texture2D>& chipsSpriteSheet);
		~ChipStack();

		virtual void LoadAssets() override;

		virtual void OnUpdate(SolutionShelves::Timestep ts) override;
		virtual void OnRender() override;

		virtual void OnImGuiRender() override;

		void SetRenderPosition(const glm::vec2& renderPosition) { m_TargetPosition = renderPosition; }
		void SetRenderSize(float renderSize) { m_RenderSize = renderSize; }
		void SetRenderRotation(float rotation) { m_Rotation = rotation; }

		glm::vec2 GetRenderPosition() const { return m_RenderPosition; }

		uint32_t GetChipAmount() const { return m_ChipAmount; }

		void SetChipAmount(uint32_t value) { m_ChipAmount = value; CalculateTexture(); }
	private:
		void CalculateTexture();
	private:
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_ChipsSpriteSheet;
		SolutionShelves::Ref<SolutionShelves::SubTexture2D> m_ChipStackTexture;

		glm::vec2 m_RenderPosition;
		glm::vec2 m_TargetPosition;
		float m_RenderSize;
		float m_Rotation;

		uint32_t m_ChipAmount;

	};
}

