#pragma once
#include <string>

#include "utility/GLFWIncludes.h"
#include "Systems/Event/FEvent.h"


namespace KREngine
{

	class WindowsProperties
	{
	
	
	public:
		WindowsProperties() = default;
		~WindowsProperties()
		{
			Moniter = nullptr;
		}
		WindowsProperties(ERenderingAPI renderingAPI, const float Height, const float Width,
		                  std::string&& screenTitle);

		WindowsProperties(const WindowsProperties& Other): API(Other.API),WindowHeight(Other.WindowHeight), WindowWidth(Other.WindowWidth), ScreenTitle(Other.ScreenTitle),Moniter(Other.Moniter)
		{
		}

		bool OnWindowsEvent(FEvent& Event);
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

		bool OnWindowsResize(WindowResizeEvent& event);


		EventCallBackFn EventCallBack;
	

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
		void static OnWindowResizeEvent( GLFWwindow* window, int width, int height );
		void static OnWindowCloseEvent( GLFWwindow* window );


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





