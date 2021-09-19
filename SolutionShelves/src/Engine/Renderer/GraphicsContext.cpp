#include "sspch.h"
#include "Engine/Renderer/GraphicsContext.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace SolutionShelves {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SS_CORE_ASSERT(false, "RendererAPI::None insuportavel!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		SS_CORE_ASSERT(false, "RendererAPI desconhecido!");
		return nullptr;
	}

}
