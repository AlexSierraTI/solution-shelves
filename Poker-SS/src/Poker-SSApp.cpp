#include <SolutionShelves.h>

#include "MainLayer.h"

#include "Engine/Core/EntryPoint.h"

#include "enet/enet.h"

namespace PokerSS
{

	class PokerSS : public SolutionShelves::Application
	{
	public:
		PokerSS()
			: Application("Poker-SS")
		{
			PushLayer(new MainLayer());
		}

		~PokerSS()
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
	return new PokerSS::PokerSS();
}
