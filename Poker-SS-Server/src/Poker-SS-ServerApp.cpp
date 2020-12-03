#include <SolutionShelves.h>

#include "MainLayer.h"

#include "Engine/Core/EntryPoint.h"

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
	return new PokerSS::PokerSSServer();
}
