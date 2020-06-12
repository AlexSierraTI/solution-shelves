#include <SolutionShelves.h>

class ExampleLayer : public SolutionShelves::Layer
{
public:
	ExampleLayer()
		: Layer("Teste Layer")
	{
	}

	void OnUpdate() override
	{
		SS_INFO("ExampleLayer::Update");
	}

	void OnEvent(SolutionShelves::Event& event) override
	{
		SS_TRACE("{0}", event);
	}
};

class SandBox : public SolutionShelves::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new SolutionShelves::ImGuiLayer());
	}

	~SandBox()
	{

	}
};

SolutionShelves::Application* SolutionShelves::CreateApplication()
{
	return new SandBox();
}