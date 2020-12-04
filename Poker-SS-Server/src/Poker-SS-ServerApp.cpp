#include <SolutionShelves.h>

#include "MainLayer.h"

#include "Engine/Core/EntryPoint.h"

#include "enet/enet.h"

namespace PokerSS
{

	class PokerSSServer : public SolutionShelves::Application
	{
	public:
		PokerSSServer()
			: Application("Poker-SS-Server")
		{
			PushLayer(new MainLayer());
		}

		~PokerSSServer()
		{
		}
	};
}

SolutionShelves::Application* SolutionShelves::CreateApplication()
{
	if (enet_initialize() != 0)
	{
		SS_ERROR("An error occurred while initializing.");
	}
	atexit(enet_deinitialize);
	return new PokerSS::PokerSSServer();
}
