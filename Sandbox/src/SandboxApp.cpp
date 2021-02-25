#include <SolutionShelves.h>

#include "SandboxVulkan.h"

#include "Engine/Core/EntryPoint.h"

namespace SolutionShelves
{
	class SandBox : public Application
	{
	public:
		SandBox()
		{
			PushLayer(new SandboxVulkan());
		}

		~SandBox()
		{

		}
	};

	Application* CreateApplication()
	{
		return new SandBox();
	}
}
