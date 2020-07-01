#include "Server.h"

namespace PokerSS
{
	Server::Server()
		: m_IsServerRunning(true)
	{
	}
	Server::~Server()
	{
	}
	void Server::Run()
	{
		// Startup Winsock
		WSADATA data;
		WORD version = MAKEWORD(2, 2);
		int wsOk = WSAStartup(version, &data);
		if (wsOk != 0)
		{
			SS_CORE_ERROR("Nao conseguiu iniciar Winsock! {0}", wsOk);
			return;
		}

		SS_CORE_INFO("Server starting...");

		// Bind socket to ip address and prt
		SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);

		sockaddr_in serverHint;
		serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
		serverHint.sin_family = AF_INET;
		serverHint.sin_port = htons(54000); // Convert from little to big endian

		if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
		{
			SS_CORE_ERROR("Nao conseguiu dar bind no socket! {0}", WSAGetLastError());
			return;
		}

		sockaddr_in client;
		int clientLength = sizeof(client);
		ZeroMemory(&client, clientLength);

		char buf[1024];
		// Enter loop
		while (m_IsServerRunning)
		{
			char serverIp[256];
			inet_ntop(AF_INET, &serverHint.sin_addr, serverIp, 256);

			SS_CORE_INFO("Server listening at port {0}", ntohs(serverHint.sin_port));

			ZeroMemory(buf, 1024);

			// Wait for message
			int bytesIn = recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength);
			if (bytesIn == SOCKET_ERROR)
			{
				SS_CORE_ERROR("Error receiving from client {0}", WSAGetLastError());
			}

			// DO STUFF
			char clientIp[256];
			ZeroMemory(clientIp, 256);

			inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

			SS_CORE_TRACE("Message recv from {0} : {1}", clientIp, buf);
		}

		// Close socket
		closesocket(in);

		// Shutdown winsock
		WSACleanup();

	}
	void Server::Shutdown()
	{
		SS_CORE_INFO("Received server shutdown command!");
		m_IsServerRunning = false;
	}
}