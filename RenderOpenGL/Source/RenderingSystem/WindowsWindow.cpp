#include "WindowsWindow.h"

#include <glad/glad.h>


namespace KREngine
{
	WindowsProperties::WindowsProperties(ERenderingAPI renderingAPI, const float Height, const float Width,
	                                     std::string&& screenTitle): API(renderingAPI), WindowHeight(Height),
	                                                                 WindowWidth(Width)
	                                                                 , ScreenTitle(std::move(screenTitle))
	{
	}

	WindowsProperties WindowsProperties::DefaultOpenGl()
	{
		WindowsProperties window_properties(ERenderingAPI::OpenGL, 1080, 720, "KAAR Engine v:0.001");
		return window_properties;
	}

	ERenderingAPI WindowsProperties::GetAPI() const
	{
		return API;
	}

	float WindowsProperties::GetHeight() const
	{
		return WindowHeight;
	}

	float WindowsProperties::GetWidth() const
	{
		return WindowWidth;
	}

	const std::string& WindowsProperties::GetTitle() const
	{
		return ScreenTitle;
	}

	bool WindowsProperties::IsOpen() const
	{
		return BIsOpen;
	}

	void KREngine::WindowsProperties::SetWidthHeight(float width, float height)
	{
		WindowWidth = width;
		WindowHeight = height;
	}


	KREngine::WindowsWindow::WindowsWindow()
	{
	}

	KREngine::WindowsWindow::WindowsWindow(WindowsProperties& windowProperties)
	{
		Properties = &windowProperties;
		Init();
		switch ( windowProperties.GetAPI() )
		{
		case ERenderingAPI::OpenGL:
			CurrentWindow = glfwCreateWindow( static_cast< int >(windowProperties.GetWidth()), static_cast< int >(windowProperties.GetHeight()), windowProperties.GetTitle().c_str(), NULL, NULL );
			if ( !CurrentWindow )
			{
			
				glfwTerminate();
				KREngine::KRELogger::Error( "Failed to create window with openGL" );
			}
			glfwMakeContextCurrent( CurrentWindow );
			glfwSwapInterval( 1 );
			glfwSetWindowUserPointer( CurrentWindow, Properties );
			glfwSetFramebufferSizeCallback( CurrentWindow, WindowResizeEvent );
			glfwSetWindowCloseCallback( CurrentWindow, WindowCloseEvent );
			if ( !gladLoadGLLoader( reinterpret_cast<GLADloadproc>(glfwGetProcAddress) ) )
			{
				KREngine::KRELogger::Error( "Failed to init GLAD" );
				_ASSERT( false );
			}
			break;
		case ERenderingAPI::Vulkan:
			KREngine::KRELogger::Warning( "Not Supported Yet" );
			_ASSERT( false );
			break;
		default:
			KREngine::KRELogger::Error( "No rendering API, Cant create a window" );
			_ASSERT( false);
			break;
			;
		}

	}



	void KREngine::WindowsWindow::Init()
	{
		if ( !glfwInit() )
		{
			KREngine::KRELogger::Error( "GLFW is missing" );
			_ASSERT( false );
		}
	


		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 4 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	}

	GLFWwindow* KREngine::WindowsWindow::GetCurrentWindow() const
	{
		return CurrentWindow;
	}

	void WindowsWindow::WindowResizeEvent(GLFWwindow* window, int width, int height)
	{
		WindowsProperties* WindowsPro = static_cast<WindowsProperties*>(glfwGetWindowUserPointer(window));
		WindowsPro->SetWidthHeight( static_cast<float>(width), static_cast<float>(height) );
		glViewport( 0, 0, width, height );
	}

	void WindowsWindow::WindowCloseEvent( GLFWwindow* window )
	{
		WindowsProperties* WindowsPro = static_cast< WindowsProperties* >( glfwGetWindowUserPointer( window ) );
		WindowsPro->OnCloseClicked();
	}

	bool WindowsWindow::IsActive() const
	{
		if (Properties)
		{
			return Properties->IsOpen();
		}
		else
			return false;
	}
}

