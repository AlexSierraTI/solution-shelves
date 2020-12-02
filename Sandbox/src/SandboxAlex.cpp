#include "SandboxAlex.h"

#include "ImGui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

SandboxAlex::SandboxAlex()
	: Layer("SandboxAlex"), m_Camera()
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
	m_Application->OnRender(m_Camera);
}

void SandboxAlex::OnImGuiRender()
{

}

void SandboxAlex::OnEvent(SolutionShelves::Event& e)
{
	m_Application->OnEvent(e);
}
