#include "TexasHoldem.h"

#include "TexasHoldem.h"

#include "Core/Random.h"
#include "Core/EntityManager.h"

#include <random>

namespace PokerSS
{
	namespace TexasHoldem
	{
		TexasHoldem::TexasHoldem()
			: m_CardBackBaralho(CardBack::BlueFlat)
		{
			// Loading Spritesheets
			m_CardSpriteSheet = SolutionShelves::Texture2D::Create("assets/textures/playingCards.png");
			m_CardBackSpriteSheet = SolutionShelves::Texture2D::Create("assets/textures/playingCardBacks.png");

			m_ChipsSpriteSheet = SolutionShelves::Texture2D::Create("assets/textures/ChipsSpriteSheet.png");

			m_PlayerTextureLeft = SolutionShelves::Texture2D::Create("assets/textures/player_1.png");
			m_PlayerTextureRight = SolutionShelves::Texture2D::Create("assets/textures/player_2.png");

			m_DealerChip = SolutionShelves::Texture2D::Create("assets/textures/dealer-chip.png");

			m_PosicaoBotao = -1;

			m_Pote = SolutionShelves::CreateRef<ChipStack>(m_ChipsSpriteSheet);
			m_Pote->EnableRender();
			m_Pote->SetRenderSize(0.3f);
			m_Pote->SetRenderPosition({ 0.05f, -0.05f });
			EntityManager::Get().PushEntity(m_Pote);

			m_Log = SolutionShelves::CreateRef<std::vector<std::string>>();
			ReinicializaEngine();
		}

		TexasHoldem::~TexasHoldem()
		{
		}

		std::string TexasHoldem::GetVencedores()
		{
			std::string textoRetorno = "";

			if (m_QuantidadeJogadoresNoJogo == 1)
			{
				for(auto& it : m_Jogadores)
				{
					if (it->GetInGame())
					{
						textoRetorno += "Jogador ";
						textoRetorno += it->GetName();
						textoRetorno += " ganha pote sem showdown e recebe (" + std::to_string(m_Stack) + ").";
					}
				}
			}
			else
			{
				uint32_t sobra = m_Stack;
				CalculaMaosJogadores();
				std::vector<DadosMao> vencedores = RankeiaJogadores();

				while (sobra > 0)
				{
					uint32_t divisao = 1;
					for (uint32_t i = 0; i < vencedores.size() - 1; i++)
					{
						auto& it = m_Jogadores[vencedores[i].IndiceJogador];
						auto& itProx = m_Jogadores[vencedores[(uint64_t)i + 1].IndiceJogador];
						if (it->GetPoints() == itProx->GetPoints())
							divisao++;
						else
							break;
					}

					for (uint32_t i = 0; i < divisao; i++)
					{
						auto& jogador = m_Jogadores[vencedores[i].IndiceJogador];
						long subtracao = 0;
						for(auto& it : m_SidePots)
						{
							if (it.JogadorExcluido->GetEntityID() == jogador->GetEntityID())
							{
								subtracao += it.Valor;
								break;
							}
						}
						double doubleFichasPote = (sobra - subtracao) / divisao;
						uint32_t fichasPote = (uint32_t)glm::floor(doubleFichasPote);

						if (divisao > 1)
						{
							textoRetorno += "Jogador ";
							textoRetorno += jogador->GetName();
							textoRetorno += ", empata no pote com ";
							textoRetorno += jogador->GetHandDescription();
							textoRetorno += " e recebe (" + std::to_string(fichasPote) +").";
						}
						else
						{
							textoRetorno += "Jogador ";
							textoRetorno += jogador->GetName();
							textoRetorno += " ganha pote com ";
							textoRetorno += jogador->GetHandDescription();
							textoRetorno += " e recebe (" + std::to_string(fichasPote) + ").";
						}
						sobra -= fichasPote;
					}
					sobra = 0;
				}


			}

			return textoRetorno;
		}

		void TexasHoldem::SetaBlinds(uint32_t qtd)
		{
			sprintf_s(m_LogString, "Blind precisa ser um numero par!");
			m_Log->push_back(m_LogString);

			SS_ASSERT(qtd % 2 == 0, "Blind precisa ser um numero par!");
			m_NivelInicialBlind = qtd;
		}

		void TexasHoldem::SetaAnte(uint32_t qtd)
		{
			m_Ante = qtd;
		}

		void TexasHoldem::AdicionaJogador(const std::string& nome)
		{
			if (m_Jogadores.size() < MAXIMO_JOGADORES)
			{
				auto novoJogador = SolutionShelves::CreateRef<Player>(nome, m_PlayerTextureLeft, m_PlayerTextureRight, m_DealerChip, m_ChipsSpriteSheet);
				novoJogador->EnableRender();
				EntityManager::Get().PushEntity(novoJogador);
				novoJogador->AddChips(5000);
				m_Jogadores.push_back(novoJogador);
			}
			else
			{
				sprintf_s(m_LogString, "Quantidade jogadores maxima(%d) ultrapassada!", MAXIMO_JOGADORES);
				m_Log->push_back(m_LogString);

				SS_ERROR("Quantidade jogadores maxima({0}) ultrapassada!", MAXIMO_JOGADORES);
			}
		}

		void TexasHoldem::AdicionaFichasJogador(uint32_t indiceJogador, uint32_t qtdFichas)
		{
			sprintf_s(m_LogString, "Tentando adicionar fichas a um jogador que nao existe");
			m_Log->push_back(m_LogString);

			SS_ASSERT(indiceJogador < m_Jogadores.size(), "Tentando adicionar fichas a um jogador que nao existe");
			m_Jogadores[indiceJogador]->AddChips(qtdFichas);
		}

		std::vector<AcoesJogador> TexasHoldem::GetAcoesPossiveis(int32_t jogadorPedindo)
		{
			std::vector<AcoesJogador> retorno;
			if (jogadorPedindo != -1 && jogadorPedindo != m_IndiceJogadorAcao)
				return retorno;

			if (m_Jogadores[m_IndiceJogadorAcao]->GetIsAllinn())
				return retorno;

			if (!m_Jogadores[m_IndiceJogadorAcao]->GetInGame())
				return retorno;

			retorno.push_back(AcoesJogador::Fugir);
			if (m_Jogadores[m_IndiceJogadorAcao]->GetBet() < m_ApostaAtual)
			{
				retorno.push_back(AcoesJogador::Chamar);
				retorno.push_back(AcoesJogador::Aumentar);
			} 
			else
			{
				retorno.push_back(AcoesJogador::Mesa);
				retorno.push_back(AcoesJogador::Apostar);
			}
			return retorno;

		}

		uint32_t TexasHoldem::GetApostaMinima()
		{
			if ((m_ApostaAtual + m_BigBlind) <= m_Jogadores[m_IndiceJogadorAcao]->GetChips())
				return (m_ApostaAtual + m_BigBlind);
			else
				return m_Jogadores[m_IndiceJogadorAcao]->GetChips();
		}

		uint32_t TexasHoldem::GetApostaMaxima()
		{
			return m_Jogadores[m_IndiceJogadorAcao]->GetChips();
		}

		void TexasHoldem::Start()
		{
			IniciarJogo();
		}

		void TexasHoldem::ReinicializaEngine()
		{
			CriarBaralho(m_CardBackBaralho);
			EmbaralhaCartas(m_Baralho);
			m_Jogadores.clear();
			m_EstadoJogoAtual = EstadoJogo::PreJogo;
			m_CartasMesa.clear();
			m_CartasMuck.clear();
			m_Stack = 0;
			m_SmallBlind = 0;
			m_BigBlind = 0;
			m_PosicaoBotao = 0;
			m_NivelInicialBlind = 0;
			m_TempoCrescimentoBlinds = 0;
			m_ApostaAtual = 0;
			m_QuantidadeJogadoresNoJogo = 0;
			m_IndiceFimRodada = 0;
			m_SidePots.clear();
			m_Ante = 0;
			
			Random::Init();
		}

