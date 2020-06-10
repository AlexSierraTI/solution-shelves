#pragma once

#ifdef SS_PLATFORM_WINDOWS

extern SolutionShelves::Application* SolutionShelves::CreateApplication();

int main(int arc, char** argv)
{
	auto app = SolutionShelves::CreateApplication();
	app->Run();
	delete app;
}

#endif