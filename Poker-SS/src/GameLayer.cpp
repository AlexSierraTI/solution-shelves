#include "GameLayer.h"

#include "ImGui/imgui.h"

#include <random>

namespace PokerSS
{
	GameLayer::GameLayer()
		: SolutionShelves::Layer("Sandbox2D"), m_Camera(nullptr)
	{
		// FPS
		m_Frames = 0;
		m_DeltaTs = 0.0f;

		auto& window = SolutionShelves::Application::Get().GetWindow();
		m_ViewportSize = { (float)window.GetWidth(), (float)window.GetHeight() };
		SetCamera();

		// Loading Spritesheets
		m_CardSpriteSheet = SolutionShelves::Texture2D::Create("assets/textures/playingCards.png");
		m_CardBackSpriteSheet = SolutionShelves::Texture2D::Create("assets/textures/playingCardBacks.png");
		
		AddPlayer("Marcos");
		AddPlayer("Joao");
		AddPlayer("Sergio");
		AddPlayer("Ueta");

		SetDealer(m_DealerCurrent);

		m_EntityManager = SolutionShelves::CreateScope<EntityManager>();

		// Background
		m_LevelOldWest = SolutionShelves::CreateRef<OldWest>();
		m_LevelOldWest->EnableRender();
		m_EntityManager->PushEntity(m_LevelOldWest);

		// Players
		for (auto& it : m_PlayerList) 
		{
			it->EnableRender();
			m_EntityManager->PushEntity(it);
		}

		// Deck 
		CreateDeck();

		CalculateLayoutPositions();
	}

	void GameLayer::OnAttach()
	{
		SS_PROFILE_FUNCTION();

		SolutionShelves::FrameBufferSpecification fbSpec(1280, 720);
		m_FrameBuffer = SolutionShelves::FrameBuffer::Create(fbSpec);
	}

	void GameLayer::OnDetach()
	{
		SS_PROFILE_FUNCTION();
		m_EntityManager.release();
	}

	void GameLayer::OnUpdate(SolutionShelves::Timestep ts)
	{

		// Update
		m_EntityManager->UpdateEntities(ts);

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
				CalculateLayoutPositions();
			}
			
			SolutionShelves::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			SolutionShelves::RenderCommand::Clear();
		}
		{
			SS_PROFILE_SCOPE("Renderer Draw");
			SolutionShelves::Renderer2D::BeginScene(*m_Camera);
			m_EntityManager.get()->RenderEntities();
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
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
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
		ImGui::End();
		ImGui::PopStyleVar();


		ImGui::End();

		m_EntityManager->ImGuiRender();
	}

	void GameLayer::OnEvent(SolutionShelves::Event& e)
	{
		SolutionShelves::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<SolutionShelves::MouseButtonPressedEvent>(SS_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
	}

	bool GameLayer::OnMouseButtonPressed(SolutionShelves::MouseButtonPressedEvent& e)
	{
		if (m_PlayerList.size() == 0) return false;
		
		uint32_t nextDealer = (m_DealerCurrent + 1) % (uint32_t)m_PlayerList.size();
		SetDealer(nextDealer);
		
		uint32_t nextPlayer = (m_DealerCurrent + 1) % (uint32_t)m_PlayerList.size();
		m_PlayerList[nextPlayer]->AddCard(m_Deck.front());
		m_Deck.pop();

		return false;
	}

	void GameLayer::SetDealer(uint32_t pos)
	{
		for (auto& it : m_PlayerList)
			it->SetDealer(false);

		if (pos < m_PlayerList.size()) 
		{
			m_PlayerList[pos]->SetDealer(true);
			m_DealerCurrent = pos;
		}
	}

	void GameLayer::AddPlayer(const std::string& name)
	{
		m_PlayerList.push_back(SolutionShelves::CreateRef<Player>(Player(name)));
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

	void GameLayer::CreateDeck()
	{
		std::vector<SolutionShelves::Ref<Card>> v_SortedDeck;
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Ace,   Suit::Spades));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Deuce, Suit::Spades));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Tray,  Suit::Spades));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Four,  Suit::Spades));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Five,  Suit::Spades));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Six,   Suit::Spades));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Seven, Suit::Spades));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Eight, Suit::Spades));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Nine,  Suit::Spades));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Ten,   Suit::Spades));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Jack,  Suit::Spades));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Queen, Suit::Spades));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::King,  Suit::Spades));

		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Ace, Suit::Diamonds));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Deuce, Suit::Diamonds));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Tray, Suit::Diamonds));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Four, Suit::Diamonds));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Five, Suit::Diamonds));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Six, Suit::Diamonds));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Seven, Suit::Diamonds));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Eight, Suit::Diamonds));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Nine, Suit::Diamonds));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Ten, Suit::Diamonds));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Jack, Suit::Diamonds));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Queen, Suit::Diamonds));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::King, Suit::Diamonds));

		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Ace, Suit::Clubs));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Deuce, Suit::Clubs));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Tray, Suit::Clubs));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Four, Suit::Clubs));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Five, Suit::Clubs));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Six, Suit::Clubs));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Seven, Suit::Clubs));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Eight, Suit::Clubs));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Nine, Suit::Clubs));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Ten, Suit::Clubs));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Jack, Suit::Clubs));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Queen, Suit::Clubs));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::King, Suit::Clubs));

		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Ace, Suit::Hearts));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Deuce, Suit::Hearts));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Tray, Suit::Hearts));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Four, Suit::Hearts));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Five, Suit::Hearts));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Six, Suit::Hearts));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Seven, Suit::Hearts));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Eight, Suit::Hearts));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Nine, Suit::Hearts));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Ten, Suit::Hearts));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Jack, Suit::Hearts));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::Queen, Suit::Hearts));
		v_SortedDeck.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, CardBack::Red4Suits, FaceValue::King, Suit::Hearts));

		const uint32_t SHUFFLE_AMOUNT = 7;
		for (uint32_t i = 0; i < SHUFFLE_AMOUNT; i++)
		{
			uint32_t seed = static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count());
			std::shuffle(v_SortedDeck.begin(), v_SortedDeck.end(), std::default_random_engine(seed));
		}
			
		while (!m_Deck.empty())
		{
			m_EntityManager->PopEntity(m_Deck.front());
			m_Deck.pop();
		}

		for (auto& it : v_SortedDeck) 
		{
			m_EntityManager->PushEntity(it);
			m_Deck.push(it);
		}
	}

	void GameLayer::CalculateLayoutPositions()
	{
		for (uint32_t index = 0; index < m_PlayerList.size(); index++)
		{
			glm::vec2 playerLevelPosition = m_LevelOldWest->GetPlayerData(index).Position;
			Orientation playerOrientation = m_LevelOldWest->GetPlayerData(index).Direction;
			glm::vec2 levelLayout = m_LevelOldWest->GetMapLayout();
			m_PlayerList[index]->SetOrientation(playerOrientation);
			float viewPortWidth = -m_Bounds.x + m_Bounds.y;
			float viewPortHeight = -m_Bounds.z + m_Bounds.w;
			float playerPosX = playerLevelPosition.x / levelLayout.x * viewPortWidth + m_Bounds.x;
			float playerPosY = m_Bounds.w - playerLevelPosition.y / levelLayout.y * viewPortHeight;
			m_PlayerList[index]->SetPosition({ playerPosX,  playerPosY });
		}
	}
}