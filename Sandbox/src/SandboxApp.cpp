#include <SolutionShelves.h>

#include "Sandbox2D.h"
#include "Sandbox3D.h"

#include "Engine/Core/EntryPoint.h"

class SandBox : public SolutionShelves::Application
{
public:
	SandBox()
	{
		PushLayer(new Sandbox3D());
		PushLayer(new Sandbox2D());
	}

	~SandBox()
	{

	}
};

SolutionShelves::Application* SolutionShelves::CreateApplication()
{
	return new SandBox();
}