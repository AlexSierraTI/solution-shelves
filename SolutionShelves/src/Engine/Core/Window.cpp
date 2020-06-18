#include "sspch.h"
#include "Window.h"

#ifdef SS_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace SolutionShelves
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
	#ifdef SS_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
	#else
		SS_CORE_ASSERT(false, "Platforma desconhecida!");
		return nullptr;
	#endif
	}

}