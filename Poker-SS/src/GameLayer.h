#pragma once

#include "Core/Base.h"

#include "Core/EntityManager.h"
#include "Core/EntityList.h"

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

		void SetDealer(uint32_t pos);

		void AddPlayer(const std::string& name);
	private:
		void SetCamera();
		void CreateDeck();
		void CalculateLayoutPositions();
	private:
		uint64_t m_Frames;
		float m_DeltaTs;

		uint32_t m_DealerCurrent;

		SolutionShelves::Scope<SolutionShelves::OrthographicCamera> m_Camera;

		SolutionShelves::Ref<SolutionShelves::FrameBuffer> m_FrameBuffer;
		glm::vec2 m_ViewportSize = { 1280.0f, 720.0f };

		SolutionShelves::Scope<EntityManager> m_EntityManager;

		// Spritesheets
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_CardSpriteSheet;
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_CardBackSpriteSheet;

		// Layout
		float m_AspectRatio;
		glm::vec4 m_Bounds;

		// Entities
		SolutionShelves::Ref<OldWest> m_LevelOldWest;
		std::vector<SolutionShelves::Ref<Player>> m_PlayerList;

		// Deck
		std::queue<SolutionShelves::Ref<Card>> m_Deck;
		std::vector<SolutionShelves::Ref<Card>> m_Muck;
	};
}

