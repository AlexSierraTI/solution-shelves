#pragma once

#include <SolutionShelves.h>

#include "Server.h"

namespace PokerSS
{
	class MainLayer : public SolutionShelves::Layer
	{
	public:
		MainLayer();
		virtual ~MainLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(SolutionShelves::Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(SolutionShelves::Event& e) override;
	private:
		bool OnKeyPressed(SolutionShelves::KeyPressedEvent& e);

	private:
		SolutionShelves::OrthographicCameraController m_CameraController;

		SolutionShelves::Ref<SolutionShelves::FrameBuffer> m_FrameBuffer;

		SolutionShelves::Ref<SolutionShelves::Scene> m_ActiveScene;

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		glm::vec2 m_ViewportSize = { 1280.0f, 720.0f };

		SolutionShelves::Entity m_CameraEntity;

		Server m_Servidor;
	};
}

