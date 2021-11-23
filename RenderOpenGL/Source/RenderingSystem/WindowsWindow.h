#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../utility/Enums.h"
#include "Math/Vec2.h"


namespace KREngine
{
	class TESTCLASS
	{

	};
	class WindowsProperties
	{
	
	
	public:
		WindowsProperties() = default;
		~WindowsProperties()
		{
			Moniter = nullptr;
		}
		WindowsProperties(ERenderingAPI renderingAPI, const float Height, const float Width,
		                  std::string&& screenTitle);;

		WindowsProperties(const WindowsProperties& Other)
		{
			this->API = Other.API;
			this->WindowHeight = Other.WindowHeight;
			this->WindowWidth = Other.WindowWidth;
			this->ScreenTitle = Other.ScreenTitle;
			this->Moniter = Other.Moniter;
		}
		static WindowsProperties DefaultOpenGl();

		ERenderingAPI GetAPI() const;

		float GetHeight() const;

		float GetWidth() const;

		const std::string& GetTitle() const;

		bool IsOpen() const;
		void OnCloseClicked()
		{
			BIsOpen = false;
		}
		void SetWidthHeight( float width, float height );
	private:
		ERenderingAPI API {ERenderingAPI::OpenGL};
		float WindowHeight =1080;
		float WindowWidth = 720;
		std::string ScreenTitle = "Renderer";
		GLFWmonitor* Moniter = nullptr;

		bool BIsOpen = true;
	private:
	
	};

	class WindowsWindow
	{
	public:
		~WindowsWindow() = default;

		WindowsWindow();
		WindowsWindow( WindowsProperties& windowProperties );
	

		GLFWwindow* GetCurrentWindow() const;
		void static WindowResizeEvent( GLFWwindow* window, int width, int height );
		void static WindowCloseEvent( GLFWwindow* window );


		WindowsProperties* Properties = nullptr;

		bool IsActive() const;
	private:

		/* Current active window */
		GLFWwindow* CurrentWindow = nullptr;


		//Function:
	private:
		void Init();
	
	
	
	};
}





