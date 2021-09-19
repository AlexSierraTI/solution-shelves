project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "off"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"include"
	}
	
	filter "system:windows"
		systemversion "latest"

		filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
