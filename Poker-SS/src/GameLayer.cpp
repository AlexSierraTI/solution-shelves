#include "GameLayer.h"

#include <random>

#include "ImGui/imgui.h"

#include "Core/EntityManager.h"

namespace PokerSS
{
	GameLayer::GameLayer()
		: SolutionShelves::Layer("Sandbox2D"), m_Camera(nullptr)
	{
		// FPS
		m_Frames = 0;
		m_DeltaTs = 0.0f;

		// Janela
		auto& window = SolutionShelves::Application::Get().GetWindow();
		m_ViewportSize = { (float)window.GetWidth(), (float)window.GetHeight() };
		SetCamera();

		Init();
	}

	void GameLayer::OnAttach()
	{
		SS_PROFILE_FUNCTION();

		SolutionShelves::FrameBufferSpecification fbSpec(1280, 720);
		m_FrameBuffer = SolutionShelves::FrameBuffer::Create(fbSpec);

		ImGuiIO io = ImGui::GetIO();
		m_FontDefault = io.Fonts->AddFontDefault();
		m_FontOpenSans = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 120.0f);
		io.Fonts->AddFontFromFileTTF("assets/SummitBold-Display.ttf", 120.0f);
		
	}

	void GameLayer::OnDetach()
	{
		SS_PROFILE_FUNCTION();
	}

	void GameLayer::OnUpdate(SolutionShelves::Timestep ts)
	{
		AddPlayersEntities();

		// Update
		EntityManager::Get().UpdateEntities(ts);
		if (EntityManager::Get().GetEntitiesCount() != m_EntityCount)
		{
			CalculateLayoutPositions(m_EngineJogo->GetJogadores(), m_LevelOldWest);
			m_EntityCount = EntityManager::Get().GetEntitiesCount();
		}

		// Render
		SolutionShelves::Renderer2D::ResetStats();

		{
			SS_PROFILE_SCOPE("Renderer Prep");
			
			m_FrameBuffer->Bind();
			// Resize
			if (SolutionShelves::FrameBufferSpecification spec = m_FrameBuffer->GetSpecification();
				m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
				(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
			{
				m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
				SetCamera();
				CalculateLayoutPositions(m_EngineJogo->GetJogadores(), m_LevelOldWest);
			}
			
			SolutionShelves::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			SolutionShelves::RenderCommand::Clear();
		}
		{
			SS_PROFILE_SCOPE("Renderer Draw");
			SolutionShelves::Renderer2D::BeginScene(*m_Camera);
			EntityManager::Get().RenderEntities();
			SolutionShelves::Renderer2D::EndScene();

			m_FrameBuffer->Unbind();
		}

		m_Frames++;
		m_DeltaTs += ts.GetSeconds();
		if (m_DeltaTs >= 1.0f)
		{
			SS_CORE_INFO("{0} FPS", m_Frames);
			m_DeltaTs = 0.0f;
			m_Frames = 0;
		}

	}

	void GameLayer::OnImGuiRender()
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
		ImGui::Begin("MyDockSpace", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Arquivo"))
			{
				if (ImGui::MenuItem("Sair")) SolutionShelves::Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
		ImGui::End();


		ImGui::Begin("Log");
		auto log = m_EngineJogo->GetLog();
		auto logIndex = log->size();
		while (logIndex != 0)
		{
			ImGui::TextWrapped("%s", log->at(logIndex - 1).c_str());
			logIndex--;
		}

		ImGui::End();

		ImGui::Begin("Config");

		auto stats = SolutionShelves::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats: ");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

		ImGui::Begin("Viewport");

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		MainLayerImGuiGameElements();
		ImGui::End();
		ImGui::PopStyleVar();

		EntityManager::Get().ImGuiRender();
	}

	void GameLayer::OnEvent(SolutionShelves::Event& e)
	{
		SolutionShelves::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<SolutionShelves::MouseButtonPressedEvent>(SS_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
	}

	bool GameLayer::OnMouseButtonPressed(SolutionShelves::MouseButtonPressedEvent& e)
	{
	
		return false;
	}

	void GameLayer::Init()
	{
		EntityManager::CreateInstance();

		m_LevelOldWest = SolutionShelves::CreateRef<OldWest>();
		m_LevelOldWest->EnableRender();
		EntityManager::Get().PushEntity(m_LevelOldWest);
		m_EntityCount++;

		// Engine Regras
		m_EngineJogo = SolutionShelves::CreateScope<TexasHoldem::TexasHoldem>();

		// Controle
		m_Controle = SolutionShelves::CreateScope<Controle>(m_EngineJogo);
		m_Controle->EnableRender();
		EntityManager::Get().PushEntity(m_Controle);
		m_EntityCount++;
	}

	void GameLayer::SetCamera()
	{
		m_AspectRatio = m_ViewportSize.x / m_ViewportSize.y;

		float camWidth = 1.0f;
		float bottom = -camWidth;
		float top = camWidth;
		float left = bottom * m_AspectRatio;
		float right = top * m_AspectRatio;
		m_Bounds = { left, right, bottom, top};

		if (m_Camera)
		{
			m_Camera->SetProjection(left, right, bottom, top);
		}
		else
		{
			m_Camera = SolutionShelves::CreateScope<SolutionShelves::OrthographicCamera>(left, right, bottom, top);
		}
	}

	void GameLayer::CalculateLayoutPositions(const std::vector<SolutionShelves::Ref<Player>> players, const SolutionShelves::Ref<Level> level)
	{
		for (uint32_t index = 0; index < players.size(); index++)
		{
			glm::vec2 playerLevelPosition = level->GetPlayerData(index).Position;
			Orientation playerOrientation = level->GetPlayerData(index).Direction;
			glm::vec2 levelLayout = level->GetMapLayout();
			players[index]->SetOrientation(playerOrientation);
			float viewPortWidth = -m_Bounds.x + m_Bounds.y;
			float viewPortHeight = -m_Bounds.z + m_Bounds.w;
			float playerPosX = playerLevelPosition.x / levelLayout.x * viewPortWidth + m_Bounds.x;
			float playerPosY = m_Bounds.w - playerLevelPosition.y / levelLayout.y * viewPortHeight;
			float playerLayoutPosX = playerLevelPosition.x / levelLayout.x * m_ViewportSize.x;
			float playerLayoutPosY = playerLevelPosition.y / levelLayout.y * m_ViewportSize.y;
			players[index]->SetPosition({ playerPosX,  playerPosY });
			players[index]->SetLayoutPosition({ playerLayoutPosX,  playerLayoutPosY });
		}
	}

	void GameLayer::AddPlayersEntities()
	{
		
		for (auto& it : m_EngineJogo->GetJogadores())
		{
			// Cards
			for (auto& it2 : it->GetHand()) 
			{
				if (it2->GetEntityID() == 0)
				{
					EntityManager::Get().PushEntity(it2);
				}
			}
		}

		// Baralho
		for (auto& it : m_EngineJogo->GetBaralho())
		{
			if (it->GetEntityID() == 0)
			{
				EntityManager::Get().PushEntity(it);
			}
		}

		// Mesa
		for (auto& it : m_EngineJogo->GetMesa())
		{
			if (it->GetEntityID() == 0)
			{
				EntityManager::Get().PushEntity(it);
			}
		}

		// Muck
		for (auto& it : m_EngineJogo->GetMuck())
		{
			if (it->GetEntityID() == 0)
			{
				EntityManager::Get().PushEntity(it);
			}
		}

	}

	void PokerSS::GameLayer::MainLayerImGuiGameElements()
	{
		switch (m_EngineJogo->GetEstadoJogo())
		{
		case TexasHoldem::EstadoJogo::Jogo:
			std::string stackSize = std::string("$ ") + std::to_string(m_EngineJogo->GetPote());
			auto pos = ImGui::GetWindowPos();
			float width = m_ViewportSize.x;
			float height = m_ViewportSize.y;
			pos.x += width * 0.5f;
			pos.y += height * 0.5f;
			ImGui::PushFont(m_FontOpenSans);
			ImGui::GetForegroundDrawList()->AddText(m_FontOpenSans, 36.0f, pos, 0xffffffff, stackSize.c_str());
			ImGui::PopFont();
			break;
		}

	}


}