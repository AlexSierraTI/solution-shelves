#pragma once

#include <SolutionShelves.h>
#include "enet/enet.h"

namespace PokerSS
{
	class Server
	{
	public:
		Server(uint16_t nPort);
		~Server();

		void Update();
	private:
		ENetAddress m_Address{};
		ENetHost* m_Server;

		uint32_t m_ConnectionCount;
	};
}