		void TexasHoldem::IniciarJogo()
		{
			if (m_Jogadores.size() < 2)
			{
				m_Log->push_back("[ERRO] Jogadores insuficientes!");
				SS_WARN("Jogadores insuficientes!");
				return;
			}

			bool jogadorSemFichas = false;
			for (auto& it : m_Jogadores)
			{
				if (it->GetChips() == 0)
				{
					sprintf_s(m_LogString, "Jogador %s nao recebeu fichas!", it->GetName().c_str());
					m_Log->push_back(m_LogString);
					SS_WARN("Jogador {0} nao recebeu fichas!", it->GetName());
					jogadorSemFichas = true;
				}
				else
				{
					it->SetInGame(true);
					it->ClearBet();
					it->SetHandDescription("");
					it->SetAllIn(false);
					it->SetPoints(0);

					if (m_Ante > 0)
					{
						m_Stack += m_Ante;
						it->RemoveChips(m_Ante);
					}
				}
			}

			if (jogadorSemFichas) return;

			m_PosicaoBotao = (Random::Int() % m_Jogadores.size());

			m_SmallBlind = m_NivelInicialBlind / 2;
			m_BigBlind = m_NivelInicialBlind;
			
			if (m_SmallBlind)
			{
				sprintf_s(m_LogString, "Blinds em %d/%d", m_SmallBlind, m_BigBlind);
				m_Log->push_back(m_LogString);
			}

			m_Stack = 0;
			if (m_Jogadores.size() == 2)
			{
				m_Jogadores[ProximaPosicao(m_PosicaoBotao - 1)]->AddBet(m_SmallBlind);
				m_Stack += m_Jogadores[ProximaPosicao(m_PosicaoBotao - 1)]->GetBet();
				m_Jogadores[ProximaPosicao(m_PosicaoBotao)]->AddBet(m_BigBlind);
				m_Stack += m_Jogadores[ProximaPosicao(m_PosicaoBotao)]->GetBet();
				m_ApostaAtual = m_BigBlind;

				if (m_SmallBlind > 0)
				{
					m_IndiceFimRodada = ProximaPosicao(m_PosicaoBotao);
					m_IndiceJogadorAcao = ProximaPosicao(m_PosicaoBotao + 1);

					
				}
				else
				{
					m_IndiceFimRodada = ProximaPosicao(m_PosicaoBotao - 1);
					m_IndiceJogadorAcao = ProximaPosicao(m_PosicaoBotao);
				}
			}
			else
			{
				m_Jogadores[ProximaPosicao(m_PosicaoBotao)]->AddBet(m_SmallBlind);
				m_Stack += m_Jogadores[ProximaPosicao(m_PosicaoBotao)]->GetBet();
				m_Jogadores[ProximaPosicao(m_PosicaoBotao + 1)]->AddBet(m_BigBlind);
				m_Stack += m_Jogadores[ProximaPosicao(m_PosicaoBotao + 1)]->GetBet();
				m_ApostaAtual = m_BigBlind;

				if (m_SmallBlind > 0)
				{
					sprintf_s(m_LogString, "Jogador %s coloca small blind de %d.", m_Jogadores[ProximaPosicao(m_PosicaoBotao)]->GetName().c_str(), m_SmallBlind);
					m_Log->push_back(m_LogString);
					sprintf_s(m_LogString, "Jogador %s coloca big blind de %d.", m_Jogadores[ProximaPosicao(m_PosicaoBotao + 1)]->GetName().c_str(), m_BigBlind);
					m_Log->push_back(m_LogString);

					m_IndiceFimRodada = ProximaPosicao(m_PosicaoBotao + 1);
					m_IndiceJogadorAcao = ProximaPosicao(m_PosicaoBotao + 2);
				} 
				else 
				{
					m_IndiceFimRodada = ProximaPosicao(m_PosicaoBotao + m_QuantidadeJogadoresNoJogo - 1);
					m_IndiceJogadorAcao = ProximaPosicao(m_PosicaoBotao);

				}
			}
			SetaJogadorAcao(m_IndiceJogadorAcao);

			EmbaralhaCartas(m_Baralho);
			m_FaseRodadaAtual = FaseRodada::Pre_Flop;
			m_EstadoJogoAtual = EstadoJogo::Jogo;

			for (uint32_t i = 0; i < (m_Jogadores.size() * QUANTIDADE_CARTAS_JOGO); i++)
			{
				auto proximaCarta = ProximaCarta();
				proximaCarta->SetRevealed(true);
				m_Jogadores[ProximaPosicao(m_PosicaoBotao + i)]->AddCard(proximaCarta);
			}

			SetaDealer(m_PosicaoBotao);
			m_NumeroMao++;
			sprintf_s(m_LogString, "Jogo INICIADO.");
			m_Log->push_back(m_LogString);

			sprintf_s(m_LogString, "Jogador %s com a acao.", m_Jogadores[m_IndiceJogadorAcao]->GetName().c_str());
			m_Log->push_back(m_LogString);

			m_Pote->SetChipAmount(m_Stack);
		}

