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
			
	}

	void OnEvent(SolutionShelves::Event& event) override
	{
		if (event.GetEventType() == SolutionShelves::EventType::KeyPressed)
		{
			SolutionShelves::KeyPressedEvent& e = (SolutionShelves::KeyPressedEvent&)event;
			if (e.GetKeyCode() == SS_KEY_TAB)
				SS_TRACE("Tab apertado!");
			else
				SS_TRACE("{0}", (char)(e.GetKeyCode()));
				
		}
		
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