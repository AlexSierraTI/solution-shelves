#include "sspch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace SolutionShelves
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		SS_CORE_ASSERT(windowHandle, "Window handle nulo!");
	}

	void OpenGLContext::Init() 
	{
		SS_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SS_CORE_ASSERT(status, "Falha ao inicializar Glad!");

		SS_CORE_INFO("OpenGL Info:");
		SS_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		SS_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		SS_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		SS_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Solution Shelves requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		SS_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}
