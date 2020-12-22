#pragma once

#include <SolutionShelves.h>

namespace PokerSS
{
	enum class TipoMensagem
	{
		CONNECT, RECONNECT, LOGIN, LOGOUT, CHAT, ACK, NACK
	};

	typedef struct _MensagemRede
	{
		uint32_t idCliente;
		TipoMensagem tipo;
		char origem[50];
		uint8_t acao;
		char dadosTexto[200];
		uint32_t dadosNumero;
	} MensagemRede;

}
