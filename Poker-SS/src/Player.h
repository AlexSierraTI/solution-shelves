#pragma once

#include "Entity.h"

#include "Card.h"

namespace PokerSS
{

	enum class Orientation
	{
		LEFT, RIGHT, DOWN, UP
	};

	class Player : public Entity
	{
	public:
		Player(const std::string& name, const glm::vec2& position, Orientation orientation);
		~Player();

		virtual void LoadAssets() override;

		virtual void OnUpdate(SolutionShelves::Timestep ts) override;
		virtual void OnRender() override;

		virtual void OnImGuiRender() override;

		std::string GetName() const { return m_Name; }

		void SetPosition(const glm::vec2& position);
		void SetDealer(bool isDealer);

		void AddCard(const SolutionShelves::Ref<Card> card);
		void RemoveCard(const SolutionShelves::Ref<Card> card);
		void ClearHand();
	private:
		void CalculateRenderPositions();
	private:
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_PlayerTextureLeft;
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_PlayerTextureRight;

		SolutionShelves::Ref<SolutionShelves::Texture2D> m_PlayerDrawTexture;
		
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_DealerChip;

		std::string m_Name;
		glm::vec2 m_Position;
		glm::vec2 m_PlayerSize;

		Orientation m_Orientation;

		bool m_Dealer = false;
		glm::vec3 m_DealerChipPosition;
		glm::vec2 m_DealerChipSize;

		float m_CardSize;

		std::unordered_map<uint32_t, SolutionShelves::Ref<Card>> m_Hand;
	};

}
