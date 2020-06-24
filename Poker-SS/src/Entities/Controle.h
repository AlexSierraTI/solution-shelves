#pragma once

#include "Entities/Entity.h"

#include "Core/EntityManager.h"
#include "Rules/TexasHoldem.h"


namespace PokerSS
{
	class Controle : public Entity
	{
	public:
		Controle(const SolutionShelves::Ref<TexasHoldem::TexasHoldem>& engineJogo, const SolutionShelves::Ref<EntityManager>& entityManager);
		~Controle();

		virtual void LoadAssets() override;

		virtual void OnUpdate(SolutionShelves::Timestep ts) override;
		virtual void OnRender() override;

		virtual void OnImGuiRender() override;

	private:
		void AddPlayer(const std::string& name);
		void AddChips(uint32_t playerIndex, uint32_t chipsAmount);

		void ChecarPodeComecarJogo();
	private:
		SolutionShelves::Ref<EntityManager> m_EntityManager;

		SolutionShelves::Ref<TexasHoldem::TexasHoldem> m_EngineJogo;
		
		char m_MensagemErro[50];

		uint32_t m_SelectedPlayer;
		char m_NomeJogadorInclusao[50];
		bool m_AdicionandoJogador = false;
		bool m_AdicionandoFichas = false;
		int32_t m_FichasAdicionar;
		bool m_PodeComecarJogo = false;
	};
}

