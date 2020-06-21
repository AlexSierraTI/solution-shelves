#include <SolutionShelves.h>

#include "GameLayer.h"

#include "Engine/Core/EntryPoint.h"

namespace PokerSS
{
	class PokerSSApp : public SolutionShelves::Application
	{
	public:
		PokerSSApp()
			: SolutionShelves::Application("Poker SS App")
		{
			PushLayer(new GameLayer());
		}

		~PokerSSApp()
		{

		}
	};
}

SolutionShelves::Application* SolutionShelves::CreateApplication()
{
	return new PokerSS::PokerSSApp();
}

