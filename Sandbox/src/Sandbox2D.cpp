#include "Sandbox2D.h"

#include "ImGui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	SS_PROFILE_FUNCTION();

	m_CheckerboardTexture = SolutionShelves::Texture2D::Create("assets/textures/Checkerboard.png");
	m_LuanaTexture = SolutionShelves::Texture2D::Create("assets/textures/luana.png");
}

void Sandbox2D::OnDetach()
{
	SS_PROFILE_FUNCTION();


}

void Sandbox2D::OnUpdate(SolutionShelves::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	SolutionShelves::Renderer2D::ResetStats();
	{
		SS_PROFILE_SCOPE("Renderer Prep");

		SolutionShelves::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		SolutionShelves::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		SS_PROFILE_SCOPE("Renderer Draw");
		SolutionShelves::Renderer2D::BeginScene(m_CameraController.GetCamera());
		SolutionShelves::Renderer2D::DrawRotatedQuad({ 1.0f,  0.0f }, { 0.8f,  0.8f }, -45.0f , { 0.8f, 0.2f, 0.3f, 1.0f });
		SolutionShelves::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f,  0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		SolutionShelves::Renderer2D::DrawQuad({  0.5f, -0.5f }, { 0.5f,  0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		SolutionShelves::Renderer2D::DrawQuad({  0.0f,  0.0f, -0.1f }, { 20.0f,  20.0f }, m_CheckerboardTexture, 10.0f);
		SolutionShelves::Renderer2D::DrawRotatedQuad({  -2.0f,  0.0f, 0.0f }, {  1.0f,  1.0f }, rotation, m_CheckerboardTexture, 20.0f);
		SolutionShelves::Renderer2D::EndScene();

		SolutionShelves::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.f, 0.4f, (y + 5.0f) / 10.f, 0.7f };
				SolutionShelves::Renderer2D::DrawQuad({ x, y }, { 0.45f,  0.45f }, color);
			}

		}
		SolutionShelves::Renderer2D::EndScene();

	}
}

void Sandbox2D::OnImGuiRender()
{
	SS_PROFILE_FUNCTION();

	 ImGui::Begin("Config");

	 auto stats = SolutionShelves::Renderer2D::GetStats();
	 ImGui::Text("Renderer2D Stats: ");
	 ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	 ImGui::Text("Quads: %d", stats.QuadCount);
	 ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	 ImGui::Text("Indices: %d", stats.GetTotalIndexCount());


	// ImGui::ColorEdit4("Cor", glm::value_ptr(m_SquareColor));
	 ImGui::End();
}

void Sandbox2D::OnEvent(SolutionShelves::Event& e)
{
	m_CameraController.OnEvent(e);
}
