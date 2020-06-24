#pragma once

#include "Entity.h"

namespace PokerSS
{
	class Card : public Entity
	{
	public:
		Card(const SolutionShelves::Ref<SolutionShelves::Texture2D>& cardSpriteSheet,
			 const SolutionShelves::Ref<SolutionShelves::Texture2D>& cardBackSpriteSheet,
		 	 CardBack cardBack, FaceValue faceValue = FaceValue::Unknown, Suit suit = Suit::Unknown);
		~Card();

		virtual void LoadAssets() override;

		virtual void OnUpdate(SolutionShelves::Timestep ts) override;
		virtual void OnRender() override;

		virtual void OnImGuiRender() override;

		void SetRenderPosition(const glm::vec2& renderPosition) { m_TargetPosition = renderPosition; }
		void SetRenderSize(float renderSize) { m_RenderSize = renderSize; }
		void SetRenderRotation(float rotation) { m_Rotation = rotation; }

		void SetCardValue(FaceValue faceValue, Suit suit);

		std::string GetCardDescription();
		FaceValue GetCardFaceValue() const { return m_FaceValue; }
		Suit GetCardSuit() const { return m_Suit; }
	private:
		void CalculateTexture();
	private:
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_CardSpriteSheet;
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_CardBackSpriteSheet;
		SolutionShelves::Ref<SolutionShelves::SubTexture2D> m_CardTexture;
		
		glm::vec2 m_RenderPosition;
		glm::vec2 m_TargetPosition;
		float m_RenderSize;
		float m_Rotation;

		Suit m_Suit;
		FaceValue m_FaceValue;
		CardBack m_CardBack;
	};
}

