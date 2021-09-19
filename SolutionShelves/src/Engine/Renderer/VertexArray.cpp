#include "sspch.h"
#include "Engine/Renderer/VertexArray.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace SolutionShelves
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:      SS_CORE_ASSERT(false, "RendererAPI::None nao suportada!"); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateRef<OpenGLVertexArray>();
		}
		SS_CORE_ASSERT(false, "RendererAPI desconhecido!");
		return nullptr;
	}
}
