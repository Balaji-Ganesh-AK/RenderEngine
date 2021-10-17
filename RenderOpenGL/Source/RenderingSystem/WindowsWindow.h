#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../utility/Enums.h"


class WindowsProperties
{
	
	
	public:
		WindowsProperties(){};
		WindowsProperties( ERenderingAPI renderingAPI, const int32 Height, const int32 Width, std::string&& screenTitle ) : API( renderingAPI ), WindowHeight( Height ), WindowWidth( Width )
			, ScreenTitle( std::move( screenTitle ) )
		{
		};

	static WindowsProperties DefaultOpenGl()
	{
		WindowsProperties window_properties( ERenderingAPI::OpenGL , 800, 600, "OpenGL");
		return window_properties;
	}

	ERenderingAPI GetAPI() const
	{
		return API;
	}
	int32 GetHeight() const
	{
		return WindowHeight;
	}
	int32 GetWidth() const
	{
		return WindowWidth;
	}
	const std::string& GetTitle() const 
	{
		return ScreenTitle;
	}
private:
	ERenderingAPI API {ERenderingAPI::OpenGL};
	int32 WindowHeight =1080;
	int32 WindowWidth = 720;
	std::string ScreenTitle = "Renderer";
	GLFWmonitor* Moniter = nullptr;
private:
	
};

class WindowsWindow
{
public:
	virtual ~WindowsWindow() = default;

	WindowsWindow();;
	WindowsWindow( WindowsProperties& windowProperties );
	

	GLFWwindow* GetCurrentWindow();
	void static WindowResizeEvent( GLFWwindow* window, int width, int height );
private:
	WindowsProperties* Properties = nullptr;
	/* Current active window */
	GLFWwindow* CurrentWindow = nullptr;


//Function:
private:
	void Init();
	
	
	
};





