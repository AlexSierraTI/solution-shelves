#pragma once

#include "Engine/Core/Base.h"
#include "Engine/Core/Application.h"

#include "Engine/Debug/Instrumentor.h"

#ifdef SS_PLATFORM_WINDOWS

extern SolutionShelves::Application* SolutionShelves::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	SolutionShelves::Log::Init();

	SS_PROFILE_BEGIN_SESSION("Startup", "SolutionShelvesProfile-Startup.json");
	auto app = SolutionShelves::CreateApplication({ argc, argv});
	SS_PROFILE_END_SESSION();

	SS_PROFILE_BEGIN_SESSION("Runtime", "SolutionShelvesProfile-Runtime.json");
	app->Run();
	SS_PROFILE_END_SESSION();

	SS_PROFILE_BEGIN_SESSION("Shutdown", "SolutionShelvesProfile-Shutdown.json");
	delete app;
	SS_PROFILE_END_SESSION();
}

#endif
