workspace "TDRL-game-engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist",
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "TDRL"
	location "TDRL"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/third_party/spdlog/include",
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
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Pong")
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

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

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
