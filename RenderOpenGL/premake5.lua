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
	kind "StaticLib"
	language "C++"
	targetname ("$(ProjectName)")
	targetdir ("$(SolutionDir)bin/$(Configuration)/$(Platform)/$(ProjectName)/")
	objdir ("$(SolutionDir)/Intermediate/")
	
	files
	{
		"Source/**.h",
		"Source/**.cpp",
		"Content/**.GLSL",
		"Content/**.png",
		"Content/**.jpg",
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
		"Dependencies/FBX/lib-vc2019/**.lib",
		"Dependencies/FBX/include/**.h",
		"Content/**.GLSL",
		"Config/**.ini",
		"**.md"
	}
	removefiles { "**/foo.h", "**/CMakeCXXCompilerId.cpp" }
	links
	{		
			"$(SolutionDir)Dependencies/GLFW/lib-vc2019/glfw3",
			
			--"$(SolutionDir)Dependencies/FBX/lib/vs2019/x64/release/libfbxsdk-md",
			
	}
	

	
	includedirs 
	{
		"$(SolutionDir)/Dependencies/glm",
		"$(SolutionDir)/Dependencies/GLFW/lib-vc2019/",
		"$(SolutionDir)/Dependencies/FBX/lib/vs2019/x64/release/",
		"$(SolutionDir)/Dependencies/FBX/include",
		"$(SolutionDir)/Dependencies/",
		"$(SolutionDir)/Dependencies/GLFW/include",
		"$(SolutionDir)/Dependencies/glad",
		"$(SolutionDir)/Source/",
		"$(SolutionDir)/../"
		
	}

			
	filter "system:windows"
		cppdialect "C++20"
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
				"opengl32.lib",
			"$(SolutionDir)Dependencies/FBX/lib/vs2019/x64/debug/libfbxsdk-md",
			"$(SolutionDir)Dependencies/FBX/lib/vs2019/x64/debug/libxml2-md",
			"$(SolutionDir)Dependencies/FBX/lib/vs2019/x64/debug/zlib-md"
			
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
				"msvcmrt.lib",
				"$(SolutionDir)Dependencies/FBX/lib/vs2019/x64/release/libfbxsdk-md",
			"$(SolutionDir)Dependencies/FBX/lib/vs2019/x64/release/libxml2-md",
			"$(SolutionDir)Dependencies/FBX/lib/vs2019/x64/release/zlib-md"
			}
			optimize "On"
			
	
	
	
project "DevelopmentApp"
	location "DevelopmentApp"
	kind "ConsoleApp"
	language "C++"
	targetname ("$(ProjectName)")
	targetdir ("$(SolutionDir)bin/$(Configuration)/$(Platform)/$(ProjectName)/")
	objdir ("$(SolutionDir)/Intermediate/")	
	
	links
	{	
		"RenderOpenGL",
	
	}
	
	libdirs 
	{
		"$(SolutionDir)bin/$(Configuration)/$(Platform)/RenderOpenGL",
	}
	files
	{
		"DevelopmentApp/Source/**.h",
		"DevelopmentApp/Source/**.cpp"
	}
	removefiles { "**/foo.h", "**/CMakeCXXCompilerId.cpp" }
	includedirs 
	{
		"$(SolutionDir)/Dependencies/glm",
		"../Source/",
		"$(SolutionDir)/Source/",
		"$(SolutionDir)/Dependencies/GLFW/include",
		"$(SolutionDir)/Dependencies/FBX/include",
		"$(SolutionDir)/Dependencies/glad",
		"$(SolutionDir)/../"
	}
	filter "system:windows"
		cppdialect "C++20"
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
				
				"opengl32.lib",
				
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
	