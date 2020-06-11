#pragma once

#ifdef SS_PLATFORM_WINDOWS

extern SolutionShelves::Application* SolutionShelves::CreateApplication();

int main(int arc, char** argv)
{
	SolutionShelves::Log::Init();

	SS_CORE_WARN("Log Inicializado!");
	
	int a = 5;
	SS_INFO("Ola Mundo! Var={0}", a);

	auto app = SolutionShelves::CreateApplication();
	app->Run();
	delete app;
}

#endif
