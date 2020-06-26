#pragma once

#include "Core/Base.h"

#include "Entities/Card.h"
#include "Entities/Player.h"

#include "Entities/ChipStack.h"

#include <future>

namespace PokerSS
{
	namespace TexasHoldem
	{
		enum class EstadoJogo
		{
			PreJogo,
			Jogo,
			FimRodada,
			FimJogo
		};
		enum class FaseRodada
		{
			Pre_Flop,
			Flop,
			Turn,
			River,
			CleanUp,
			FimDeJogo
		};

		enum class VelocidadeTorneio
		{
			Normal,
			Turbo
		};

		enum class AcoesJogador
		{
			Mesa,
			Fugir,
			Chamar,
			Apostar,
			Aumentar
		};

		enum class TipoMao
		{
			HighCard,
			Par,
			DoisPares,
			Trinca,
			Sequencia,
			Flush,
			FullHouse,
			Quadra,
			StraightFlush
		};

		struct DadosMao
		{
			uint32_t Pontos;
			std::string Descricao;
			int32_t IndiceJogador;

			DadosMao(uint32_t pontos, const std::string descricao)
				: Pontos(pontos), Descricao(descricao), IndiceJogador(-1)
			{
			}
			DadosMao(uint32_t pontos, const std::string descricao, int32_t indiceJogador)
				: Pontos(pontos), Descricao(descricao), IndiceJogador(indiceJogador)
			{
			}

		};

		struct SidePot
		{
			SolutionShelves::Ref<Player> JogadorExcluido;
			uint32_t Valor;
			uint32_t ValorAllIn;
			SidePot(SolutionShelves::Ref<Player> jogador, uint32_t valor, uint32_t valorAllIn)
				: JogadorExcluido(jogador), Valor(valor), ValorAllIn(valorAllIn)
			{
			}
		};

		class TexasHoldem
		{
		public:
			TexasHoldem();
			~TexasHoldem();

			std::string GetVencedores();
			
			void SetaCardBack(CardBack cardBack) { m_CardBackBaralho = cardBack; }
			void SetaBlinds(uint32_t qtd);
			void SetaAnte(uint32_t qtd);
			void AdicionaJogador(const std::string& nome);
			void AdicionaFichasJogador(uint32_t indiceJogador, uint32_t qtdFichas);
			void AcaoJogador(AcoesJogador tipoAcao, uint32_t qtdFichas);

			uint32_t GetNumeroMao() const { return m_NumeroMao; }
			std::vector<SolutionShelves::Ref<Player>> GetJogadores() const { return m_Jogadores; }
			EstadoJogo GetEstadoJogo() const { return m_EstadoJogoAtual; }
			uint32_t GetPote() const { return m_Pote->GetChipAmount(); }
			std::vector<SolutionShelves::Ref<Card>> GetBaralho() const { return m_Baralho; }
			std::vector<SolutionShelves::Ref<Card>> GetMuck() const { return m_CartasMuck; }
			std::vector<SolutionShelves::Ref<Card>> GetMesa() const { return m_CartasMesa; }
			std::vector<AcoesJogador> GetAcoesPossiveis(int32_t jogadorPedindo = -1);
			uint32_t GetApostaMinima();
			uint32_t GetApostaMaxima();
			SolutionShelves::Ref<std::vector<std::string>> GetLog() const { return m_Log; }
			bool GetAguardando() const { return m_Aguardando; }
			
			void Start();
		private:
			// Controles do Jogo
			void ReinicializaEngine();
			void IniciarJogo();
			void NovaMao();
			void IniciaNovaMao();
			void AvancaJogo();
			std::vector<DadosMao> RankeiaJogadores();
			void AumentaBlinds();
			void ProximoJogadorMesmaFase();
			void ProximoJogador();
			SolutionShelves::Ref<Card> ProximaCarta();
			uint32_t ProximaPosicao(uint32_t pos);
			uint32_t PosicaoAnterior(uint32_t pos);
			void SetaDealer(uint32_t pos);
			void SetaJogadorAcao(uint32_t pos);

