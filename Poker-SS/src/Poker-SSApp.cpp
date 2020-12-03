#include <SolutionShelves.h>

#include "MainLayer.h"

#include "Engine/Core/EntryPoint.h"

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
	return new PokerSS::PokerSS();
}
