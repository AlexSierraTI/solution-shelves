#pragma once

#include "Entity.h"

#include "Card.h"

#include "ChipStack.h"

namespace PokerSS
{
	class Player : public Entity
	{
	public:
		Player(const std::string& name,
			   const SolutionShelves::Ref<SolutionShelves::Texture2D>& playerTextureLeft,
			   const SolutionShelves::Ref<SolutionShelves::Texture2D>& playerTextureRight,
			   const SolutionShelves::Ref<SolutionShelves::Texture2D>& dealerChip,
			   const SolutionShelves::Ref<SolutionShelves::Texture2D>& chipStackTexture);
		~Player();

		virtual void LoadAssets() override;

		virtual void OnUpdate(SolutionShelves::Timestep ts) override;
		virtual void OnRender() override;

		virtual void OnImGuiRender() override;

		std::string GetName() const { return m_Name; }
		bool GetInGame() const { return m_InGame; }
		uint32_t GetPoints() const { return m_Points; }
		std::string GetHandDescription() const { return m_HandDescription; }
		std::vector<SolutionShelves::Ref<Card>> GetHand() const { return m_Hand; }
		uint32_t GetBet() const { return m_Bet; }
		uint32_t GetChips() const { return m_Chips; }
		glm::vec3 GetDealerChipPosition() const { return m_DealerChipPosition; }
		Orientation GetOrientation() const { return m_Orientation; }
		bool GetIsAllIn();
		bool GetFlatCalled() const { return m_FlatCalled; }
		SidePot GetSidePot() const { return m_Sidepot; }

		void SetPosition(const glm::vec2& position);
		void SetLayoutPosition(const glm::vec2& position);
		void SetOrientation(Orientation orientation);
		void SetDealer(bool isDealer);
		void SetInGame(bool status) { m_InGame = status; }
		void SetPoints(uint32_t value) { m_Points = value; }
		void SetHandDescription(const std::string& description) { m_HandDescription = description; }
		void SetInAction(bool value) { m_InAction = value; }
		void SetFolded(bool value) { m_Folded = value; }
		void SetFlatCalled(bool value) { m_FlatCalled = value; }
		void AddSidePot(uint32_t valor);
		void SetSidePotAllInValue(uint32_t valor);

		void AddCard(const SolutionShelves::Ref<Card> card);
		void RemoveCard(const SolutionShelves::Ref<Card> card);
		void ClearHand();

		void AddChips(uint32_t value);
		void RemoveChips(uint32_t value);
		
		void AddBet(uint32_t value);
		void ClearBet();

		void PopEntities();
	private:
		void CalculateRenderPositions();
	private:
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_PlayerTextureLeft;
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_PlayerTextureRight;

		SolutionShelves::Ref<SolutionShelves::Texture2D> m_PlayerDrawTexture;
		
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_DealerChip;
		
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_ChipStackTexture;

		std::string m_Name;
		glm::vec2 m_Position;
		glm::vec2 m_GridPosition;
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
		SidePot m_Sidepot = SidePot(0, 0);
		bool m_InAction;
		bool m_Folded;
		bool m_FlatCalled;

		SolutionShelves::Ref<ChipStack> m_ChipStack;
		SolutionShelves::Ref<ChipStack> m_ChipStackBet;

	};

}
