
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
		files {"Source/Engine/**.h", "Source/Engine/**.cpp"}
		links {"d3d11"}

	project "Game"
		kind "WindowedApp"
		language "C++"
		targetdir "bin/%{cfg.buildcfg}"
		objdir "Temp"
		location "Source/Game"
		files {"Source/Game/**.h", "Source/Game/**.cpp"}
		includedirs{ "Source/", "Source/Engine/"}
		links{"Engine"}
