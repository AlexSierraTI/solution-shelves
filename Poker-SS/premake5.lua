project "Poker-SS"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/SolutionShelves/vendor/spdlog/include",
		"%{wks.location}/SolutionShelves/src",
		"%{wks.location}/SolutionShelves/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.enet}"
	}

	links
	{
		"SolutionShelves"
	}
	
	filter "system:windows"
		systemversion "latest"
		links
		{
			"ws2_32.lib",
			"winmm.lib"
		}
		
	filter "configurations:Debug"
		defines "SS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SS_DIST"
		runtime "Release"
		optimize "on"
