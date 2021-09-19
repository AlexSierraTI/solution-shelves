#include "sspch.h"
#include "Engine/Renderer/Buffer.h"

#include "Engine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace SolutionShelves
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:      SS_CORE_ASSERT(false, "RendererAPI::None nao suportada!"); return nullptr;
			case RendererAPI::API::OpenGL:    return CreateRef<OpenGLVertexBuffer>(size);
		}
		SS_CORE_ASSERT(false, "RendererAPI desconhecido!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:      SS_CORE_ASSERT(false, "RendererAPI::None nao suportada!"); return nullptr;
			case RendererAPI::API::OpenGL:    return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		SS_CORE_ASSERT(false, "RendererAPI desconhecido!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:      SS_CORE_ASSERT(false, "RendererAPI::None nao suportada!"); return nullptr;
			case RendererAPI::API::OpenGL:    return CreateRef<OpenGLIndexBuffer>(indices, count);
		}
		SS_CORE_ASSERT(false, "RendererAPI desconhecido!");
		return nullptr;
	}
}
