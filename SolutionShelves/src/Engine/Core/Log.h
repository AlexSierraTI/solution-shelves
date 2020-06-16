#pragma once

#include "Engine/Core/Base.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace SolutionShelves
{

	class SOLUTION_SHELVES_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		
	};

}

// Core log macros
#define SS_CORE_TRACE(...)    ::SolutionShelves::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SS_CORE_INFO(...)     ::SolutionShelves::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SS_CORE_WARN(...)     ::SolutionShelves::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SS_CORE_ERROR(...)    ::SolutionShelves::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SS_CORE_CRITICAL(...) ::SolutionShelves::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SS_TRACE(...)         ::SolutionShelves::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SS_INFO(...)          ::SolutionShelves::Log::GetClientLogger()->info(__VA_ARGS__)
#define SS_WARN(...)          ::SolutionShelves::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SS_ERROR(...)         ::SolutionShelves::Log::GetClientLogger()->error(__VA_ARGS__)
#define SS_CRITICAL(...)      ::SolutionShelves::Log::GetClientLogger()->critical(__VA_ARGS__)
