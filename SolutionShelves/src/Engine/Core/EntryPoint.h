#pragma once

#ifdef SS_PLATFORM_WINDOWS

extern SolutionShelves::Application* SolutionShelves::CreateApplication();

int main(int arc, char** argv)
{
	SolutionShelves::Log::Init();

	SS_PROFILE_BEGIN_SESSION("Startup", "SolutionShelvesProfile-Startup.json");
	auto app = SolutionShelves::CreateApplication();
	SS_PROFILE_END_SESSION();

	SS_PROFILE_BEGIN_SESSION("Runtime", "SolutionShelvesProfile-Runtime.json");
	app->Run();
	SS_PROFILE_END_SESSION();

	SS_PROFILE_BEGIN_SESSION("Shutdown", "SolutionShelvesProfile-Shutdown.json");
	delete app;
	SS_PROFILE_END_SESSION();

	return 0;
}

#endif
