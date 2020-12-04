#include "Client.h"

namespace PokerSS
{
	Client::Client()
		: m_IsConnected(false), m_Peer(nullptr)
	{
		m_Client = enet_host_create(NULL, 1, 2, 0, 0);
		if (m_Client == NULL)
		{
			SS_ERROR("An error occurred while trying to create an client host.");
		}
		else
		{
			SS_INFO("Client host created.");
		}
	}

	Client::~Client()
	{
		enet_host_destroy(m_Client);
	}
	void Client::Update()
	{
		if (!m_IsConnected) return;

		ENetEvent event;

		if (enet_host_service(m_Client, &event, 0))
		{
			switch (event.type)
			{
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
				m_IsConnected = false;
			}
		}
	}

	void Client::Connect(const std::string& endereco, uint16_t porta)
	{
		ENetAddress address;
		ENetEvent event;

		enet_address_set_host(&address, endereco.c_str());
		address.port = porta;

		m_Peer = enet_host_connect(m_Client, &address, 2, 0);
		if (m_Peer == NULL)
		{
			SS_ERROR("No available peers for initiating an connection.");
		}
		else
		{
			if (enet_host_service(m_Client, &event, 5000) > 0 &&
				event.type == ENET_EVENT_TYPE_CONNECT)
			{
				SS_WARN("Connection to {0}:{1} succeeded.", endereco, porta);
				m_IsConnected = true;
			}
			else
			{
				enet_peer_reset(m_Peer);
				SS_WARN("Connection to {0}:{1} failed.", endereco, porta);
			}
		}
	}

	void Client::Disconnect()
	{
		ENetEvent event;
		enet_peer_disconnect(m_Peer, 0);
		m_IsConnected = false;

		while (enet_host_service(m_Client, &event, 3000) > 0)
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_RECEIVE:
				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				SS_WARN("Disconnection succeeded.");
				return;
			}
		}
		enet_peer_reset(m_Peer);
	}

	void Client::Ping()
	{
		ENetPacket* packet = enet_packet_create("PING",
			strlen("PING") + 1,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(m_Peer, 0, packet);
	}
}
