#include "Controle.h"

namespace PokerSS
{
	Controle::Controle(const SolutionShelves::Ref<TexasHoldem::TexasHoldem>& engineJogo)
		: m_EngineJogo(engineJogo), m_SelectedPlayer(-1)
	{
		m_NomeJogadorInclusao[0] = 0;
		m_MensagemErro[0] = 0;
		m_FichasAdicionar = 0;
		m_SelectedPlayer = -1;
		m_AcoesPossiveis.clear();
		m_Apostando = false;
		m_Aumentando = false;
		m_RemovendoFichas = false;

		m_PrimeiroFoco = false;
		
		m_Server = SolutionShelves::CreateRef<Server>();
		m_ServerThread = std::thread(&Server::Run, m_Server);

		LoadAssets();
		//AddPlayer("Marcos");
		//AddPlayer("Sergio");
		//AddPlayer("Ueta");
		//AddPlayer("Joao");
		//AddPlayer("Alb");
		//AddPlayer("Beb");
		//AddPlayer("Ceb");
		//AddPlayer("Ked");
		//AddPlayer("Bob");

	}

	Controle::~Controle()
	{
		m_ServerThread.join();
	}

	void Controle::LoadAssets()
	{

	}

	void Controle::OnUpdate(SolutionShelves::Timestep ts)
	{
		ChecarPodeComecarJogo();
	}

	void Controle::OnRender()
	{
	}

	

