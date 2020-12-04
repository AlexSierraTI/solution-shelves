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
		char nomeCliente[20];

		if (enet_host_service(m_Server, &event, 0))
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				SS_WARN("A new client connected from {0}:{1}.",
					event.peer->address.host,
					event.peer->address.port);

				event.peer->data = (unsigned char *)m_ConnectionCount;
				m_ConnectionCount++;
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
}
