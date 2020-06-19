#pragma once

#include <SolutionShelves.h>

#include "ParticleSystem.h"

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
	SolutionShelves::Ref<SolutionShelves::Texture2D> m_SpriteSheet;
	SolutionShelves::Ref<SolutionShelves::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

	size_t m_MapWidth, m_MapHeight;
	std::unordered_map<char, SolutionShelves::Ref<SolutionShelves::SubTexture2D>> s_TextureMap;
};

