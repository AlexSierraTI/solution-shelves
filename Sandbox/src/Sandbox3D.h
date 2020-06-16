#pragma once

#include <SolutionShelves.h>

class Sandbox3D : public SolutionShelves::Layer
{
public:
	Sandbox3D();
	virtual ~Sandbox3D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(SolutionShelves::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(SolutionShelves::Event& e) override;

private:
	SolutionShelves::ShaderLibrary m_ShaderLibrary;
	SolutionShelves::Ref<SolutionShelves::Shader> m_Shader;
	SolutionShelves::Ref<SolutionShelves::VertexArray> m_VertexArray;

	SolutionShelves::Ref<SolutionShelves::Shader> m_FlatColorShader;
	SolutionShelves::Ref<SolutionShelves::VertexArray> m_SquareVA;

	SolutionShelves::Ref<SolutionShelves::Texture2D> m_Texture;
	SolutionShelves::Ref<SolutionShelves::Texture2D> m_LuanaTexture;

	SolutionShelves::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