		void TexasHoldem::NovaMao()
		{
			if (m_FaseRodadaAtual != FaseRodada::CleanUp)
			{
				m_Log->push_back("Fase atual não pode iniciar nova mão.");
				SS_ERROR("Fase atual não pode iniciar nova mão.");
				return;
			}

			// Retorna cartas dos jogadores, mesa e muck ao baralho
			for (auto& it : m_Jogadores)
			{
				while (!it->GetHand().empty())
				{
					auto carta = it->GetHand().back();
					carta->SetRevealed(false);
					m_Baralho.push_back(carta);
					it->RemoveCard(carta);
				}
			}
			while (!m_CartasMesa.empty())
			{
				auto card = m_CartasMesa.back();
				card->SetRevealed(false);
				m_Baralho.push_back(m_CartasMesa.back());
				m_CartasMesa.pop_back();
			}
			while (!m_CartasMuck.empty())
			{
				auto card = m_CartasMuck.back();
				card->SetRevealed(false);
				m_Baralho.push_back(m_CartasMuck.back());
				m_CartasMuck.pop_back();
			}

			//Dá as fichas para os jogadores que ganharam
			long sobra = m_Stack;
			std::vector<DadosMao> vencedores = RankeiaJogadores();

			sprintf_s(m_LogString, GetVencedores().c_str());
			m_Log->push_back(m_LogString);

			while (sobra > 0)
			{
				uint32_t divisao = 1;
				for (uint32_t i = 0; i < vencedores.size() - 1; i++)
				{
					auto& jogador1 = m_Jogadores[vencedores[i].IndiceJogador];
					auto& jogador2 = m_Jogadores[vencedores[i + 1].IndiceJogador];
					if (jogador1->GetPoints() == jogador2->GetPoints())
						divisao++;
					else
						break;
				}

				std::vector<int> remover;
				for (uint32_t i = 0; i < divisao; i++)
				{
					auto& jogador1 = m_Jogadores[vencedores[i].IndiceJogador];
					long subtracao = 0;
					for(auto& it : m_SidePots)
					{
						if (it.JogadorExcluido->GetEntityID() == jogador1->GetEntityID())
						{
							subtracao += it.Valor;
							break;
						}
					}
					double d_FichasPote = (sobra - subtracao) / divisao;
					uint32_t fichasPote = (uint32_t)glm::floor(d_FichasPote);
					jogador1->AddChips(fichasPote);
					sobra -= fichasPote;
					remover.push_back(i);
				}
				if (sobra > 0 && vencedores.size() > 0)
				{
					auto& jogador1 = m_Jogadores[vencedores[0].IndiceJogador];
					sprintf_s(m_LogString,"Atribuindo %d fichas ao jogador %s por sobra indivisel no sidepot", sobra, jogador1->GetName().c_str());
					m_Log->push_back(m_LogString);
					SS_WARN("Atribuindo {0} fichas ao jogador {1} por sobra indivisel no sidepot", sobra, jogador1->GetName());
					jogador1->AddChips(sobra);
				}
				sobra = 0;
			}

			m_SidePots.clear();

			// Verifica jogadores no jogo
			for (auto& it : m_Jogadores)
				it->SetInGame(it->GetChips() > 0);

			// Move botao
			m_PosicaoBotao = ProximaPosicao(m_PosicaoBotao);

			//Acerta Blinds
			if (m_TempoCrescimentoBlinds > 0)
			{
				if (m_TempoDecorridoBlind >= m_TempoCrescimentoBlinds)
				{
					AumentaBlinds();
					m_TempoDecorridoBlind = 0.0f;
				}
			}

			m_Stack = 0;

			m_QuantidadeJogadoresNoJogo = 0;
			for(auto& it : m_Jogadores)
			{
				if (it->GetChips() == 0)
				{
					it->SetInGame(false);
				}
				else
				{
					it->SetInGame(true);
					m_QuantidadeJogadoresNoJogo++;
				}

				it->ClearBet();
				it->SetHandDescription(" - ");
				it->SetAllIn(false);
				it->SetPoints(0);

				if (m_Ante > 0)
				{
					m_Stack += m_Ante;
					it->RemoveChips(m_Ante);
				}

			}

			if (m_QuantidadeJogadoresNoJogo == 1)
			{
				m_FaseRodadaAtual = FaseRodada::FimDeJogo;
				m_EstadoJogoAtual = EstadoJogo::FimJogo;
				sprintf_s(m_LogString, "Jogo encerrado.");
				m_Log->push_back(m_LogString);

				SS_WARN("Jogo encerrado.");
				return;
			}

			if (m_Jogadores.size() == 2)
			{
				m_Jogadores[ProximaPosicao(m_PosicaoBotao + m_QuantidadeJogadoresNoJogo - 1)]->AddBet(m_SmallBlind);
				m_Stack += m_SmallBlind;
				m_Jogadores[ProximaPosicao(m_PosicaoBotao)]->AddBet(m_BigBlind);
				m_Stack += m_BigBlind;
				m_ApostaAtual = m_BigBlind;

				if (m_SmallBlind > 0)
				{
					sprintf_s(m_LogString, "Jogador %s coloca small blind de %d.", m_Jogadores[ProximaPosicao(m_PosicaoBotao)]->GetName().c_str(), m_SmallBlind);
					m_Log->push_back(m_LogString);
					sprintf_s(m_LogString, "Jogador %s coloca big blind de %d.", m_Jogadores[ProximaPosicao(m_PosicaoBotao + 1)]->GetName().c_str(), m_BigBlind);
					m_Log->push_back(m_LogString);

					m_IndiceFimRodada = ProximaPosicao(m_PosicaoBotao);
					m_IndiceJogadorAcao = ProximaPosicao(m_PosicaoBotao + 1);
				}
				else
				{
					m_IndiceFimRodada = ProximaPosicao(m_PosicaoBotao + m_QuantidadeJogadoresNoJogo - 1);
					m_IndiceJogadorAcao = ProximaPosicao(m_PosicaoBotao);
				}
			}
			else
			{
				m_Jogadores[ProximaPosicao(m_PosicaoBotao)]->AddBet(m_SmallBlind);
				m_Stack += m_SmallBlind;
				m_Jogadores[ProximaPosicao(m_PosicaoBotao + 1)]->AddBet(m_BigBlind);
				m_Stack += m_BigBlind;
				m_ApostaAtual = m_BigBlind;

				if (m_SmallBlind > 0)
				{
					sprintf_s(m_LogString, "Jogador %s coloca small blind de %d.", m_Jogadores[ProximaPosicao(m_PosicaoBotao)]->GetName().c_str(), m_SmallBlind);
					m_Log->push_back(m_LogString);
					sprintf_s(m_LogString, "Jogador %s coloca big blind de %d.", m_Jogadores[ProximaPosicao(m_PosicaoBotao + 1)]->GetName().c_str(), m_BigBlind);
					m_Log->push_back(m_LogString);


					m_IndiceFimRodada = ProximaPosicao(m_PosicaoBotao + 1);
					m_IndiceJogadorAcao = ProximaPosicao(m_PosicaoBotao + 2);
				}
				else
				{
					m_IndiceFimRodada = ProximaPosicao(m_PosicaoBotao - 1);
					m_IndiceJogadorAcao = ProximaPosicao(m_PosicaoBotao);
				}
			}
			SetaJogadorAcao(m_IndiceJogadorAcao);

			m_CartasMesa.clear();
			m_CartasMuck.clear();
			EmbaralhaCartas(m_Baralho);
			for (uint32_t i = 0; i < (m_Jogadores.size() * QUANTIDADE_CARTAS_JOGO); i++)
			{
				auto proximaCarta = ProximaCarta();
				proximaCarta->SetRevealed(true);
				m_Jogadores[ProximaPosicao(m_PosicaoBotao + i)]->AddCard(proximaCarta);
			}

			SetaDealer(m_PosicaoBotao);

			m_FaseRodadaAtual = FaseRodada::Pre_Flop;
			m_NumeroMao++;
			
			m_Pote->SetChipAmount(m_Stack);

			sprintf_s(m_LogString, "Jogador %s com a acao.", m_Jogadores[m_IndiceJogadorAcao]->GetName().c_str());
			m_Log->push_back(m_LogString);

		}

		std::vector<DadosMao> TexasHoldem::RankeiaJogadores()
		{
			std::vector<DadosMao> retorno;
			
			for (uint32_t indice = 0; indice < (uint32_t)m_Jogadores.size(); indice++)
			{
				auto& it = m_Jogadores[indice];
				if (m_Jogadores[indice]->GetInGame())
					retorno.push_back(DadosMao(it->GetPoints(), it->GetName(), indice));
			}
			sort(retorno.begin(), retorno.end(), [](DadosMao left, DadosMao right)
				{
					return left.Pontos > right.Pontos;
				});
			return retorno;
		}

		void TexasHoldem::AumentaBlinds()
		{
			if (m_ToggleBlind)
			{
				m_ToggleBlind = false;
				m_BigBlind += m_SmallBlind;
				m_SmallBlind = m_BigBlind / 2;
			} 
			else
			{
				m_ToggleBlind = true;
				m_BigBlind += m_BigBlind;
				m_SmallBlind = m_BigBlind / 2;
			}
		}

		void TexasHoldem::AvancaJogo()
		{
			if (m_FaseRodadaAtual == FaseRodada::FimDeJogo)
			{
				sprintf_s(m_LogString, "Fim de jogo!");
				m_Log->push_back(m_LogString);
				return;
			}

			if (m_IndiceFimRodada == m_IndiceJogadorAcao)
			{
				for (auto& it : m_Jogadores)
				{
					it->RemoveChips(it->GetBet());
					it->ClearBet();
				}

				m_Pote->SetChipAmount(m_Stack);

				switch (m_FaseRodadaAtual)
				{
				case FaseRodada::Pre_Flop:
					m_CartasMuck.push_back(ProximaCarta());
					m_CartasMesa.push_back(ProximaCarta());
					m_CartasMesa.push_back(ProximaCarta());
					m_CartasMesa.push_back(ProximaCarta());
					PosicionaCartasMesa();
					PosicionaCartasMuck();
					ProximoJogador();
					m_ApostaAtual = 0;
					m_IndiceFimRodada = ProximaPosicao(m_PosicaoBotao - 1);
					if (m_FaseRodadaAtual == FaseRodada::Pre_Flop)
						m_FaseRodadaAtual = FaseRodada::Flop;

					sprintf_s(m_LogString, "Flop de %s, %s e %s.", m_CartasMesa[0]->GetCardDescription().c_str(),
						m_CartasMesa[1]->GetCardDescription().c_str(), m_CartasMesa[2]->GetCardDescription().c_str());
					m_Log->push_back(m_LogString);

					break;
				case FaseRodada::Flop:
					m_CartasMuck.push_back(ProximaCarta());
					m_CartasMesa.push_back(ProximaCarta());
					PosicionaCartasMesa();
					PosicionaCartasMuck();
					ProximoJogador();
					m_ApostaAtual = 0;
					m_IndiceFimRodada = ProximaPosicao(m_PosicaoBotao - 1);
					if (m_FaseRodadaAtual == FaseRodada::Flop)
						m_FaseRodadaAtual = FaseRodada::Turn;
					sprintf_s(m_LogString, "Turn de %s.", m_CartasMesa[3]->GetCardDescription().c_str());
					m_Log->push_back(m_LogString);
					break;
				case FaseRodada::Turn:
					m_CartasMuck.push_back(ProximaCarta());
					m_CartasMesa.push_back(ProximaCarta());
					PosicionaCartasMesa();
					PosicionaCartasMuck();
					ProximoJogador();
					m_ApostaAtual = 0;
					m_IndiceFimRodada = ProximaPosicao(m_PosicaoBotao - 1);
					if (m_FaseRodadaAtual == FaseRodada::Turn)
						m_FaseRodadaAtual = FaseRodada::River;

					sprintf_s(m_LogString, "River de %s.", m_CartasMesa[4]->GetCardDescription().c_str());
					m_Log->push_back(m_LogString);
					break;
				case FaseRodada::River:
					CalculaMaosJogadores();
					if (m_FaseRodadaAtual == FaseRodada::River)
						m_FaseRodadaAtual = FaseRodada::CleanUp;

					sprintf_s(m_LogString, "%s.", GetVencedores().c_str());
					m_Log->push_back(m_LogString);
					m_EstadoJogoAtual = EstadoJogo::FimRodada;
					break;
				case FaseRodada::CleanUp:
					//Aguardando ação de começar nova mão
					break;
				case FaseRodada::FimDeJogo:
					//Aguardando novo jogo
					break;
				default:
					SS_ERROR("Fase inesperada, jogo em estado nao previsto");
				}
			}
			else
			{
				ProximoJogadorMesmaFase();
			}
		}

