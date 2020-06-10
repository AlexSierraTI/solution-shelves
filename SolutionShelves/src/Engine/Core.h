#pragma once

#ifdef SS_PLATFORM_WINDOWS
	#ifdef SS_BUILD_DLL
		#define SOLUTION_SHELVES_API __declspec(dllexport)
	#else
		#define SOLUTION_SHELVES_API __declspec(dllimport)
	#endif
#else
	#error Solution Shelves apenas para Windows!
#endif