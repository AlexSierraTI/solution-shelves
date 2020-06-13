workspace "EngineGrafico"
	architecture "x86_64"

	filter "system:windows"
		disablewarnings { "4996", "4251" }
		
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "SolutionShelves/vendor/GLFW/include"
IncludeDir["Glad"] = "SolutionShelves/vendor/Glad/include"
IncludeDir["ImGui"] = "SolutionShelves/vendor/ImGui"
IncludeDir["glm"] = "SolutionShelves/vendor/glm"

group "Dependencias"
	include "SolutionShelves/vendor/GLFW"
	include "SolutionShelves/vendor/Glad"
	include "SolutionShelves/vendor/ImGui"

group ""

project "SolutionShelves"
	location "SolutionShelves"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "sspch.h"
	pchsource "SolutionShelves/src/sspch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines 
		{
			"SS_PLATFORM_WINDOWS",
			"SS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
	
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "SS_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SS_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SS_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"SolutionShelves/vendor/spdlog/include",
		"SolutionShelves/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"SolutionShelves"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines 
		{
			"SS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SS_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SS_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SS_DIST"
		runtime "Release"
		optimize "On"