		void TexasHoldem::ProximoJogadorMesmaFase()
		{
			m_IndiceJogadorAcao = ProximaPosicao(m_IndiceJogadorAcao);
			SetaJogadorAcao(m_IndiceJogadorAcao);

			int primeiroIndice = m_IndiceJogadorAcao;
			while (m_Jogadores[m_IndiceJogadorAcao]->GetIsAllinn())
			{
				sprintf_s(m_LogString, "Jogador %s, All - Inn", m_Jogadores[m_IndiceJogadorAcao]->GetName().c_str());
				m_Log->push_back(m_LogString);

				m_IndiceJogadorAcao = ProximaPosicao(m_IndiceJogadorAcao);
				SetaJogadorAcao(m_IndiceJogadorAcao);
				if (m_IndiceJogadorAcao == primeiroIndice)
				{
					sprintf_s(m_LogString, "Todos jogadores All - Inn");
					m_Log->push_back(m_LogString);
					//Todos AllInn
					m_IndiceFimRodada = m_IndiceJogadorAcao;
					if (m_FaseRodadaAtual < FaseRodada::CleanUp)
					{
						m_FaseRodadaAtual = (FaseRodada)((uint32_t)m_FaseRodadaAtual + 1);
						AvancaJogo();
					}
					else
						return;
				}
			}
			int qtdJogadoresAllIn = 0;
			for(auto& it : m_Jogadores)
			{
				if (it->GetIsAllinn())
					qtdJogadoresAllIn++;
			}
			if (qtdJogadoresAllIn == m_QuantidadeJogadoresNoJogo - 1 && m_Jogadores[m_IndiceJogadorAcao]->GetBet() == m_ApostaAtual)
			{
				m_IndiceFimRodada = m_IndiceJogadorAcao;
				if (m_FaseRodadaAtual < FaseRodada::CleanUp)
				{
					m_FaseRodadaAtual = (FaseRodada)((uint32_t)m_FaseRodadaAtual + 1);
					AvancaJogo();
				}
			}

		}

		void TexasHoldem::ProximoJogador()
		{
			m_IndiceJogadorAcao = ProximaPosicao(m_PosicaoBotao);
			SetaJogadorAcao(m_IndiceJogadorAcao);
			uint32_t primeiroIndice = m_IndiceJogadorAcao;
			while (m_Jogadores[m_IndiceJogadorAcao]->GetIsAllinn())
			{
				m_IndiceJogadorAcao = ProximaPosicao(m_PosicaoBotao);
				SetaJogadorAcao(m_IndiceJogadorAcao);
				if (m_IndiceJogadorAcao == primeiroIndice)
				{
					sprintf_s(m_LogString, "Todos os jogadores estao ALL IN");
					m_Log->push_back(m_LogString);
					break;

					// Todos All-In
					m_IndiceFimRodada = m_IndiceJogadorAcao;
					if (m_FaseRodadaAtual < FaseRodada::CleanUp)
					{
						m_FaseRodadaAtual = (FaseRodada)((uint32_t)m_FaseRodadaAtual + 1);
						AvancaJogo();
					}
					else
						break;
				}
			}
			uint32_t qtdJogadoresAllIn = 0;
			for (auto& it : m_Jogadores)
			{
				if (it->GetIsAllinn())
					qtdJogadoresAllIn++;
			}

			if (qtdJogadoresAllIn == m_QuantidadeJogadoresNoJogo - 1)
			{
				m_IndiceFimRodada = m_IndiceJogadorAcao;
				if (m_FaseRodadaAtual < FaseRodada::CleanUp)
				{
					m_FaseRodadaAtual = (FaseRodada)((uint32_t)m_FaseRodadaAtual + 1);
					AvancaJogo();
				}
			}
			sprintf_s(m_LogString, "Jogador %s com a acao.", m_Jogadores[m_IndiceJogadorAcao]->GetName().c_str());
			m_Log->push_back(m_LogString);

		}

		SolutionShelves::Ref<Card> TexasHoldem::ProximaCarta()
		{
			if (m_Baralho.size() == 0) 
			{
				sprintf_s(m_LogString, "Baralho vazio ao pedir proxima carta!");
				m_Log->push_back(m_LogString);
				SS_ERROR("Baralho vazio ao pedir proxima carta!");
			}

			SolutionShelves::Ref<Card> retorno = m_Baralho.back();
			m_Baralho.pop_back();
			return retorno;
		}

		uint32_t TexasHoldem::ProximaPosicao(uint32_t pos)
		{
			uint32_t novaPos = (pos + 1) % (uint32_t)m_Jogadores.size();
			SS_ASSERT(novaPos != pos, "Erro pegando proxima posicao (loop infinito) antes da recursao");

			if (!m_Jogadores[novaPos]->GetInGame())
				novaPos = ProximaPosicao(novaPos);

			SS_ASSERT(novaPos != pos, "Erro pegando proxima posicao (loop infinito) depois da recursao");

			return novaPos;
		}

