#pragma once

#include "Core/Base.h"

#include "Entities/Card.h"
#include "Entities/Player.h"

namespace PokerSS
{
	namespace TexasHoldem
	{
		enum class EstadoJogo
		{
			PreJogo,
			Jogo,
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
			Apostar
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

			DadosMao(uint32_t pontos, const std::string descricao)
				: Pontos(pontos), Descricao(descricao)
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
			void AdicionaJogador(const SolutionShelves::Ref<Player>& j);
			void AdicionaFichasJogador(uint32_t indiceJogador, uint32_t qtdFichas);

			uint32_t GetNumeroMao() const { return m_NumeroMao; }
			std::vector<SolutionShelves::Ref<Player>> GetJogadores() const { return m_Jogadores; }
			EstadoJogo GetEstadoJogo() const { return m_EstadoJogoAtual; }
			
			void Start();

		private:
			// Controles do Jogo
			void ReinicializaEngine();
			void IniciarJogo();
			void NovaMao();
			std::vector<SolutionShelves::Ref<Player>> RankeiaJogadores();
			void AumentaBlinds();
			void AvancaJogo();
			void ProximoJogadorMesmaFase();
			void ProximoJogador();
			SolutionShelves::Ref<Card> ProximaCarta();
			uint32_t ProximaPosicao(uint32_t pos);
			void AcaoJogador(AcoesJogador tipoAcao, uint32_t qtdFichas);

			// Metodos  de Analise
			void CalculaMaosJogadores();
			DadosMao AnalisaMao(const std::vector<SolutionShelves::Ref<Card>>& mao);
			uint32_t CalculaPontos(const std::vector<SolutionShelves::Ref<Card>>& mao, TipoMao tipo);

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
		private:
			// Spritesheets
			SolutionShelves::Ref<SolutionShelves::Texture2D> m_CardSpriteSheet;
			SolutionShelves::Ref<SolutionShelves::Texture2D> m_CardBackSpriteSheet;

			CardBack m_CardBackBaralho;

			std::vector<SolutionShelves::Ref<Card>> m_Baralho;
			std::vector<SolutionShelves::Ref<Player>> m_Jogadores;

			EstadoJogo m_EstadoJogoAtual;
			FaseRodada m_FaseRodadaAtual;

			uint32_t m_ApostaAtual;
			uint32_t m_Stack;
			std::vector<SolutionShelves::Ref<Card>> m_CartasMesa;
			std::vector<SolutionShelves::Ref<Card>> m_CartasMuck;

			SolutionShelves::Ref<Player> m_JogadorAcao;
			uint32_t m_IndiceJogadorAcao;
			uint32_t m_QuantidadeJogadoresNoJogo;
			uint32_t m_IndiceFimRodada;

			uint32_t m_SmallBlind;
			uint32_t m_BigBlind;
			uint32_t m_Ante;

			uint32_t m_NivelInicialBlind;
			uint32_t m_PosicaoBotao;

			float m_TempoCrescimentoBlinds;
			float m_TempoDecorridoBlind;
			uint32_t m_ToggleBlind;

			uint32_t m_NumeroMao;

			std::vector<SidePot> m_SidePots;

			const uint8_t QUANTIDADE_CARTAS_JOGO = 2;
			const uint8_t QUANTIDADE_EMBARALHADAS = 7;
			const uint8_t MAXIMO_JOGADORES = 10;
		};
	}
}

