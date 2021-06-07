#include <SolutionShelves.h>

#include "Sandbox2D.h"
#include "Sandbox3D.h"
#include "SandboxAlex.h"

#include "Engine/Core/EntryPoint.h"

class SandBox : public SolutionShelves::Application
{
public:
	SandBox(SolutionShelves::ApplicationCommandLineArgs args)
		: Application("SandBox", args)
	{
		// PushLayer(new Sandbox3D());
		PushLayer(new Sandbox2D());
		// PushLayer(new SandboxAlex);
	}

	~SandBox()
	{

	}
};

SolutionShelves::Application* SolutionShelves::CreateApplication(SolutionShelves::ApplicationCommandLineArgs args)
{
	return new SandBox(args);
}
