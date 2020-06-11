#include "Application.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"

namespace SolutionShelves
{

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategory::EventCategoryApplication))
		{
			SS_TRACE(e);
		}
		if (e.IsInCategory(EventCategory::EventCategoryInput))
		{
			SS_TRACE(e);
		}

		while (true);
	}



}