#pragma once

#include <SolutionShelves.h>
#include "enet/enet.h"

#include "Protocolo.h"

namespace PokerSS
{
	class Server
	{
	public:
		Server(uint16_t nPort);
		~Server();

		void Update();
	
	private:
		void TratarConexao(const ENetEvent& event);
		void TratarMensagemRecebida(const ENetEvent& event);
		void TratarDesconexao(const ENetEvent& event);

		void AdicionarCliente(uint32_t id);
		bool ClienteExiste(uint32_t id);
		void RemoverCliente(uint32_t id);
		void AtualizarCliente(uint32_t id, std::string nome);

		MensagemRede CriarMensagem(TipoMensagem tipo, uint32_t cliente = 0, std::string texto = "", uint32_t numero = 0, uint8_t acao = 0);
		void Send(MensagemRede mensagem, ENetPeer& peer);
		void SendAll(MensagemRede mensagem, uint32_t exclude = 99);
	private:
		ENetAddress m_Address{};
		ENetHost* m_Server;

		uint32_t m_ConnectionCount;
		std::unordered_map<uint32_t, std::string> m_ListaClientes;
	};
}
