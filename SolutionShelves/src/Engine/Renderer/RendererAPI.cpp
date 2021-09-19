#include "sspch.h"
#include "Engine/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace SolutionShelves
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::None:    SS_CORE_ASSERT(false, "RendererAPI::None insuportavel!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		SS_CORE_ASSERT(false, "RendererAPI desconhecido!");
		return nullptr;
	}
}
