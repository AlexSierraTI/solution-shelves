#include "sspch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace SolutionShelves
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:      SS_CORE_ASSERT(false, "RendererAPI::None nao suportada!"); return nullptr;
		case RendererAPI::API::OpenGL:    return std::make_shared<OpenGLVertexArray>();
		}
		SS_CORE_ASSERT(false, "RendererAPI desconhecido!");
		return nullptr;
	}
}
