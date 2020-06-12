#pragma once

#include "Core.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Window.h"


namespace SolutionShelves 
{
	class SOLUTION_SHELVES_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// A ser definido no CLIENTE
	Application* CreateApplication();
}

