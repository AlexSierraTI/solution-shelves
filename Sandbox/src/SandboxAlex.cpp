#include "SandboxAlex.h"

#include "ImGui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

SandboxAlex::SandboxAlex()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
	m_Application = std::make_unique<Fps>(800, 450, 4);
}

void SandboxAlex::OnAttach()
{
}

void SandboxAlex::OnDetach()
{
}

void SandboxAlex::OnUpdate(SolutionShelves::Timestep ts)
{
	SolutionShelves::Renderer2D::ResetStats();

	SolutionShelves::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	SolutionShelves::RenderCommand::Clear();

	m_Application->OnUpdate(ts);
	m_Application->OnRender(m_CameraController);
}

void SandboxAlex::OnImGuiRender()
{
	/*
	ImGui::Begin("Config");

	auto stats = SolutionShelves::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::End();
	*/
}

void SandboxAlex::OnEvent(SolutionShelves::Event& e)
{
	m_Application->OnEvent(e);
}
