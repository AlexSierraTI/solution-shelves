#include "MainLayer.h"

#include "ImGui/imgui.h"

namespace PokerSS
{
	MainLayer::MainLayer()
		: Layer("MainLayer"), m_CameraController(1280.0f / 720.0f, true), m_Servidor((uint16_t)20051982)
	{
	}

	void MainLayer::OnAttach()
	{
		SS_PROFILE_FUNCTION();

		SolutionShelves::FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_FrameBuffer = SolutionShelves::FrameBuffer::Create(fbSpec);

		m_ActiveScene = SolutionShelves::CreateRef<SolutionShelves::Scene>();

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
		m_CameraEntity.AddComponent<SolutionShelves::CameraComponent>();

		m_Servidor.Start();
	}

	void MainLayer::OnDetach()
	{
		SS_PROFILE_FUNCTION();
		m_Servidor.Stop();
	}

	void MainLayer::OnUpdate(SolutionShelves::Timestep ts)
	{
		// Resize
		if (SolutionShelves::FrameBufferSpecification spec = m_FrameBuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		// Update
		m_Servidor.Update();

		// Render
		SolutionShelves::Renderer2D::ResetStats();
		m_FrameBuffer->Bind();
		SolutionShelves::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		SolutionShelves::RenderCommand::Clear();

		// Update Scene
		m_ActiveScene->OnUpdate(ts);

		m_FrameBuffer->Unbind();
	}

	void MainLayer::OnImGuiRender()
	{
		SS_PROFILE_FUNCTION();

		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSize = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSize;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Arquivo"))
			{
				if (ImGui::MenuItem("Sair")) 
					SolutionShelves::Application::Get().Close();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Stats");

		auto stats = SolutionShelves::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats: ");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		SolutionShelves::Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void MainLayer::OnEvent(SolutionShelves::Event& e)
	{
		SolutionShelves::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<SolutionShelves::KeyPressedEvent>(SS_BIND_EVENT_FN(MainLayer::OnKeyPressed));
	}
	bool MainLayer::OnKeyPressed(SolutionShelves::KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;

		bool control = SolutionShelves::Input::IsKeyPressed(SolutionShelves::Key::LeftControl) || 
			SolutionShelves::Input::IsKeyPressed(SolutionShelves::Key::RightControl);
		bool shift = SolutionShelves::Input::IsKeyPressed(SolutionShelves::Key::LeftShift) || 
			SolutionShelves::Input::IsKeyPressed(SolutionShelves::Key::RightShift);

		switch (e.GetKeyCode())
		{
			case SolutionShelves::Key::A:
			default:
				break;
		}
		return false;
	}

}