		void TexasHoldem::AcaoJogador(AcoesJogador tipoAcao, uint32_t qtdFichas)
		{
			switch (tipoAcao)
			{
			case AcoesJogador::Fugir:
				m_Jogadores[m_IndiceJogadorAcao]->RemoveChips(m_Jogadores[m_IndiceJogadorAcao]->GetBet());
				m_Stack += m_Jogadores[m_IndiceJogadorAcao]->GetBet();
				m_Pote->SetChipAmount(m_Pote->GetChipAmount() +  m_Jogadores[m_IndiceJogadorAcao]->GetBet());
				m_Jogadores[m_IndiceJogadorAcao]->SetInGame(false);
				m_Jogadores[m_IndiceJogadorAcao]->SetFolded(true);
				m_Jogadores[m_IndiceJogadorAcao]->ClearBet();
				while (!m_Jogadores[m_IndiceJogadorAcao]->GetHand().empty())
				{
					auto carta = m_Jogadores[m_IndiceJogadorAcao]->GetHand().back();
					carta->SetRevealed(false);
					m_CartasMuck.push_back(carta);
					m_Jogadores[m_IndiceJogadorAcao]->RemoveCard(carta);
				}
				m_QuantidadeJogadoresNoJogo--;

				sprintf_s(m_LogString, "Jogador %s FUGIU.", m_Jogadores[m_IndiceJogadorAcao]->GetName().c_str());
				m_Log->push_back(m_LogString);

				if (m_QuantidadeJogadoresNoJogo == 1)
					m_FaseRodadaAtual = FaseRodada::CleanUp;
				break;
			case AcoesJogador::Mesa:
				if (m_Jogadores[m_IndiceJogadorAcao]->GetBet() != m_ApostaAtual)
				{
					sprintf_s(m_LogString, "Ação nao permitida");
					m_Log->push_back(m_LogString);

					SS_ERROR("Acao nao permitida");
					return;
				}
				sprintf_s(m_LogString, "Jogador %s MESA.", m_Jogadores[m_IndiceJogadorAcao]->GetName().c_str());
				m_Log->push_back(m_LogString);
				break;
			case AcoesJogador::Chamar:
				if (m_ApostaAtual > m_Jogadores[m_IndiceJogadorAcao]->GetChips())
					qtdFichas = m_Jogadores[m_IndiceJogadorAcao]->GetChips();
				else
					qtdFichas = m_ApostaAtual;

				m_Stack += (qtdFichas - m_Jogadores[m_IndiceJogadorAcao]->GetBet());
				m_Jogadores[m_IndiceJogadorAcao]->AddBet(qtdFichas - m_Jogadores[m_IndiceJogadorAcao]->GetBet());

				sprintf_s(m_LogString, "Jogador %s da CALL", m_Jogadores[m_IndiceJogadorAcao]->GetName().c_str());
				m_Log->push_back(m_LogString);

				for(auto& it : m_SidePots)
				{
					long valorAdicionalSidepot = qtdFichas - it.ValorAllIn;
					if (valorAdicionalSidepot > 0)
						it.Valor += valorAdicionalSidepot;
				}

				if (m_Jogadores[m_IndiceJogadorAcao]->GetIsAllinn())
				{
					sprintf_s(m_LogString, "Jogador %s esta ALLINN", m_Jogadores[m_IndiceJogadorAcao]->GetName().c_str());
					m_Log->push_back(m_LogString);

					m_SidePots.push_back({ m_Jogadores[m_IndiceJogadorAcao], m_ApostaAtual - qtdFichas, m_Jogadores[m_IndiceJogadorAcao]->GetBet() });
				}

				break;
			case AcoesJogador::Apostar:
			case AcoesJogador::Aumentar:
				if (qtdFichas < (m_ApostaAtual + m_BigBlind) && qtdFichas <= m_Jogadores[m_IndiceJogadorAcao]->GetChips())
				{
					sprintf_s(m_LogString, "Aposta inválida.");
					m_Log->push_back(m_LogString);

					SS_ERROR("Aposta inválida.");
					return;
				}

				if (qtdFichas > m_Jogadores[m_IndiceJogadorAcao]->GetChips())
					qtdFichas = m_Jogadores[m_IndiceJogadorAcao]->GetChips();

				m_Stack += (qtdFichas - m_Jogadores[m_IndiceJogadorAcao]->GetBet());
				m_Jogadores[m_IndiceJogadorAcao]->AddBet(qtdFichas - m_Jogadores[m_IndiceJogadorAcao]->GetBet());
				if (m_Jogadores[m_IndiceJogadorAcao]->GetBet() > m_ApostaAtual)
				{
					m_ApostaAtual = qtdFichas;
					m_IndiceFimRodada = ProximaPosicao(m_IndiceJogadorAcao + m_QuantidadeJogadoresNoJogo - 2);

					if (tipoAcao == AcoesJogador::Apostar)
						sprintf_s(m_LogString, "Jogador %s APOSTA %d fichas.", m_Jogadores[m_IndiceJogadorAcao]->GetName().c_str(), qtdFichas);
					else
						sprintf_s(m_LogString, "Jogador %s AUMENTA para %d fichas.", m_Jogadores[m_IndiceJogadorAcao]->GetName().c_str(), qtdFichas);

					m_Log->push_back(m_LogString);

				}

				for (auto& it : m_SidePots)
				{
					long valorAdicionalSidepot = qtdFichas - it.ValorAllIn;
					if (valorAdicionalSidepot > 0)
						it.Valor += valorAdicionalSidepot;
				}

				if (m_Jogadores[m_IndiceJogadorAcao]->GetIsAllinn())
				{
					sprintf_s(m_LogString, "Jogador %s esta ALLINN.", m_Jogadores[m_IndiceJogadorAcao]->GetName().c_str());
					m_Log->push_back(m_LogString);
					m_SidePots.push_back({ m_Jogadores[m_IndiceJogadorAcao], m_ApostaAtual - qtdFichas, m_Jogadores[m_IndiceJogadorAcao]->GetBet() });
				}

				break;
			default:
				sprintf_s(m_LogString, "Ação inexistente(não implementada)");
				m_Log->push_back(m_LogString);
				SS_ERROR("Ação inexistente (não implementada)");
				return;
			}

			AvancaJogo();
		}

		void TexasHoldem::SetaDealer(uint32_t pos)
		{
			for (auto& it : m_Jogadores)
				it->SetDealer(false);
			m_Jogadores[pos]->SetDealer(true);
		}

		void TexasHoldem::SetaJogadorAcao(uint32_t pos)
		{
			for (auto& it : m_Jogadores)
				it->SetInAction(false);

			m_Jogadores[m_IndiceJogadorAcao] = m_Jogadores[pos];
			m_Jogadores[m_IndiceJogadorAcao]->SetInAction(true);
		}

		void TexasHoldem::CalculaMaosJogadores()
		{
			for (auto& it : m_Jogadores)
			{
				if (it->GetInGame())
				{
					std::vector<SolutionShelves::Ref<Card>> cartasJogador;
					std::string descricaoMao = "";
					for (auto& it2 : m_CartasMesa)
						cartasJogador.push_back(it2);
					for (auto& it2 : it->GetHand())
						cartasJogador.push_back(it2);
					OrdenarCartas(cartasJogador);
					DadosMao dadosMao = AnalisaMao(cartasJogador);
					it->SetPoints(dadosMao.Pontos);
					it->SetHandDescription(dadosMao.Descricao);
				}
				else
				{
					it->SetPoints(0);
					it->SetHandDescription("FUGIU");
				}
			}
		}

		DadosMao TexasHoldem::AnalisaMao(const std::vector<SolutionShelves::Ref<Card>>& mao)
		{
			DadosMao retorno = DadosMao(0, "Mao vazia");

			uint32_t pontos = 0;
			std::string descritivo = "";

			std::vector<SolutionShelves::Ref<Card>> melhorMaoPossivel;

			if (mao.size() == 0) return retorno;

			melhorMaoPossivel = StraightFlush(mao);
			if (melhorMaoPossivel.size())
			{
				pontos = CalculaPontos(melhorMaoPossivel, TipoMao::StraightFlush);
				if (melhorMaoPossivel[0]->GetCardFaceValue() == FaceValue::Ace)
					descritivo = "Royal Straight Flush";
				else
					descritivo = "Straight Flush";
			}
			else
			{
				melhorMaoPossivel = Quadra(mao);
				if (melhorMaoPossivel.size())
				{
					pontos = CalculaPontos(melhorMaoPossivel, TipoMao::Quadra);
					descritivo = "Quadra";
				}
				else
				{
					melhorMaoPossivel = FullHouse(mao);
					if (melhorMaoPossivel.size())
					{
						pontos = CalculaPontos(melhorMaoPossivel, TipoMao::FullHouse);
						descritivo = "Full House";
					}
					else
					{
						melhorMaoPossivel = Flush(mao);
						if (melhorMaoPossivel.size())
						{
							pontos = CalculaPontos(melhorMaoPossivel, TipoMao::Flush);
							descritivo = "Flush";
						}
						else
						{
							melhorMaoPossivel = Sequencia(mao);
							if (melhorMaoPossivel.size())
							{
								pontos = CalculaPontos(melhorMaoPossivel, TipoMao::Sequencia);
								descritivo = "Sequência";
							}
							else
							{
								melhorMaoPossivel = Trinca(mao);
								if (melhorMaoPossivel.size())
								{
									pontos = CalculaPontos(melhorMaoPossivel, TipoMao::Trinca);
									descritivo = "Trinca";
								}
								else
								{
									melhorMaoPossivel = DoisPares(mao);
									if (melhorMaoPossivel.size())
									{
										pontos = CalculaPontos(melhorMaoPossivel, TipoMao::DoisPares);
										descritivo = "Dois Pares";
									}
									else
									{
										melhorMaoPossivel = UmPar(mao);
										if (melhorMaoPossivel.size())
										{
											pontos = CalculaPontos(melhorMaoPossivel, TipoMao::Par);
											descritivo = "Um Par";
										}
										else
										{
											melhorMaoPossivel = CartaAlta(mao);
											pontos = CalculaPontos(melhorMaoPossivel, TipoMao::HighCard);
											descritivo = "Carta Alta";
										}
									}
								}
							}
						}
					}
				}
			}

			retorno.Descricao = descritivo;
			retorno.Pontos = pontos;
			return retorno;
		}

