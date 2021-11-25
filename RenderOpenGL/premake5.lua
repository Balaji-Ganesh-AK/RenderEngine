workspace "RenderOpenGL"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Shippment"
	}
	
outputdir = "%{cfg.buildcfg}"

project "RenderOpenGL"
	location "RenderOpenGL"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "%{prj.name}")
	
	files
	{
		"Source/**.h",
		"Source/**.cpp",
		"Content/**.GLSL",
		"Glad/**.c",
		"Dependencies/ImGUI/**.h",
		"Dependencies/ImGUI/**.cpp",
		"Dependencies/glm/glm/**.hpp",
		"Dependencies/glm/glm/**.h",
		"Dependencies/glm/glm/**.cpp",
		"Dependencies/glm/glm/**.inl",
		"Content/**.GLSL",
		"Config/**.ini"
	}
	
	includedirs 
	{
		"$(SolutionDir)/Dependencies/glm",
		"$(SolutionDir)/Dependencies/ ",
		"$(SolutionDir)/Dependencies/GLFW/include",
		"$(SolutionDir)/Dependencies/glad",
		"$(SolutionDir)/Source/"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
		
		}
		
		filter "configurations:Debug"
			defines
			{
				"_CRTDBG_MAP_ALLOC",
				"GUI",
				"LOGGING",
				"PROFILE",
				"_DEBUG",
				"_CONSOLE",
			}
			links
			{
				"glfw3.lib",
				"opengl32.lib"
			}
			symbols "on"
		filter "configurations:Release"
			defines
			{
				"_CRTDBG_MAP_ALLOC",
				"GUI",
				"LOGGING",
				"PROFILE",
				"NDEBUG",
				"_CONSOLE",
				"ENGINE_ONLY",
			}
			links
			{
				"glfw3.lib",
				"opengl32.lib",
				"msvcrt.lib",
				"msvcmrt.lib"
			}
			optimize "On"
		