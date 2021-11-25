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
	targetname ("$(ProjectName)")
	targetdir ("$(SolutionDir)bin/$(Configuration)/$(Platform)/$(ProjectName)/")
	objdir ("$(SolutionDir)/Intermediate/")
	
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
		"Dependencies/glad/**.h",
		"Dependencies/KHR/**.h",
		"Dependencies/GLFW/lib-vc2019/**.lib",
		"Dependencies/GLFW/include/**.h",
		"Content/**.GLSL",
		"Config/**.ini",
		"**.md"
	}
	
	links
	{		
			"$(SolutionDir)Dependencies/GLFW/lib-vc2019/glfw3"
	}
	
	includedirs 
	{
		"$(SolutionDir)/Dependencies/glm",
		"$(SolutionDir)/Dependencies/GLFW/lib-vc2019/",
		"$(SolutionDir)/Dependencies/",
		"$(SolutionDir)/Dependencies/GLFW/include",
		"$(SolutionDir)/Dependencies/glad",
		"$(SolutionDir)/Source/",
		"$(SolutionDir)/../"
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
				"opengl32.lib",
				"msvcrt.lib",
				"msvcmrt.lib"
			}
			optimize "On"
		