#pragma once

#include "Core/Base.h"

#include "Core/EntityList.h"

#include "Rules/TexasHoldem.h"

#include "Entities/Levels/Level.h"
#include "Entities/Controle.h"

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
		bool OnWindowResizeEvent(SolutionShelves::WindowResizeEvent& e);
	private:
		void Init();
		void SetCamera();
		void CalculateLayoutPositions(const std::vector<SolutionShelves::Ref<Player>> players, const SolutionShelves::Ref<Level> level);
		void AddPlayersEntities();
		void MainLayerImGuiGameElements();
	private:
		uint64_t m_Frames;
		float m_DeltaTs;

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		SolutionShelves::Scope<SolutionShelves::OrthographicCamera> m_Camera;

		SolutionShelves::Ref<SolutionShelves::FrameBuffer> m_FrameBuffer;
		glm::vec2 m_ViewportSize = { 1280.0f, 720.0f };

		// Layout
		float m_AspectRatio;
		glm::vec4 m_Bounds;

		// Entities
		SolutionShelves::Ref<OldWest> m_LevelOldWest;
		SolutionShelves::Ref<Controle> m_Controle;
		
		int32_t m_EntityCount;

		// EngineJogo
		SolutionShelves::Ref<TexasHoldem::TexasHoldem> m_EngineJogo;

		ImFont* m_FontDefault;
		ImFont* m_FontOpenSans;
	};
}

