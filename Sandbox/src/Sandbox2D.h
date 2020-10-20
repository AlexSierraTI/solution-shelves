#pragma once

#include <SolutionShelves.h>

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
	SolutionShelves::Camera m_Camera;

	SolutionShelves::Ref<SolutionShelves::Texture2D> m_CheckerboardTexture;
};

