#pragma once

#include <SolutionShelves.h>

#include "Engine/Network/NetServer.h"

namespace PokerSS
{
	enum class MsgTypes : uint32_t
	{
		ServerAccept,
		ServerDeny,
		ServerPing
	};

	class Server : public SolutionShelves::server_interface<MsgTypes>
	{
	public:
		Server(uint16_t nPort) 
			: SolutionShelves::server_interface<MsgTypes>(nPort)
		{
		}
	protected:
		virtual bool OnClientConnect(SolutionShelves::Ref<SolutionShelves::connection<MsgTypes>> client);

		virtual void OnClientDisconnect(SolutionShelves::Ref<SolutionShelves::connection<MsgTypes>> client);

		virtual void OnMessage(SolutionShelves::Ref<SolutionShelves::connection<MsgTypes>> client, SolutionShelves::message<MsgTypes>& msg);
	};
}
