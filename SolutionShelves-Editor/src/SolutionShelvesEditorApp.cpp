#include <SolutionShelves.h>

#include "EditorLayer.h"

#include "Engine/Core/EntryPoint.h"

namespace SolutionShelves
{

	class SolutionShelvesEditor : public Application
	{
	public:
		SolutionShelvesEditor()
			: Application("Solution Shelves Editor")
		{
			PushLayer(new EditorLayer());
		}

		~SolutionShelvesEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new SolutionShelvesEditor();
	}
}