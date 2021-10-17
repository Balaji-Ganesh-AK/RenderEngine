#include "WindowsWindow.h"





#include "../utility/KRELogger.h"

WindowsWindow::WindowsWindow()
{
}

WindowsWindow::WindowsWindow(WindowsProperties& windowProperties)
{
	Properties = &windowProperties;
	Init();
	switch ( windowProperties.GetAPI() )
	{
		case ERenderingAPI::OpenGL:
			CurrentWindow = glfwCreateWindow( windowProperties.GetWidth(), windowProperties.GetHeight(), windowProperties.GetTitle().c_str(), NULL, NULL );
			if ( !CurrentWindow )
			{
			
				glfwTerminate();
				KREngine::KRELogger::Error( "Failed to create window with openGL" );
			}
			glfwMakeContextCurrent( CurrentWindow );
			glfwSwapInterval( 1 );
			glfwSetFramebufferSizeCallback( CurrentWindow, WindowResizeEvent);
			if ( !gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress ) )
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

void WindowsWindow::Init()
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

GLFWwindow* WindowsWindow::GetCurrentWindow()
{
	return CurrentWindow;
}

void WindowsWindow::WindowResizeEvent(GLFWwindow* window, int width, int height)
{
	glViewport( 0, 0, width, height );
}