	void Controle::OnImGuiRender()
	{
		const float PLAYER_LIST_X = 180.0f;
		const float PLAYER_LIST_Y = 300.0f;
		const float PLAYER_LIST_CHIPS_PADDING = 20.0f;
		const float MAIN_MENU_X = 180.0f;
		const float MAIN_MENU_Y = 450.0f;
		const float BUTTON_SPACING = 25.0f;
		const float MAIN_MENU_BUTTON_X = 130.0f;
		const float MAIN_MENU_BUTTON_Y = 30.0f;

		const float ACTION_MENU_X = 180.0f;
		const float ACTION_MENU_Y = 200.0f;

		const float ACTION_MENU_BUTTON_X = 80.0f;
		const float ACTION_MENU_BUTTON_Y = 30.0f;
		const float ACTION_BUTTON_SPACING = 50.0f;

		const float DIALOG_X = 180.0f;
		const float DIALOG_Y = 130.0f;
		const float DIALOG_BUTTON_SPACING = 20.0f;
		const float DIALOG_BUTTON_X = 140.0f;
		const float DIALOG_BUTTON_Y = 30.0f;

		int32_t i = 0;
		static bool controleOpen = true;
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar;
		// window_flags |= ImGuiWindowFlags_NoMove;

		ImGui::Begin("Controle", NULL, window_flags);
		
		if (m_EngineJogo->GetAguardando())
		{
			// Aguardando engine
		}
		else
		{
			switch (m_EngineJogo->GetEstadoJogo())
			{
			case TexasHoldem::EstadoJogo::PreJogo:
				m_AcoesPossiveis.clear();
				ImGui::BeginChildFrame(ImGuiID(1004), ImVec2(MAIN_MENU_X, MAIN_MENU_Y));
				ImGui::ListBoxHeader("", ImVec2(PLAYER_LIST_X, PLAYER_LIST_Y));
				for (auto& it : m_EngineJogo->GetJogadores())
				{
					if (ImGui::Selectable(it->GetName().c_str(), i == m_SelectedPlayer))
					{
						m_SelectedPlayer = i;
					}
					
					ImGui::NewLine();
					ImGui::SameLine(PLAYER_LIST_CHIPS_PADDING);
					ImGui::Text("Fichas :");
					ImGui::SameLine();
					ImGui::Text("$ %ld", it->GetChips());
					i++;
				}
				ImGui::ListBoxFooter();
				ImGui::NewLine();
				ImGui::SameLine(BUTTON_SPACING);
				if (ImGui::Button("Adicionar Jogador", ImVec2(MAIN_MENU_BUTTON_X, MAIN_MENU_BUTTON_Y)))
				{
					m_PrimeiroFoco = true;
					m_AdicionandoJogador = true;
					m_AdicionandoFichas = false;
					m_RemovendoFichas = false;
				}
				if (m_SelectedPlayer != -1)
				{
					ImGui::NewLine();
					ImGui::SameLine(BUTTON_SPACING);
					if (ImGui::Button("Adicionar Fichas", ImVec2(MAIN_MENU_BUTTON_X, MAIN_MENU_BUTTON_Y)))
					{
						m_AdicionandoFichas = true;
						m_AdicionandoJogador = false;
						m_RemovendoFichas = false;
					}
				}
				if (m_SelectedPlayer != -1 && m_EngineJogo->GetJogadores()[m_SelectedPlayer]->GetChips() > 0)
				{
					ImGui::NewLine();
					ImGui::SameLine(BUTTON_SPACING);
					if (ImGui::Button("Remover Fichas", ImVec2(MAIN_MENU_BUTTON_X, MAIN_MENU_BUTTON_Y)))
					{
						m_RemovendoFichas = true;
						m_AdicionandoJogador = false;
						m_AdicionandoFichas = false;
					}
				}

				if (m_PodeComecarJogo)
				{
					ImGui::NewLine();
					ImGui::SameLine(BUTTON_SPACING);
					if (ImGui::Button("INICIAR!", ImVec2(MAIN_MENU_BUTTON_X, MAIN_MENU_BUTTON_Y)))
					{
						m_EngineJogo->Start();
						m_AdicionandoFichas = false;
						m_AdicionandoJogador = false;
						m_RemovendoFichas = false;
					}
				}

				ImGui::NewLine();
				ImGui::SameLine(BUTTON_SPACING);
				if (ImGui::Button("Teste Envio", ImVec2(MAIN_MENU_BUTTON_X, MAIN_MENU_BUTTON_Y)))
				{
					Client::Teste();
				}
				ImGui::EndChildFrame();
				break;
			case TexasHoldem::EstadoJogo::Jogo:
				ImGui::BeginChildFrame(ImGuiID(1006), ImVec2(ACTION_MENU_X, ACTION_MENU_Y));
				
				ImGui::NewLine();
				ImGui::NewLine();

				m_AcoesPossiveis.clear();
				m_AcoesPossiveis = m_EngineJogo->GetAcoesPossiveis();
				if (std::find(m_AcoesPossiveis.begin(), m_AcoesPossiveis.end(), TexasHoldem::AcoesJogador::Mesa) != m_AcoesPossiveis.end())
				{
					ImGui::NewLine();
					ImGui::SameLine(ACTION_BUTTON_SPACING);
					if (ImGui::Button("Mesa", ImVec2(ACTION_MENU_BUTTON_X, ACTION_MENU_BUTTON_Y)))
					{
						m_EngineJogo->AcaoJogador(TexasHoldem::AcoesJogador::Mesa, 0);
						m_Aumentando = false;
						m_Apostando = false;
					}
				}
				if (std::find(m_AcoesPossiveis.begin(), m_AcoesPossiveis.end(), TexasHoldem::AcoesJogador::Chamar) != m_AcoesPossiveis.end())
				{
					ImGui::NewLine();
					ImGui::SameLine(ACTION_BUTTON_SPACING);

					if (ImGui::Button("Chamar", ImVec2(ACTION_MENU_BUTTON_X, ACTION_MENU_BUTTON_Y)))
					{
						m_EngineJogo->AcaoJogador(TexasHoldem::AcoesJogador::Chamar, 0);
						m_Aumentando = false;
						m_Apostando = false;
					}
				}
				if (std::find(m_AcoesPossiveis.begin(), m_AcoesPossiveis.end(), TexasHoldem::AcoesJogador::Apostar) != m_AcoesPossiveis.end())
				{
					ImGui::NewLine();
					ImGui::SameLine(ACTION_BUTTON_SPACING);

					if (ImGui::Button("Apostar", ImVec2(ACTION_MENU_BUTTON_X, ACTION_MENU_BUTTON_Y)))
					{
						m_FichasAdicionar = m_EngineJogo->GetApostaMinima();
						m_Aumentando = false;
						m_Apostando = true;
					}
				}
				if (std::find(m_AcoesPossiveis.begin(), m_AcoesPossiveis.end(), TexasHoldem::AcoesJogador::Aumentar) != m_AcoesPossiveis.end())
				{
					ImGui::NewLine();
					ImGui::SameLine(ACTION_BUTTON_SPACING);

					if (ImGui::Button("Aumentar", ImVec2(ACTION_MENU_BUTTON_X, ACTION_MENU_BUTTON_Y)))
					{
						m_FichasAdicionar = m_EngineJogo->GetApostaMinima();
						m_Aumentando = true;
						m_Apostando = true;
					}
				}

				if (std::find(m_AcoesPossiveis.begin(), m_AcoesPossiveis.end(), TexasHoldem::AcoesJogador::Fugir) != m_AcoesPossiveis.end())
				{
					ImGui::NewLine();
					ImGui::SameLine(ACTION_BUTTON_SPACING);

					if (ImGui::Button("Fugir", ImVec2(ACTION_MENU_BUTTON_X, ACTION_MENU_BUTTON_Y)))
					{
						m_EngineJogo->AcaoJogador(TexasHoldem::AcoesJogador::Fugir, 0);
						m_Aumentando = false;
						m_Apostando = false;
					}
				}
				ImGui::EndChildFrame();

				break;
			case TexasHoldem::EstadoJogo::FimRodada:
				m_AcoesPossiveis.clear();

				break;
			case TexasHoldem::EstadoJogo::FimJogo:
				m_AcoesPossiveis.clear();
				ImGui::BeginChildFrame(ImGuiID(1006), ImVec2(ACTION_MENU_X, ACTION_MENU_Y));

				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::SameLine(DIALOG_BUTTON_SPACING);
				if (ImGui::Button("REINICIAR", ImVec2(DIALOG_BUTTON_X, DIALOG_BUTTON_Y)))
				{
					m_EngineJogo->ReinicializaEngine();
				}
				ImGui::EndChildFrame();
				break;
			}
		}

		if (m_AdicionandoFichas)
		{
			ImGui::BeginChildFrame(ImGuiID(1001), ImVec2(DIALOG_X, DIALOG_Y));
			ImGui::Text("%s - %d", m_EngineJogo->GetJogadores()[m_SelectedPlayer]->GetName().c_str(), m_EngineJogo->GetJogadores()[m_SelectedPlayer]->GetChips());
			ImGui::NewLine();
			ImGui::SameLine(DIALOG_BUTTON_SPACING);
			ImGui::DragInt("+", &m_FichasAdicionar, 200.0f, 0, 5000, "$ %d");

			ImGui::NewLine();
			ImGui::SameLine(DIALOG_BUTTON_SPACING);
			if (ImGui::Button("OK", ImVec2(DIALOG_BUTTON_X, DIALOG_BUTTON_Y)))
			{
				m_EngineJogo->GetJogadores()[m_SelectedPlayer]->AddChips(m_FichasAdicionar);
				m_AdicionandoFichas = false;
				m_FichasAdicionar = 0;
			}
			ImGui::NewLine();
			ImGui::SameLine(DIALOG_BUTTON_SPACING);
			if (ImGui::Button("Cancelar", ImVec2(DIALOG_BUTTON_X, DIALOG_BUTTON_Y)))
			{
				m_AdicionandoFichas = false;
				m_FichasAdicionar = 0;
			}
			ImGui::EndChildFrame();
		}

		if (m_RemovendoFichas)
		{
			ImGui::BeginChildFrame(ImGuiID(1002), ImVec2(DIALOG_X, DIALOG_Y));
			ImGui::Text("%s - %d", m_EngineJogo->GetJogadores()[m_SelectedPlayer]->GetName().c_str(), m_EngineJogo->GetJogadores()[m_SelectedPlayer]->GetChips());
			ImGui::NewLine();
			ImGui::SameLine(DIALOG_BUTTON_SPACING);
			ImGui::DragInt("-", &m_FichasAdicionar, 200.0f, 0, m_EngineJogo->GetJogadores()[m_SelectedPlayer]->GetChips(), "$ %d");
			ImGui::NewLine();
			ImGui::SameLine(DIALOG_BUTTON_SPACING);
			if (ImGui::Button("OK", ImVec2(DIALOG_BUTTON_X, DIALOG_BUTTON_Y)))
			{
				m_EngineJogo->GetJogadores()[m_SelectedPlayer]->RemoveChips(m_FichasAdicionar);
				m_RemovendoFichas = false;
				m_FichasAdicionar = 0;
			}
			ImGui::NewLine();
			ImGui::SameLine(DIALOG_BUTTON_SPACING);
			if (ImGui::Button("Cancelar", ImVec2(DIALOG_BUTTON_X, DIALOG_BUTTON_Y)))
			{
				m_RemovendoFichas = false;
				m_FichasAdicionar = 0;
			}
			ImGui::EndChildFrame();
		}

		if (m_AdicionandoJogador)
		{
			if (strlen(m_NomeJogadorInclusao))
			{
				sprintf_s(m_MensagemErro, "");
			}

			ImGui::BeginChildFrame(ImGuiID(1003), ImVec2(DIALOG_X, DIALOG_Y));

			if (!ImGui::IsAnyItemFocused() && m_PrimeiroFoco)
			{
				ImGui::SetKeyboardFocusHere();
				m_PrimeiroFoco = false;
			}
			ImGui::SameLine(DIALOG_BUTTON_SPACING);
			ImGui::InputText("Nome", m_NomeJogadorInclusao, sizeof(m_NomeJogadorInclusao));

			ImGui::NewLine();
			ImGui::SameLine(DIALOG_BUTTON_SPACING);
			if (ImGui::Button("OK", ImVec2(DIALOG_BUTTON_X, DIALOG_BUTTON_Y)) || ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
			{
				if (strlen(m_NomeJogadorInclusao))
				{
					AddPlayer(m_NomeJogadorInclusao);
					m_AdicionandoJogador = false;
					m_NomeJogadorInclusao[0] = 0;
				}
				else
				{
					sprintf_s(m_MensagemErro, "Preencha o nome do jogador");
				}
			}
			ImGui::NewLine();
			ImGui::SameLine(DIALOG_BUTTON_SPACING);
			if (ImGui::Button("Cancelar", ImVec2(DIALOG_BUTTON_X, DIALOG_BUTTON_Y)) || ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape)))
			{
				sprintf_s(m_NomeJogadorInclusao, "");
				m_AdicionandoJogador = false;
			}
			ImGui::Text(m_MensagemErro);

			ImGui::EndChildFrame();
		}

