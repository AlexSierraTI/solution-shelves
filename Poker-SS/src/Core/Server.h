#pragma once

#include "Base.h"
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

namespace PokerSS
{
	class Server
	{
	public:
		Server();
		~Server();

		void Run();
		void Shutdown();
	private:
		bool m_IsServerRunning;
		std::vector<RemotePlayer> m_Players;
	};
}

