#pragma once

#include <SolutionShelves.h>

#include "ParticleSystem.h"

#include "Pratica.h"

class Sandbox2D : public SolutionShelves::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(SolutionShelves::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(SolutionShelves::Event& e) override;
private:
	SolutionShelves::OrthographicCameraController m_CameraController;
	SolutionShelves::Ref<SolutionShelves::Texture2D> m_CheckerboardTexture;
	SolutionShelves::Ref<SolutionShelves::Texture2D> m_LuanaTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

	std::unique_ptr<Pratica> m_Pratica = nullptr;
};

