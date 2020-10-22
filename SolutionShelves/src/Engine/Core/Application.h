#pragma once

#include "Engine/Core/Base.h"

#include "Engine/Core/Window.h"
#include "Engine/Core/LayerStack.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

#include "Engine/Core/Timestep.h"

#include "Engine/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace SolutionShelves 
{
	class Application
	{
	public:
		Application(const std::string& name = "Solution Shelves App");
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }

		void Close();
		
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// A ser definido no CLIENTE
	Application* CreateApplication();
}

