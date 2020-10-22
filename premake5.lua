include "./vendor/premake/premake_customization/solution_items.lua"

workspace "SolutionShelves"
	architecture "x86_64"
	startproject "SolutionShelves-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	solution_items
	{
		".editorconfig"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}
	

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/SolutionShelves/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/SolutionShelves/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/SolutionShelves/vendor/ImGui"
IncludeDir["glm"] = "%{wks.location}/SolutionShelves/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/SolutionShelves/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/SolutionShelves/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/SolutionShelves/vendor/yaml-cpp/include"

group "Dependencias"
	include "vendor/premake"
	include "SolutionShelves/vendor/GLFW"
	include "SolutionShelves/vendor/Glad"
	include "SolutionShelves/vendor/ImGui"
	include "SolutionShelves/vendor/yaml-cpp"
group ""

include "SolutionShelves"
include "Sandbox"
include "SolutionShelves-Editor"
