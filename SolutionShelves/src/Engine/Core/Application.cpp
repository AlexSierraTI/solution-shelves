#include "sspch.h"
#include "Application.h"

#include "Engine/Core/Log.h"

#include "Engine/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace SolutionShelves
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		SS_PROFILE_FUNCTION();

		SS_ASSERT(!s_Instance, "Application ja existe!");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create(WindowProps(name)));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		
		m_Window->SetVSync(false);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		SS_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		SS_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		SS_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{
		SS_PROFILE_FUNCTION();

		SS_ASSERT(m_LayerStack.LayerExists(layer), "Layer inexistente!");
		layer->OnDetach();
		m_LayerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* layer)
	{
		SS_PROFILE_FUNCTION();

		SS_ASSERT(m_LayerStack.LayerExists(layer), "Overlay inexistente!");
		layer->OnDetach();
		m_LayerStack.PopOverlay(layer);
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		SS_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled) 
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::Run()
	{
		SS_PROFILE_FUNCTION();

		while (m_Running)
		{
			SS_PROFILE_SCOPE("RunLoop");

			double time = glfwGetTime(); // Platform::GetTime
			Timestep timestep = (float)time - m_LastFrameTime;
			m_LastFrameTime = (float)time;

			if (!m_Minimized)
			{
				{
					SS_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
			}


			m_ImGuiLayer->Begin();
			{
				SS_PROFILE_SCOPE("LayerStack OnImGuiRender");

				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		SS_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
