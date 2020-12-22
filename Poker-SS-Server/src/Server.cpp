#include "Server.h"

namespace PokerSS
{
	Server::Server(uint16_t nPort)
		: m_ConnectionCount(0)
	{
		m_Address.host = ENET_HOST_ANY;
		m_Address.port = nPort;
		m_Server = enet_host_create(&m_Address, 32, 2, 0, 0);
		if (m_Server == NULL)
		{
			SS_ERROR("An error occurred while trying to create an server host.");
		}
		else
		{
			SS_INFO("Server host created");
		}
	}

	Server::~Server()
	{
		enet_host_destroy(m_Server);
	}

	void Server::Update()
	{
		ENetEvent event;

		if (enet_host_service(m_Server, &event, 0))
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				SS_WARN("A new client connected from {0}:{1}.",
					event.peer->address.host,
					event.peer->address.port);
				TratarConexao(event);
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				SS_WARN("A packet of length {0} containing {1} was received from {2} on channel {3}.",
					event.packet->dataLength,
					event.packet->data,
					event.peer->data,
					event.channelID);
				enet_packet_destroy(event.packet);
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				SS_WARN("{0} disconnected.", event.peer->data);
				event.peer->data = NULL;
			}
		}
	}

	void Server::TratarConexao(const ENetEvent& event)
	{
		uint32_t novoId = m_ConnectionCount;
		event.peer->data = &novoId;
		m_ConnectionCount++;

		AdicionarCliente(novoId);

		MensagemRede mensagemResposta = CriarMensagem(TipoMensagem::CONNECT, novoId, "Conexao Estabelecida", novoId);
		Send(mensagemResposta, *event.peer);
	}

	void Server::TratarMensagemRecebida(const ENetEvent& event)
	{
	}

	void Server::TratarDesconexao(const ENetEvent& event)
	{
	}

	void Server::AdicionarCliente(uint32_t id)
	{
		if (!ClienteExiste(id))
			m_ListaClientes.emplace(id, "anon");
		else
			SS_WARN("Id {0} ja existe na lista de clientes", id);
	}

	bool Server::ClienteExiste(uint32_t id)
	{
		return (m_ListaClientes.find(id) != m_ListaClientes.end());
	}

	void Server::RemoverCliente(uint32_t id)
	{
		if (ClienteExiste(id))
			m_ListaClientes.erase(id);
		else
			SS_WARN("Id {0} nao existe na lista de clientes", id);
	}

	void Server::AtualizarCliente(uint32_t id, std::string nome)
	{
		if (ClienteExiste(id))
			m_ListaClientes.at(id) = nome;
		else
			SS_WARN("Id {0} nao existe na lista de clientes", id);
	}

	MensagemRede Server::CriarMensagem(PokerSS::TipoMensagem tipo, uint32_t cliente, std::string texto, uint32_t numero, uint8_t acao)
	{
		MensagemRede retorno{};
		sprintf_s(retorno.origem, "SERVIDOR");

		retorno.tipo = tipo;
		retorno.acao = acao;
		sprintf_s(retorno.dadosTexto, texto.substr(0, 200).c_str());
		retorno.dadosNumero = numero;
		retorno.idCliente = cliente;

		return retorno;
	}

	void Server::Send(MensagemRede mensagem, ENetPeer& peer)
	{
		ENetPacket* packet = enet_packet_create(&mensagem,
			sizeof(mensagem),
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(&peer, 0, packet);
	}

	void Server::SendAll(MensagemRede mensagem, uint32_t exclude)
	{
		ENetPacket* packet = enet_packet_create(&mensagem,
			sizeof(mensagem),
			ENET_PACKET_FLAG_RELIABLE);
		for (int i = 0; i < m_Server->peerCount; i++)
		{
			if (*(uint32_t*)m_Server->peers[i].data != exclude)
				enet_peer_send(&m_Server->peers[i], 0, packet);
		}
	}
}
