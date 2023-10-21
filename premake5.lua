
workspace "SimpleEngine"
	startproject "Game"
	architecture "x64"
	warnings "Extra"
	flags {"FatalWarnings"}
	cppdialect "C++20"

	configurations {
		"Debug",
		"Release"
	}

	project "Engine"
		kind "StaticLib"
		language "C++"
		targetdir "Lib"
		objdir "Temp"
		location "Source/Engine"
		files {"Source/Engine/**.h", "Source/Engine/**.cpp", "Source/Engine/Shaders/**hlsl"}
		includedirs{"Source/Engine/"}
		links {"d3d11"}

		shadermodel("5.0")

	filter("files:**PS.hlsl")
		shadertype("Pixel")

	filter("files:**VS.hlsl")
		shadertype("Vertex")

	project "Game"
		kind "WindowedApp"
		language "C++"
		targetdir "bin/%{cfg.buildcfg}"
		objdir "Temp"
		location "Source/Game"
		files {"Source/Game/**.h", "Source/Game/**.cpp", "Source/Game/Resources/**.rc"}
		includedirs{ "Source/", "Source/Engine/"}
		links{"Engine"}
		dependson {"Engine"}
