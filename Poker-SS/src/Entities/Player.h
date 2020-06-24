#pragma once

#include "Entity.h"

#include "Card.h"

namespace PokerSS
{
	class Player : public Entity
	{
	public:
		Player(const std::string& name);
		~Player();

		virtual void LoadAssets() override;

		virtual void OnUpdate(SolutionShelves::Timestep ts) override;
		virtual void OnRender() override;

		virtual void OnImGuiRender() override;

		std::string GetName() const { return m_Name; }
		bool GetInGame() const { return m_InGame; }
		bool GetPoints() const { return m_Points; }
		std::string GetHandDescription() const { return m_HandDescription; }
		std::vector<SolutionShelves::Ref<Card>> GetHand() const { return m_Hand; }
		uint32_t GetBet() const { return m_Bet; }
		uint32_t GetChips() const { return m_Chips; }
		bool GetIsAllinn() const { return m_AllIn; }

		void SetPosition(const glm::vec2& position);
		void SetOrientation(Orientation orientation);
		void SetDealer(bool isDealer);
		void SetInGame(bool status) { m_InGame = status; }
		void SetPoints(uint32_t value) { m_Points = value; }
		void SetHandDescription(const std::string& description) { m_HandDescription = description; }
		void SetAllIn(bool value) { m_AllIn = value; }

		void AddCard(const SolutionShelves::Ref<Card> card);
		void RemoveCard(const SolutionShelves::Ref<Card> card);
		void ClearHand();

		void AddChips(uint32_t value);
		void RemoveChips(uint32_t value);
		
		void AddBet(uint32_t value) { m_Bet += value; }
		void ClearBet() { m_Bet = 0; }
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

		std::vector<SolutionShelves::Ref<Card>> m_Hand;
		bool m_InGame;
		uint32_t m_Points;
		std::string m_HandDescription;
		uint32_t m_Chips;
		uint32_t m_Bet;
		bool m_AllIn;

	};

}
