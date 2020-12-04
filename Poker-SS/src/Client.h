#pragma once

#include <SolutionShelves.h>
#include "enet/enet.h"

namespace PokerSS
{
	class Client
	{
	public:
		Client();
		~Client();

		void Update();

		void Connect(const std::string& endereco, uint16_t porta);
		void Disconnect();

		void Ping();

		bool IsConnected() const { return m_IsConnected; }
	private:
		ENetHost* m_Client;
		ENetPeer* m_Peer;

		bool m_IsConnected;
	};
}