		if (m_Apostando)
		{
			ImGui::BeginChildFrame(ImGuiID(1005), ImVec2(DIALOG_X, DIALOG_Y));
			ImGui::Text("Minimo: %d - Maximo: %d", m_EngineJogo->GetApostaMinima(), m_EngineJogo->GetApostaMaxima());
			ImGui::NewLine();
			ImGui::SameLine(DIALOG_BUTTON_SPACING);
			ImGui::DragInt("+", &m_FichasAdicionar,
				m_EngineJogo->GetApostaMinima() == m_EngineJogo->GetApostaMaxima() ? 0.0f : 25.0f,
				m_EngineJogo->GetApostaMinima(), m_EngineJogo->GetApostaMaxima(), "$ %d");

			ImGui::NewLine();
			ImGui::SameLine(DIALOG_BUTTON_SPACING);
			if (ImGui::Button("OK", ImVec2(DIALOG_BUTTON_X, DIALOG_BUTTON_Y)))
			{
				if (m_Aumentando)
					m_EngineJogo->AcaoJogador(TexasHoldem::AcoesJogador::Aumentar, m_FichasAdicionar);
				else
					m_EngineJogo->AcaoJogador(TexasHoldem::AcoesJogador::Apostar, m_FichasAdicionar);

				m_Aumentando = false;
				m_Apostando = false;
				m_FichasAdicionar = 0;
			}
			ImGui::NewLine();
			ImGui::SameLine(DIALOG_BUTTON_SPACING);
			if (ImGui::Button("Cancelar", ImVec2(DIALOG_BUTTON_X, DIALOG_BUTTON_Y)))
			{
				m_Aumentando = false;
				m_Apostando = false;
				m_FichasAdicionar = 0;
			}
			ImGui::EndChildFrame();
		}


		ImGui::End();
	}

	void Controle::AddPlayer(const std::string& name)
	{
		m_EngineJogo->AdicionaJogador(name);
	}
	void Controle::AddChips(uint32_t playerIndex, uint32_t chipsAmount)
	{
		m_EngineJogo->AdicionaFichasJogador(playerIndex, chipsAmount);
	}

	void Controle::ChecarPodeComecarJogo()
	{
		auto& v_ListaJogadores = m_EngineJogo->GetJogadores();
		if (v_ListaJogadores.size() > 1)
		{
			bool todosComFicha = true;
			for (auto& it : v_ListaJogadores)
			{
				if (it->GetChips() == 0)
				{
					todosComFicha = false;
					break;
				}
			}
			m_PodeComecarJogo = todosComFicha;
		}
		else
		{
			m_PodeComecarJogo = false;
		}
	}
}