		uint32_t TexasHoldem::CalculaPontos(const std::vector<SolutionShelves::Ref<Card>>& mao, TipoMao tipo)
		{
			
			//High Card = (M1 * 10000) + (M2 * 1000) + (M3 * 100) + (M4 * 10) + M5
			//Par = (valor do par * 1000) + (M3 * 100) + (M4 * 10) + M5 + (155000)
			//Dois Pares = (valor do maior par * 100) + (valor menor par * 10) + M5 + (170500)
			//Trinca = (valor da trinca * 100) + (M4 * 10) + M5 + (172100)
			//Sequencia = (valor da maior carta da sequencia * 10) + (174000)
			//Flush = (M1 * 10000) + (M2 * 1000) + (M3 * 100) + (M4 * 10) + M5 + 175000
			//Full House = (valor da trinca * 10) + valor do par + (330000)
			//Quadra = (valor da quadra * 10) + M5 + (331000)
			//Straigth-Flush = M1 + (332000)

			uint32_t pontos = 0;

			SS_ASSERT(mao.size() >= 5, "Quantidade de cartas invalida!");

			switch (tipo)
			{
			case TipoMao::HighCard:
				pontos = ((uint32_t)mao[0]->GetCardFaceValue() + 2) * 10000 +
						 ((uint32_t)mao[1]->GetCardFaceValue() + 2) * 1000 +
						 ((uint32_t)mao[2]->GetCardFaceValue() + 2) * 100 +
						 ((uint32_t)mao[3]->GetCardFaceValue() + 2) * 10 +
						 ((uint32_t)mao[4]->GetCardFaceValue() + 2);
				break;
			case TipoMao::Par:
				pontos = ((uint32_t)mao[0]->GetCardFaceValue() + 2) * 1000 +
						 ((uint32_t)mao[2]->GetCardFaceValue() + 2) * 100 +
						 ((uint32_t)mao[3]->GetCardFaceValue() + 2) * 10 +
						 ((uint32_t)mao[4]->GetCardFaceValue() + 2) +
						 155000;
				break;
			case TipoMao::DoisPares:
				pontos = ((uint32_t)mao[0]->GetCardFaceValue() + 2) * 100 +
						 ((uint32_t)mao[2]->GetCardFaceValue() + 2) * 10 +
						 ((uint32_t)mao[4]->GetCardFaceValue() + 2) +
						 170500;
				break;
			case TipoMao::Trinca:
				pontos = ((uint32_t)mao[0]->GetCardFaceValue() + 2) * 100 +
						 ((uint32_t)mao[3]->GetCardFaceValue() + 2) * 10 +
						 ((uint32_t)mao[4]->GetCardFaceValue() + 2) +
						 172100;
				break;
			case TipoMao::Sequencia:
				pontos = ((uint32_t)mao[0]->GetCardFaceValue() + 2) * 10 +
						 174000;
				break;
			case TipoMao::Flush:
				pontos = ((uint32_t)mao[0]->GetCardFaceValue() + 2) * 10000 +
						 ((uint32_t)mao[1]->GetCardFaceValue() + 2) * 1000 +
						 ((uint32_t)mao[2]->GetCardFaceValue() + 2) * 100 +
						 ((uint32_t)mao[3]->GetCardFaceValue() + 2) * 10 +
						 ((uint32_t)mao[4]->GetCardFaceValue() + 2) +
						 175000;
				break;
			case TipoMao::FullHouse:
				pontos = ((uint32_t)mao[0]->GetCardFaceValue() + 2) * 10 +
						 ((uint32_t)mao[3]->GetCardFaceValue() + 2) +
						 330000;
				break;
			case TipoMao::Quadra:
				pontos = ((uint32_t)mao[0]->GetCardFaceValue() + 2) * 10 +
						 ((uint32_t)mao[4]->GetCardFaceValue() + 2) +
						 331000;
				break;
			case TipoMao::StraightFlush:
				pontos = ((uint32_t)mao[0]->GetCardFaceValue() + 2) +
						 332000;
				break;
			default:
				SS_CORE_ERROR("funcao CalculaPontos - Tipo de jogo não implementado");
			}

			return pontos;
		}

		std::vector<SolutionShelves::Ref<Card>> TexasHoldem::CartaAlta(const std::vector<SolutionShelves::Ref<Card>>& mao)
		{
			std::vector<SolutionShelves::Ref<Card>> retorno;
			for (int8_t i = (int8_t)mao.size() - 1; i >= 0; i--)
			{
				retorno.push_back(mao[i]);
				if (retorno.size() == 5)
					return retorno;
			}
			return retorno;
		}

		std::vector<SolutionShelves::Ref<Card>> TexasHoldem::UmPar(const std::vector<SolutionShelves::Ref<Card>>& mao)
		{
			std::vector<SolutionShelves::Ref<Card>> retorno;

			bool achouPar = false;

			for (int8_t i = (int8_t)mao.size() - 1; i >= 0; i--)
			{
				retorno.push_back(mao[i]);
				if (retorno.size() == 1) continue;

				for (uint8_t j = 0; j < retorno.size() - 1; j++)
				{
					if (!(retorno[j]->GetCardFaceValue() == retorno[(uint64_t)j + 1]->GetCardFaceValue()))
					{
						if (i > 0)
						{
							retorno.clear();
							retorno.push_back(mao[i]);
							break;
						}
						else
						{
							retorno.clear();
							return retorno;
						}
					}
				}
				if (retorno.size() == 2)
				{
					achouPar = true;
					break;
				}
			}

			if (achouPar)
			{
				for (int8_t i = (int8_t)mao.size() - 1; i >= 0; i--)
				{
					if (mao[i]->GetCardFaceValue() == retorno[0]->GetCardFaceValue()) continue;
					retorno.push_back(mao[i]);
					if (retorno.size() == 5)
						return retorno;
				}
			}
			retorno.clear();
			return retorno;
		}