			// Metodos  de Analise
			void CalculaMaosJogadores();
			DadosMao AnalisaMao(const std::vector<SolutionShelves::Ref<Card>>& mao);
			uint32_t CalculaPontos(const std::vector<SolutionShelves::Ref<Card>>& mao, TipoMao tipo);
			uint32_t QuantidadeJogadoresNoJogo();
			bool VerificaShowdown();

			std::vector<SolutionShelves::Ref<Card>> CartaAlta(const std::vector<SolutionShelves::Ref<Card>>& mao);
			std::vector<SolutionShelves::Ref<Card>> UmPar(const std::vector<SolutionShelves::Ref<Card>>& mao);
			std::vector<SolutionShelves::Ref<Card>> DoisPares(const std::vector<SolutionShelves::Ref<Card>>& mao);
			std::vector<SolutionShelves::Ref<Card>> Trinca(const std::vector<SolutionShelves::Ref<Card>>& mao);
			std::vector<SolutionShelves::Ref<Card>> Sequencia(const std::vector<SolutionShelves::Ref<Card>>& mao);
			std::vector<SolutionShelves::Ref<Card>> Flush(const std::vector<SolutionShelves::Ref<Card>>& mao);
			std::vector<SolutionShelves::Ref<Card>> FullHouse(const std::vector<SolutionShelves::Ref<Card>>& mao);
			std::vector<SolutionShelves::Ref<Card>> Quadra(const std::vector<SolutionShelves::Ref<Card>>& mao);
			std::vector<SolutionShelves::Ref<Card>> StraightFlush(const std::vector<SolutionShelves::Ref<Card>>& mao);

			// Deck
			void CriarBaralho(CardBack cardback);
			void OrdenarCartas(std::vector<SolutionShelves::Ref<Card>>& cartas);
			void EmbaralhaCartas(std::vector<SolutionShelves::Ref<Card>>& cartas);
			void DistribuirCartasIniciais();
			void PosicionaCartasDeck();
			void PosicionaCartasMesa();
			void PosicionaCartasMuck();

		private:
			// Constantes
			const uint8_t QUANTIDADE_CARTAS_JOGO = 2;
			const uint8_t QUANTIDADE_EMBARALHADAS = 7;
			const uint8_t MAXIMO_JOGADORES = 10;
			const uint32_t TEMPO_AGUARDAR = 5;

			// Textures
			SolutionShelves::Ref<SolutionShelves::Texture2D> m_CardSpriteSheet;
			SolutionShelves::Ref<SolutionShelves::Texture2D> m_CardBackSpriteSheet;
			SolutionShelves::Ref<SolutionShelves::Texture2D> m_ChipsSpriteSheet;
			SolutionShelves::Ref<SolutionShelves::Texture2D> m_PlayerTextureLeft;
			SolutionShelves::Ref<SolutionShelves::Texture2D> m_PlayerTextureRight;
			SolutionShelves::Ref<SolutionShelves::Texture2D> m_DealerChip;
			
			CardBack m_CardBackBaralho;

			std::vector<SolutionShelves::Ref<Card>> m_Baralho;
			std::vector<SolutionShelves::Ref<Player>> m_Jogadores;

			EstadoJogo m_EstadoJogoAtual;
			FaseRodada m_FaseRodadaAtual;

			uint32_t m_ApostaAtual;
			uint32_t m_UltimoAumento;
			uint32_t m_Stack;
			SolutionShelves::Ref<ChipStack> m_Pote;

			std::vector<SolutionShelves::Ref<Card>> m_CartasMesa;
			std::vector<SolutionShelves::Ref<Card>> m_CartasMuck;

			uint32_t m_IndiceJogadorAcao;
			uint32_t m_IndiceFimRodada;

			uint32_t m_SmallBlind;
			uint32_t m_BigBlind;
			uint32_t m_Ante;

			uint32_t m_NivelInicialBlind;
			int32_t m_PosicaoBotao;

			float m_TempoCrescimentoBlinds;
			float m_TempoDecorridoBlind;
			uint32_t m_ToggleBlind;

			uint32_t m_NumeroMao;

			std::vector<SidePot> m_SidePots;

			SolutionShelves::Ref<std::vector<std::string>> m_Log;
			char m_LogString[600];

			bool m_Aguardando;
			std::vector<std::future<void>> m_Futures;
			bool m_AcaoFechada;
		};
	}
}

