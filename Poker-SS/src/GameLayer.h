#pragma once

#include <SolutionShelves.h>

#include "EntityManager.h"
#include "EntityList.h"

namespace PokerSS
{
	class GameLayer : public SolutionShelves::Layer
	{
	public:
		GameLayer();
		virtual ~GameLayer() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(SolutionShelves::Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(SolutionShelves::Event& e) override;
		bool OnMouseButtonPressed(SolutionShelves::MouseButtonPressedEvent& e);

		void SetDealer(const std::string& dealerName);
	private:
		void CreateCamera(uint32_t width, uint32_t height);
		void CreateDeck();
		glm::vec2 CalculateLayoutPosition(float x, float y);
	private:
		std::string m_DealerName;

		SolutionShelves::Scope<SolutionShelves::OrthographicCamera> m_Camera;

		SolutionShelves::Ref<SolutionShelves::FrameBuffer> m_FrameBuffer;
		glm::vec2 m_ViewportSize = { 1280.0f, 720.0f };

		SolutionShelves::Scope<EntityManager> m_EntityManager;

		// Spritesheets
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_CardSpriteSheet;
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_CardBackSpriteSheet;

		// Layout
		float m_MapWidth;
		float m_MapHeight;

		// Entities
		SolutionShelves::Ref<OldWest> m_LevelOldWest;
		std::unordered_map<std::string, SolutionShelves::Ref<Player>> m_PlayerList;

		// Deck
		std::queue<SolutionShelves::Ref<Card>> m_Deck;
		std::vector<SolutionShelves::Ref<Card>> m_Muck;
	};
}

