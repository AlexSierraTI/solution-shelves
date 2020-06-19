#pragma once

#include <SolutionShelves.h>

#include "Estudos/Fps.h"

class SandboxAlex : public SolutionShelves::Layer
{
public:
	SandboxAlex();
	virtual ~SandboxAlex() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(SolutionShelves::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(SolutionShelves::Event & e) override;
private:
	SolutionShelves::OrthographicCameraController m_CameraController;
	SolutionShelves::Ref<SolutionShelves::Texture2D> m_CheckerboardTexture;
	SolutionShelves::Ref<SolutionShelves::Texture2D> m_LuanaTexture;

	std::unique_ptr<PixelEngineWrapper> m_Application = nullptr;

};

