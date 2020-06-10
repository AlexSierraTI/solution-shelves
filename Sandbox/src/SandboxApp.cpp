#include <SolutionShelves.h>

class SandBox : public SolutionShelves::Application
{
public:
	SandBox()
	{
	}

	~SandBox()
	{

	}
};

SolutionShelves::Application* SolutionShelves::CreateApplication()
{
	return new SandBox();
}