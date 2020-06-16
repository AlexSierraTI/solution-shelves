#pragma once

#include <memory>

#ifdef SS_PLATFORM_WINDOWS
	#if SS_DYNAMIC_LINK
		#ifdef SS_BUILD_DLL
			#define SOLUTION_SHELVES_API __declspec(dllexport)
		#else
			#define SOLUTION_SHELVES_API __declspec(dllimport)
		#endif
	#else
		#define SOLUTION_SHELVES_API
	#endif
#else
	#error Solution Shelves apenas para Windows!
#endif

#ifdef SS_DEBUG
	#define SS_ENABLE_ASSERTS
#endif

#ifdef SS_ENABLE_ASSERTS
	#define SS_ASSERT(x, ...) { if (!(x)) { SS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define SS_CORE_ASSERT(x, ...) { if (!(x)) { SS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SS_ASSERT(x, ...) 
	#define SS_CORE_ASSERT(x, ...) 
#endif

#include "sspch.h"

#define BIT(x) (1 << x)

#define SS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace SolutionShelves
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
