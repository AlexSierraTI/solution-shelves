include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

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

group "Dependencies"
	include "vendor/premake"
	include "SolutionShelves/vendor/GLFW"
	include "SolutionShelves/vendor/Glad"
	include "SolutionShelves/vendor/ImGui"
	include "SolutionShelves/vendor/yaml-cpp"
group ""

include "SolutionShelves"
include "Sandbox"
include "SolutionShelves-Editor"
