
workspace "SimpleEngine"
	startproject "Game"
	architecture "x64"
	warnings "Extra"
	flags {"FatalWarnings"}

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

	project "Game"
		kind "WindowedApp"
		language "C++"
		targetdir "bin/%{cfg.buildcfg}"
		objdir "Temp"
		location "Source/Game"
		files {"Source/Game/**.h", "Source/Game/**.cpp"}
		includedirs{ "Source/", "Source/Engine/"}
		links{"Engine"}


	postbuildcommands {
    "if exist \"%{wks.location}Source/Engine/Resources/Game.aps\" {MOVE} \"%{wks.location}Source/Engine/Resources/Game.aps\" \"%{wks.location}Temp/Game.aps\""
}