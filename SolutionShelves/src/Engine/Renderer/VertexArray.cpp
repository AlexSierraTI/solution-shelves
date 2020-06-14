#include "sspch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace SolutionShelves
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:      SS_CORE_ASSERT(false, "RendererAPI::None nao suportada!"); return nullptr;
		case RendererAPI::OpenGL:    return new OpenGLVertexArray();
		}
		SS_CORE_ASSERT(false, "RendererAPI desconhecido!");
		return nullptr;
	}
}
