#include "sspch.h"
#include "Texture.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace SolutionShelves
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:      SS_CORE_ASSERT(false, "RendererAPI::None nao suportada!"); return nullptr;
		case RendererAPI::API::OpenGL:    return std::make_shared<OpenGLTexture2D>(path);
		}
		SS_CORE_ASSERT(false, "RendererAPI desconhecido!");
		return nullptr;
	}
}
