#include "sspch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace SolutionShelves
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}