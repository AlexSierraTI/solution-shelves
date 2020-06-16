#include "Sandbox2D.h"

#include "ImGui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{


}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(SolutionShelves::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);


	// Render
	// SolutionShelves::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	// SolutionShelves::RenderCommand::Clear();

	SolutionShelves::Renderer2D::BeginScene(m_CameraController.GetCamera());
	SolutionShelves::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f, 0.8f },  { 0.8f, 0.2f, 0.3f, 1.0f });
	SolutionShelves::Renderer2D::DrawQuad({  0.5f, -0.5f }, { 0.5f, 0.75f }, { m_SquareColor });
	SolutionShelves::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Cor sb2d");
	ImGui::ColorEdit4("Cor", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(SolutionShelves::Event& e)
{
	m_CameraController.OnEvent(e);
}
