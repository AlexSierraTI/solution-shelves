#include "sspch.h"
#include "Engine/Renderer/Shader.h"

#include "Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace SolutionShelves
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:      SS_CORE_ASSERT(false, "RendererAPI::None nao suportada!"); return nullptr;
		case RendererAPI::API::OpenGL:    return CreateRef<OpenGLShader>(filepath);
		}
		SS_CORE_ASSERT(false, "RendererAPI desconhecido!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:      SS_CORE_ASSERT(false, "RendererAPI::None nao suportada!"); return nullptr;
			case RendererAPI::API::OpenGL:    return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		SS_CORE_ASSERT(false, "RendererAPI desconhecido!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		SS_CORE_ASSERT(!Exists(name), "Shader ja existe!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}


	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		SS_CORE_ASSERT(Exists(name), "Shader inencontravel!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}
