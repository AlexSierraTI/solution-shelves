#include "sspch.h"
#include "Engine/Core/Application.h"

#include "Engine/Core/Log.h"

#include "Engine/Renderer/Renderer.h"

#include "Engine/Core/Input.h"

#include <GLFW/glfw3.h>

namespace SolutionShelves
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name, ApplicationCommandLineArgs args)
		: m_CommandLineArgs(args)
	{
		SS_PROFILE_FUNCTION();

		SS_ASSERT(!s_Instance, "Application ja existe!");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(SS_BIND_EVENT_FN(Application::OnEvent));
		
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

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		SS_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SS_BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SS_BIND_EVENT_FN(OnWindowResize));

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

		LARGE_INTEGER perfCountFrequencyResult;
		QueryPerformanceFrequency(&perfCountFrequencyResult);
		int64_t perfCountFrequency = perfCountFrequencyResult.QuadPart;

		LARGE_INTEGER lastCounter;
		QueryPerformanceCounter(&lastCounter);

		while (m_Running)
		{
			SS_PROFILE_SCOPE("RunLoop");

			double time = glfwGetTime();
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

			LARGE_INTEGER endCounter;
			QueryPerformanceCounter(&endCounter);
			int64_t counterElapsed = endCounter.QuadPart - lastCounter.QuadPart;
			m_CurrentFps = (int32_t)(perfCountFrequency / counterElapsed);
			lastCounter = endCounter;
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
