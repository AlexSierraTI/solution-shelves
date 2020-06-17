#include "Sandbox2D.h"

#include "ImGui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

#include "Util.h"

#include <chrono>

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = SolutionShelves::Texture2D::Create("assets/textures/Checkerboard.png");
	m_LuanaTexture = SolutionShelves::Texture2D::Create("assets/textures/luana.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(SolutionShelves::Timestep ts)
{
	SS_PROFILE_FUNCTION();
	// Update
	{
		SS_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		SS_PROFILE_SCOPE("Renderer Prep");
		SolutionShelves::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		SolutionShelves::RenderCommand::Clear();
	}

	{
		SS_PROFILE_SCOPE("Renderer Draw");
		SolutionShelves::Renderer2D::BeginScene(m_CameraController.GetCamera());
		SolutionShelves::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f,  0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		SolutionShelves::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f,  0.75f }, { m_SquareColor });
		SolutionShelves::Renderer2D::DrawQuad({ 0.0f,  0.0f, -0.1f }, { 10.0f,  10.0f }, m_CheckerboardTexture);
		SolutionShelves::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	SS_PROFILE_FUNCTION();

	ImGui::Begin("Cor sb2d");
	ImGui::ColorEdit4("Cor", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(SolutionShelves::Event& e)
{
	m_CameraController.OnEvent(e);
}
