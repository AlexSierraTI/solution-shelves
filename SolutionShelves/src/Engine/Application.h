#pragma once

#include "Core.h"

namespace SolutionShelves 
{
	class SOLUTION_SHELVES_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// A ser definido no CLIENTE
	Application* CreateApplication();
}

