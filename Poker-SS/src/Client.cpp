#include "Client.h"

namespace PokerSS
{
	void Client::PingServer()
	{
		if (IsConnected())
		{
			SolutionShelves::message<MsgTypes> msg;
			msg.header.id = MsgTypes::ServerPing;

			std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
			msg << timeNow;

			Send(msg);
		}
	}

	void Client::Update()
	{
		if (IsConnected())
		{
			if(!Incoming().empty())
			{
				auto msg = Incoming().pop_front().msg;
				switch (msg.header.id)
				{
					case MsgTypes::ServerAccept:
						SS_INFO("Servidor aceitou a conexao");
						break;
					case MsgTypes::ServerPing:
						std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
						std::chrono::system_clock::time_point timeThen;
						msg >> timeThen;

						double_t elapsedTime = std::chrono::duration<double>(timeNow - timeThen).count();

						SS_INFO("Ping: {0}", elapsedTime);

						m_Latency = (uint32_t)(elapsedTime * 1000);

						break;
				}
			}
		}
	}
}
