#pragma once

#include <SolutionShelves.h>

#include "Engine/Network/NetClient.h"

namespace PokerSS
{
	enum class MsgTypes : uint32_t
	{
		ServerAccept,
		ServerDeny,
		ServerPing
	};

	class Client : public SolutionShelves::client_interface<MsgTypes>
	{
	public:
		void PingServer();
		void Update();

		uint32_t GetLatency() const { return m_Latency; }
	private:
		uint32_t m_Latency = 9999;
	};
}