		std::vector<SolutionShelves::Ref<Card>> TexasHoldem::DoisPares(const std::vector<SolutionShelves::Ref<Card>>& mao)
		{
			std::vector<SolutionShelves::Ref<Card>> retorno;

			std::vector<SolutionShelves::Ref<Card>> retornoPar1;
			std::vector<SolutionShelves::Ref<Card>> retornoPar2;
			bool achouPar = false;

			for (int8_t i = (int8_t)mao.size() - 1; i >= 0; i--)
			{
				retornoPar1.push_back(mao[i]);
				if (retornoPar1.size() == 1) continue;

				for (uint8_t j = 0; j < retornoPar1.size() - 1; j++)
				{
					if (!(retornoPar1[j]->GetCardFaceValue() == retornoPar1[(uint64_t)j + 1]->GetCardFaceValue()))
					{
						if (i > 0)
						{
							retornoPar1.clear();
							retornoPar1.push_back(mao[i]);
							break;
						}
						else
						{
							retorno.clear();
							return retorno;
						}
					}
				}
				if (retornoPar1.size() == 2)
				{
					achouPar = true;
					break;
				}
			}

			if (achouPar)
			{
				for (int8_t i = (int8_t)mao.size() - 1; i >= 0; i--)
				{
					if (mao[i]->GetCardFaceValue() == retornoPar1[0]->GetCardFaceValue()) continue;
					retornoPar2.push_back(mao[i]);
					if (retornoPar2.size() == 1) continue;

					for (uint8_t j = 0; j < retornoPar2.size() - 1; j++)
					{
						if (!(retornoPar2[j]->GetCardFaceValue() == retornoPar2[(uint64_t)j + 1]->GetCardFaceValue()))
						{
							if (i > 0)
							{
								retornoPar2.clear();
								retornoPar2.push_back(mao[i]);
								break;
							}
							else
							{
								retorno.clear();
								return retorno;
							}
						}
					}
					if (retornoPar2.size() == 2)
					{
						for (auto& it : retornoPar1)
							retorno.push_back(it);
						for (auto& it : retornoPar2)
							retorno.push_back(it);

						for (int8_t k = (int8_t)mao.size() - 1; k >= 0; k--)
						{
							if (mao[k]->GetCardFaceValue() != retornoPar1[0]->GetCardFaceValue() && mao[k]->GetCardFaceValue() != retornoPar2[0]->GetCardFaceValue())
							{
								retorno.push_back(mao[k]);
								break;
							}
						}
						return retorno;
					}
				}
			}
			retorno.clear();
			return retorno;
		}

		std::vector<SolutionShelves::Ref<Card>> TexasHoldem::Trinca(const std::vector<SolutionShelves::Ref<Card>>& mao)
		{
			std::vector<SolutionShelves::Ref<Card>> retorno;
			std::vector<SolutionShelves::Ref<Card>> retornoTrinca;
			bool achouTrinca = false;

			for (int8_t i = (int8_t)mao.size() - 1; i >= 0; i--)
			{
				retornoTrinca.push_back(mao[i]);
				if (retornoTrinca.size() == 1) continue;

				for (uint8_t j = 0; j < retornoTrinca.size() - 1; j++)
				{
					if (!(retornoTrinca[j]->GetCardFaceValue() == retornoTrinca[(uint64_t)j + 1]->GetCardFaceValue()))
					{
						if (i > 1)
						{
							retornoTrinca.clear();
							retornoTrinca.push_back(mao[i]);
							break;
						}
						else
						{
							retorno.clear();
							return retorno;
						}
					}
				}
				if (retornoTrinca.size() == 3)
				{
					achouTrinca = true;
					break;
				}
			}

			if (achouTrinca)
			{
				for (int8_t i = (int8_t)mao.size() - 1; i >= 0; i--)
				{
					if (mao[i]->GetCardFaceValue() == retornoTrinca[0]->GetCardFaceValue()) continue;
					retornoTrinca.push_back(mao[i]);
					if (retornoTrinca.size() == 5)
					{
						for (auto& it : retornoTrinca)
							retorno.push_back(it);
						return retorno;
					}
				}
			}
			retorno.clear();
			return retorno;
		}

		std::vector<SolutionShelves::Ref<Card>> TexasHoldem::Sequencia(const std::vector<SolutionShelves::Ref<Card>>& mao)
		{
			std::vector<SolutionShelves::Ref<Card>> retorno;

			std::vector<SolutionShelves::Ref<Card>> asesBaixos;
			std::vector<SolutionShelves::Ref<Card>> cinSemCopias;

			for (uint8_t i = 0; i < mao.size(); i++)
			{
				bool achouCarta = false;
				SolutionShelves::Ref<Card> c = mao[i];
				for (auto& it : cinSemCopias)
				{
					if (it->GetCardFaceValue() == c->GetCardFaceValue())
					{
						achouCarta = true;
						break;
					}
				}
				if (!achouCarta) cinSemCopias.push_back(c);
			}

			for (int8_t i = (int8_t)cinSemCopias.size() - 1; i >= 0; i--)
			{
				if (cinSemCopias[i]->GetCardFaceValue() == FaceValue::Ace) asesBaixos.push_back(cinSemCopias[i]);
				retorno.push_back(cinSemCopias[i]);
				if (retorno.size() == 1) continue;

				for (uint8_t j = 0; j < retorno.size() - 1; j++)
				{
					if (!(retorno[j]->GetCardFaceValue() == (FaceValue)((uint8_t)retorno[(uint64_t)j + 1]->GetCardFaceValue() + 1)))
					{
						if (i > 2)
						{
							retorno.clear();
							retorno.push_back(cinSemCopias[i]);
							break;
						}
						else
						{
							retorno.clear();
							return retorno;
						}
					}
				}
				if (retorno.size() == 4)
				{
					if (retorno[3]->GetCardFaceValue() == FaceValue::Deuce)
					{
						if (asesBaixos.size() > 0)
							retorno.push_back(asesBaixos[0]);
					}
				}
				if (retorno.size() == 5) return retorno;
			}
			return retorno;

		}

		std::vector<SolutionShelves::Ref<Card>> TexasHoldem::Flush(const std::vector<SolutionShelves::Ref<Card>>& mao)
		{
			std::vector<SolutionShelves::Ref<Card>> retorno;
			uint8_t qtdEspadas = 0;
			uint8_t qtdPaus = 0;
			uint8_t qtdCopas = 0;
			uint8_t qtdOuros = 0;
			bool achouFlush = false;
			Suit naipeFlush = Suit::Unknown;

			for (auto& it : mao)
			{
				switch (it->GetCardSuit())
				{
				case Suit::Spades:
					qtdEspadas++;
					if (qtdEspadas == 5)
					{
						achouFlush = true;
						it->GetCardSuit();
					}
					break;
				case Suit::Clubs:
					qtdPaus++;
					if (qtdPaus == 5)
					{
						achouFlush = true;
						it->GetCardSuit();
					}
					break;
				case Suit::Diamonds:
					qtdOuros++;
					if (qtdOuros == 5)
					{
						achouFlush = true;
						it->GetCardSuit();
					}
					break;
				case Suit::Hearts:
					qtdCopas++;
					if (qtdCopas == 5)
					{
						achouFlush = true;
						it->GetCardSuit();
					}
					break;
				}
				if (achouFlush) break;
			}
			for (int8_t i = (int8_t)mao.size() - 1; i >= 0; i--)
			{
				if (mao[i]->GetCardSuit() != naipeFlush) continue;
				retorno.push_back(mao[i]);
				if (retorno.size() == 5) return retorno;
			}
			retorno.clear();
			return retorno;
		}

		std::vector<SolutionShelves::Ref<Card>> TexasHoldem::FullHouse(const std::vector<SolutionShelves::Ref<Card>>& mao)
		{
			std::vector<SolutionShelves::Ref<Card>> retorno;

			std::vector<SolutionShelves::Ref<Card>> retornoTrinca;
			std::vector<SolutionShelves::Ref<Card>> retornoPar;
			bool achouTrinca = false;

			for (int8_t i = (int8_t)mao.size() - 1; i >= 0; i--)
			{
				retornoTrinca.push_back(mao[i]);
				if (retornoTrinca.size() == 1) continue;

				for (uint8_t j = 0; j < retornoTrinca.size() - 1; j++)
				{
					if (!(retornoTrinca[j]->GetCardFaceValue() == retornoTrinca[(uint64_t)j + 1]->GetCardFaceValue()))
					{
						if (i > 1)
						{
							retornoTrinca.clear();
							retornoTrinca.push_back(mao[i]);
							break;
						}
						else
						{
							retorno.clear();
							return retorno;
						}
					}
				}
				if (retornoTrinca.size() == 3)
				{
					achouTrinca = true;
					break;
				}
			}

			if (achouTrinca)
			{
				for (int8_t i = (int8_t)mao.size() - 1; i >= 0; i--)
				{
					if (mao[i]->GetCardFaceValue() == retornoTrinca[0]->GetCardFaceValue()) continue;
					retornoPar.push_back(mao[i]);
					if (retornoPar.size() == 1) continue;

					for (int j = 0; j < retornoPar.size() - 1; j++)
					{
						if (!(retornoPar[j]->GetCardFaceValue() == retornoPar[(uint64_t)j + 1]->GetCardFaceValue()))
						{
							if (i > 0)
							{
								retornoPar.clear();
								retornoPar.push_back(mao[i]);
								break;
							}
							else
							{
								retorno.clear();
								return retorno;
							}
						}
					}
					if (retornoPar.size() == 2)
					{
						for (auto& it : retornoTrinca)
							retorno.push_back(it);
						for (auto& it : retornoPar)
							retorno.push_back(it);
						return retorno;
					}
				}
			}
			retorno.clear();
			return retorno;
		}

