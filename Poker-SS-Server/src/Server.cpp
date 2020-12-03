#include "Server.h"

namespace PokerSS
{

	bool Server::OnClientConnect(SolutionShelves::Ref<SolutionShelves::connection<MsgTypes>> client)
	{
		SolutionShelves::message<MsgTypes> msg;
		msg.header.id = MsgTypes::ServerAccept;
		client->Send(msg);

		return true;
	}

	void Server::OnClientDisconnect(SolutionShelves::Ref<SolutionShelves::connection<MsgTypes>> client)
	{
		SS_WARN("Removendo cliente [{0}]", client->GetID());
	}

	void Server::OnMessage(SolutionShelves::Ref<SolutionShelves::connection<MsgTypes>> client, SolutionShelves::message<MsgTypes>& msg)
	{
		switch (msg.header.id)
		{
		case MsgTypes::ServerPing:
			SS_INFO("[{0}]: Server Ping", client->GetID());
			client->Send(msg);
			break;

		}
	}
}
