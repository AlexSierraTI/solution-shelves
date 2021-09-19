#include "sspch.h"
#include "Engine/Renderer/UniformBuffer.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace SolutionShelves
{
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: SS_CORE_ASSERT(false, "RendererAPI::None nao suportada!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		SS_CORE_ASSERT(false, "RendererAPI desconhecida!");
		return nullptr;
	}
}
