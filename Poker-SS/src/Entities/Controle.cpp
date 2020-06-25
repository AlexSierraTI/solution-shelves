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

		m_PrimeiroFoco = false;

		LoadAssets();
		AddPlayer("Marcos");
		AddPlayer("Sergio");
		AddPlayer("Ueta");
		AddPlayer("Joao");

	}
	Controle::~Controle()
	{
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
		int32_t i = 0;
		ImGui::Begin("Controle");

		if (m_AdicionandoFichas)
		{
			ImGui::Begin("Adicionar Fichas");
			ImGui::Text("%s - %d", m_EngineJogo->GetJogadores()[m_SelectedPlayer]->GetName().c_str(), m_EngineJogo->GetJogadores()[m_SelectedPlayer]->GetChips());
			ImGui::DragInt("Adicionar", &m_FichasAdicionar, 200, 0, 5000, "$ %d");
			if (ImGui::Button("OK", ImVec2(100, 30)))
			{
				m_EngineJogo->GetJogadores()[m_SelectedPlayer]->AddChips(m_FichasAdicionar);
				m_AdicionandoFichas = false;
				m_FichasAdicionar = 0;
			}
			if (ImGui::Button("Cancelar", ImVec2(100, 30)))
			{
				m_AdicionandoFichas = false;
				m_FichasAdicionar = 0;
			}
			ImGui::End();
		}

		if (m_AdicionandoJogador)
		{
			if (strlen(m_NomeJogadorInclusao))
			{
				sprintf_s(m_MensagemErro, "");
			}

			ImGui::Begin("Adicionar Jogador");
			if (!ImGui::IsAnyItemFocused() && m_PrimeiroFoco)
			{
				ImGui::SetKeyboardFocusHere();
				m_PrimeiroFoco = false;
			}
			ImGui::InputText("Nome", m_NomeJogadorInclusao, sizeof(m_NomeJogadorInclusao));
			if (ImGui::Button("OK", ImVec2(100, 30)) || ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter)))
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
			if (ImGui::Button("Cancelar", ImVec2(100, 30)) || ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape)))
			{
				sprintf_s(m_NomeJogadorInclusao, "");
				m_AdicionandoJogador = false;
			}
			ImGui::Text(m_MensagemErro);
			
			ImGui::End();
		}

		switch (m_EngineJogo->GetEstadoJogo())
		{
		case TexasHoldem::EstadoJogo::PreJogo:
			m_AcoesPossiveis.clear();

			ImGui::ListBoxHeader("", ImVec2(250, 300));
			for (auto& it : m_EngineJogo->GetJogadores())
			{
				if (ImGui::Selectable(it->GetName().c_str(), i == m_SelectedPlayer))
				{
					m_SelectedPlayer = i;
				}
				ImGui::Text("    ");
				ImGui::SameLine();
				ImGui::Text("Fichas :");
				ImGui::SameLine();
				ImGui::Text("%ld", it->GetChips());
				i++;
			}
			ImGui::ListBoxFooter();
			if (ImGui::Button("Adicionar Jogador", ImVec2(150, 30)))
			{
				m_PrimeiroFoco = true;
				m_AdicionandoJogador = true;
			}
			if (m_SelectedPlayer != -1)
			{
				if (ImGui::Button("Adicionar Fichas", ImVec2(150, 30)))
				{
					m_AdicionandoFichas = true;
				}
			}

			if (m_PodeComecarJogo)
			{
				if (ImGui::Button("INICIAR!", ImVec2(150, 30)))
				{
					m_EngineJogo->Start();
				}
			}

			break;
		case TexasHoldem::EstadoJogo::Jogo:

			if (m_Apostando)
			{
				ImGui::Begin("Apostando");
				ImGui::Text("Minimo: %d - Maximo: %d", m_EngineJogo->GetApostaMinima(), m_EngineJogo->GetApostaMaxima());
				ImGui::DragInt("Adicionar", &m_FichasAdicionar, 25, m_EngineJogo->GetApostaMinima(), m_EngineJogo->GetApostaMaxima(), "$ %d");
				if (ImGui::Button("OK", ImVec2(100, 30)))
				{
					if (m_Aumentando)
						m_EngineJogo->AcaoJogador(TexasHoldem::AcoesJogador::Apostar, m_FichasAdicionar);
					else
						m_EngineJogo->AcaoJogador(TexasHoldem::AcoesJogador::Aumentar, m_FichasAdicionar);

					m_Aumentando = false;
					m_Apostando = false;
					m_FichasAdicionar = 0;
				}
				if (ImGui::Button("Cancelar", ImVec2(100, 30)))
				{
					m_Aumentando = false;
					m_Apostando = false;
					m_FichasAdicionar = 0;
				}
				ImGui::End();
			}

			m_AcoesPossiveis.clear();
			m_AcoesPossiveis = m_EngineJogo->GetAcoesPossiveis();
			if (std::find(m_AcoesPossiveis.begin(), m_AcoesPossiveis.end(), TexasHoldem::AcoesJogador::Mesa) != m_AcoesPossiveis.end())
			{
				if (ImGui::Button("Mesa", ImVec2(150, 30)))
				{
					m_EngineJogo->AcaoJogador(TexasHoldem::AcoesJogador::Mesa, 0);
				}
			}
			if (std::find(m_AcoesPossiveis.begin(), m_AcoesPossiveis.end(), TexasHoldem::AcoesJogador::Chamar) != m_AcoesPossiveis.end())
			{
				if (ImGui::Button("Chamar", ImVec2(150, 30)))
				{
					m_EngineJogo->AcaoJogador(TexasHoldem::AcoesJogador::Chamar, 0);
				}
			}
			if (std::find(m_AcoesPossiveis.begin(), m_AcoesPossiveis.end(), TexasHoldem::AcoesJogador::Apostar) != m_AcoesPossiveis.end())
			{
				if (ImGui::Button("Apostar", ImVec2(150, 30)))
				{
					m_FichasAdicionar = m_EngineJogo->GetApostaMinima();
					m_Aumentando = false;
					m_Apostando = true;
				}
			}
			if (std::find(m_AcoesPossiveis.begin(), m_AcoesPossiveis.end(), TexasHoldem::AcoesJogador::Aumentar) != m_AcoesPossiveis.end())
			{
				if (ImGui::Button("Aumentar", ImVec2(150, 30)))
				{
					m_FichasAdicionar = m_EngineJogo->GetApostaMinima();
					m_Aumentando = true;
					m_Apostando = true;
				}
			}

			if (std::find(m_AcoesPossiveis.begin(), m_AcoesPossiveis.end(), TexasHoldem::AcoesJogador::Fugir) != m_AcoesPossiveis.end())
			{
				if (ImGui::Button("Fugir", ImVec2(150, 30)))
				{
					m_EngineJogo->AcaoJogador(TexasHoldem::AcoesJogador::Fugir, 0);
				}
			}

			break;
		case TexasHoldem::EstadoJogo::FimRodada:
			m_AcoesPossiveis.clear();

			break;
		case TexasHoldem::EstadoJogo::FimJogo:
			m_AcoesPossiveis.clear();

			break;
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
		if (m_EngineJogo->GetJogadores().size() == 4)
		{
			bool todosComFicha = true;
			for (auto& it : m_EngineJogo->GetJogadores())
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