		std::vector<SolutionShelves::Ref<Card>> TexasHoldem::Quadra(const std::vector<SolutionShelves::Ref<Card>>& mao)
		{
			std::vector<SolutionShelves::Ref<Card>> retorno;
			for (int8_t i = (int8_t)mao.size() - 1; i >= 0; i--)
			{
				retorno.push_back(mao[i]);
				if (retorno.size() == 1) continue;

				for (uint8_t j = 0; j < retorno.size() - 1; j++)
				{
					if (!(retorno[j]->GetCardFaceValue() == retorno[(uint64_t)j + 1]->GetCardFaceValue()))
					{
						if (i > 3)
						{
							retorno.clear();
							retorno.push_back(mao[i]);
							break;
						}
						else
						{
							retorno.clear();
							return retorno;
						}
					}
				}
				if (retorno.size() == 4)
				{
					for (int8_t k = (int8_t)mao.size() - 1; k >= 0; k--)
					{
						if (mao[k]->GetCardFaceValue() != retorno[0]->GetCardFaceValue())
						{
							retorno.push_back(mao[k]);
							break;
						}
					}
					return retorno;
				}
			}
			retorno.clear();
			return retorno;
		}

		std::vector<SolutionShelves::Ref<Card>> TexasHoldem::StraightFlush(const std::vector<SolutionShelves::Ref<Card>>& mao)
		{
			std::vector<SolutionShelves::Ref<Card>> retorno = Flush(mao);
			if (retorno.size()) {
				retorno = Sequencia(retorno);
			}
			return retorno;
		}

		void TexasHoldem::CriarBaralho(CardBack cardback)
		{
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Ace, Suit::Spades));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Deuce, Suit::Spades));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Tray, Suit::Spades));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Four, Suit::Spades));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Five, Suit::Spades));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Six, Suit::Spades));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Seven, Suit::Spades));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Eight, Suit::Spades));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Nine, Suit::Spades));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Ten, Suit::Spades));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Jack, Suit::Spades));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Queen, Suit::Spades));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::King, Suit::Spades));

			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Ace, Suit::Diamonds));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Deuce, Suit::Diamonds));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Tray, Suit::Diamonds));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Four, Suit::Diamonds));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Five, Suit::Diamonds));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Six, Suit::Diamonds));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Seven, Suit::Diamonds));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Eight, Suit::Diamonds));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Nine, Suit::Diamonds));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Ten, Suit::Diamonds));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Jack, Suit::Diamonds));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Queen, Suit::Diamonds));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::King, Suit::Diamonds));

			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Ace, Suit::Clubs));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Deuce, Suit::Clubs));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Tray, Suit::Clubs));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Four, Suit::Clubs));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Five, Suit::Clubs));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Six, Suit::Clubs));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Seven, Suit::Clubs));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Eight, Suit::Clubs));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Nine, Suit::Clubs));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Ten, Suit::Clubs));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Jack, Suit::Clubs));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Queen, Suit::Clubs));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::King, Suit::Clubs));

			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Ace, Suit::Hearts));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Deuce, Suit::Hearts));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Tray, Suit::Hearts));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Four, Suit::Hearts));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Five, Suit::Hearts));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Six, Suit::Hearts));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Seven, Suit::Hearts));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Eight, Suit::Hearts));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Nine, Suit::Hearts));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Ten, Suit::Hearts));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Jack, Suit::Hearts));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::Queen, Suit::Hearts));
			m_Baralho.push_back(SolutionShelves::CreateRef<Card>(m_CardSpriteSheet, m_CardBackSpriteSheet, cardback, FaceValue::King, Suit::Hearts));
		}

		void TexasHoldem::OrdenarCartas(std::vector<SolutionShelves::Ref<Card>>& cartas)
		{
			sort(cartas.begin(), cartas.end(), [](const SolutionShelves::Ref<Card>& left, const SolutionShelves::Ref<Card>& right) 
				{ 
					return (uint32_t)left->GetCardFaceValue() < (uint32_t)right->GetCardFaceValue();
				});
		}

		void TexasHoldem::EmbaralhaCartas(std::vector<SolutionShelves::Ref<Card>>& cartas)
		{
			for (uint32_t i = 0; i < QUANTIDADE_EMBARALHADAS; i++)
			{
				uint32_t seed = static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count());
				std::shuffle(cartas.begin(), cartas.end(), std::default_random_engine(seed));
			}

			for(auto & it : cartas)
			{
				it->SetRenderPosition({ -0.5, -0.5 });
				it->SetRenderSize(0.1f);
				it->EnableRender();
				it->SetRevealed(false);
			}
			PosicionaCartasDeck();
		}

		void TexasHoldem::PosicionaCartasDeck()
		{
			if (m_PosicaoBotao == -1) return;

			for (auto& it : m_Baralho)
			{
				float posX = 0.0f;
				float posY = 0.0f;
				auto orientation = m_Jogadores[m_PosicaoBotao]->GetOrientation();
				auto buttonPosition = m_Jogadores[m_PosicaoBotao]->GetDealerChipPosition();
				switch (orientation)
				{
				case Orientation::UP:
					posX = buttonPosition.x - 0.5f;
					posY = buttonPosition.y;
					break;
				case Orientation::DOWN:
					posX = buttonPosition.x - 0.25f;
					posY = buttonPosition.y - 0.25f;
					break;
				case Orientation::LEFT:
					posX = buttonPosition.x;
					posY = buttonPosition.y - 0.25f;
					break;
				case Orientation::RIGHT:
					posX = buttonPosition.x;
					posY = buttonPosition.y + 0.25f;
					break;
				}

				it->SetRenderPosition({ posX, posY });
				it->SetRenderSize(0.1f);
				it->EnableRender();
				it->SetRevealed(false);
			}
		}

		void TexasHoldem::PosicionaCartasMesa()
		{
			uint32_t cartasRestantes = (uint32_t)m_CartasMesa.size();
			for (uint32_t i = 0; i < (uint32_t)m_CartasMesa.size(); i++)
			{
				cartasRestantes--;
				float posX = (0.16f * i) - (cartasRestantes * 0.16f);
				float posY = 0.15f;

				m_CartasMesa[i]->SetRenderPosition({ posX, posY });
				m_CartasMesa[i]->SetRenderSize(0.25f);
				m_CartasMesa[i]->EnableRender();
				m_CartasMesa[i]->SetRevealed(true);
			}
		}

		void TexasHoldem::PosicionaCartasMuck()
		{
			if (m_PosicaoBotao == -1) return;

			for (auto& it : m_CartasMuck)
			{
				float posX = 0.0f;
				float posY = 0.0f;
				auto orientation = m_Jogadores[m_PosicaoBotao]->GetOrientation();
				auto buttonPosition = m_Jogadores[m_PosicaoBotao]->GetDealerChipPosition();
				switch (orientation)
				{
				case Orientation::UP:
					posX = buttonPosition.x - 0.75f;
					posY = buttonPosition.y;
					break;
				case Orientation::DOWN:
					posX = buttonPosition.x - 0.50f;
					posY = buttonPosition.y - 0.25f;
					break;
				case Orientation::LEFT:
					posX = buttonPosition.x - 0.25f;
					posY = buttonPosition.y - 0.25f;
					break;
				case Orientation::RIGHT:
					posX = buttonPosition.x + 0.25f;
					posY = buttonPosition.y + 0.25f;
					break;
				}

				it->SetRenderPosition({ posX, posY });
				it->SetRenderSize(0.05f);
				it->EnableRender();
				it->SetRevealed(false);
			}
		}
	
	}
}
