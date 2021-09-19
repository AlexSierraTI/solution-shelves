#include <SolutionShelves.h>

#include "Engine/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace SolutionShelves
{

	class SolutionShelvesEditor : public Application
	{
	public:
		SolutionShelvesEditor(ApplicationCommandLineArgs args)
			: Application("Solution Shelves Editor", args)
		{
			PushLayer(new EditorLayer());
		}

		~SolutionShelvesEditor()
		{

		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new SolutionShelvesEditor(args);
	}
}
