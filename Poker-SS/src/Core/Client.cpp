#include "Client.h"

#include "Base.h"
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

namespace PokerSS
{
	void Client::Teste()
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

		// Create hint structure for the server
		sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(54000);
		inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

		// Socket creation
		SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

		// Write out to that socket
		std::string envio = "Alo mundo";
		int sendOk = sendto(out, envio.c_str(), (uint32_t)envio.size() + 1, 0, (sockaddr*)&server, (uint32_t)sizeof(server));

		if (sendOk == SOCKET_ERROR)
		{
			SS_CORE_ERROR("Erro ao enviar dados para o servidor! {0}", WSAGetLastError());
			return;
		}

		// Close the socket
		closesocket(out);

		// Close down Winsock
		WSACleanup();
	}
}