
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
		local shader_dir = "../../Bin/Shaders/"
		defines { 'SHADER_DIR="' .. shader_dir .. '"' }
		os.mkdir(shader_dir)

		filter("files:**.hlsl")
			shaderobjectfileoutput(shader_dir.."%{file.basename}"..".cso")

		filter("files:**PS.hlsl")
			shadertype("Pixel")

		filter("files:**VS.hlsl")
			shadertype("Vertex")

	project "Game"
		kind "WindowedApp"
		language "C++"
		targetdir "Bin/"
		targetname "%{prj.name}_%{cfg.buildcfg}"
		objdir "Temp"
		location "Source/Game"
		files {"Source/Game/**.h", "Source/Game/**.cpp", "Source/Game/Resources/**.rc"}
		includedirs{ "Source/", "Source/Engine/"}
		links{"Engine"}
		dependson {"Engine"}
