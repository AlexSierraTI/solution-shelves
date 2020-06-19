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
	m_SpriteSheet = SolutionShelves::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 2.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
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
#if 0
	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		SS_PROFILE_SCOPE("Renderer Draw");
		SolutionShelves::Renderer2D::BeginScene(m_CameraController.GetCamera());
		SolutionShelves::Renderer2D::DrawRotatedQuad({ 1.0f,  0.0f }, { 0.8f,  0.8f }, glm::radians(-45.0f) , { 0.8f, 0.2f, 0.3f, 1.0f });
		SolutionShelves::Renderer2D::DrawQuad({ -1.0f,  0.0f }, { 0.8f,  0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		SolutionShelves::Renderer2D::DrawQuad({  0.5f, -0.5f }, { 0.5f,  0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		SolutionShelves::Renderer2D::DrawQuad({  0.0f,  0.0f, -0.2f }, { 20.0f,  20.0f }, m_CheckerboardTexture, 10.0f);
		SolutionShelves::Renderer2D::DrawRotatedQuad({ -2.0f,  0.0f, 0.15f }, { 1.0f,  1.0f }, glm::radians(rotation), m_LuanaTexture, 1.0f);
		SolutionShelves::Renderer2D::EndScene();

		SolutionShelves::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.f, 0.4f, (y + 5.0f) / 10.f, 0.7f };
				SolutionShelves::Renderer2D::DrawQuad({ x, y, -0.1f }, { 0.45f,  0.45f }, color);
			}

		}
		SolutionShelves::Renderer2D::EndScene();
	}
#endif

	if (SolutionShelves::Input::IsMouseButtonPressed(SS_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = SolutionShelves::Input::GetMousePosition();
		auto width = SolutionShelves::Application::Get().GetWindow().GetWidth();
		auto height = SolutionShelves::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 25; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	SolutionShelves::Renderer2D::BeginScene(m_CameraController.GetCamera());
	SolutionShelves::Renderer2D::DrawQuad({ 0.0f,  0.0f, 0.0f }, { 1.0f,  1.0f }, m_SpriteSheet);
	SolutionShelves::Renderer2D::EndScene();

	
	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

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

	 ImGui::End();
}

void Sandbox2D::OnEvent(SolutionShelves::Event& e)
{
	m_CameraController.OnEvent(e);
}
