#include "sspch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace SolutionShelves
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}