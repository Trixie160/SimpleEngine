
workspace "SimpleEngine"
	startproject "Game"
	architecture "x64"
	language "C++"
	cppdialect "C++20"
	warnings "Extra"
	flags { "FatalWarnings" }
	objdir "Temp"

	local shader_dir = "../../Bin/Shaders/"
	os.mkdir(shader_dir)

	defines { 
		'SHADER_DIR="' .. shader_dir .. '"' 
	}

	configurations {
		"Debug",
		"Release"
	}

	filter "configurations:Debug"
		defines { "_DEBUG" }
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines { "_RELEASE" }
		optimize "On"
		runtime "Release"

	project "Engine"
		kind "StaticLib"
		targetdir "Lib"
		targetname("%{prj.name}_%{cfg.buildcfg}")
		location "Source/Engine"
		includedirs{"Source/Engine/"}
		files {"Source/Engine/**.h", "Source/Engine/**.cpp", "Source/Engine/Shaders/**hlsl"}
		links {"d3d11"}

		shadermodel("5.0")
		
		filter("files:**.hlsl")
			shaderobjectfileoutput(shader_dir.."%{file.basename}"..".cso")

		filter("files:Source/Engine/Shaders/PS/**.hlsl")
			shadertype("Pixel")

		filter("files:Source/Engine/Shaders/VS/**.hlsl")
			shadertype("Vertex")

	project "Game"
		kind "WindowedApp"
		targetdir "Bin/%{cfg.buildcfg}"
		targetname "SimpleEngine_%{cfg.buildcfg}"
		location "Source/Game"
		includedirs{ "Source/", "Source/Engine/" ,"Source/Game/"}
		files {"Source/Game/**.h", "Source/Game/**.cpp", "Source/Game/Resources/**.rc"}
		dependson { "Engine" }
		links { "Engine"}
