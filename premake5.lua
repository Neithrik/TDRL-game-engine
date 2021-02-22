workspace "TDRL-game-engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory).
IncludeDir = {}
IncludeDir["GLFW"] = "TDRL/third_party/glfw/include"
IncludeDir["GLEW"] = "TDRL/third_party/glew/include"

include "TDRL/third_party/GLFW"

project "TDRL"
	location "TDRL"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/third_party/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
	}

	libdirs
	{
		"%{prj.name}/third_party/glew/lib/Release/x64",
	}

	bindirs
	{
		"%{prj.name}/third_party/glew/bin/Release/x64",
	}

	links
	{
		"GLFW",
		"glew32.lib",
		"opengl32.lib",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.19041.0"

		defines
		{
			"TDRL_PLATFORM_WINDOWS",
			"TDRL_BUILD_DLL",
			"_WINDLL",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Pong")
		}

	filter "configurations:Debug"
		defines "TDRL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "TDRL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "TDRL_DIST"
		optimize "On"

project "Pong"
	location "Pong"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"TDRL/third_party/spdlog/include",
		"tdrl/src", 
	}


	links
	{
		"tdrl"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.19041.0"

		defines
		{
			"TDRL_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "TDRL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "TDRL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "TDRL_DIST"
		optimize "On"
