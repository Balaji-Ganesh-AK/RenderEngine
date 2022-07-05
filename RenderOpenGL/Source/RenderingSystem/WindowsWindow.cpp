#include "WindowsWindow.h"
#include "utility/EngineCore.h"
#include "utility/GLFWIncludes.h"



namespace KREngine
{
	WindowsProperties::WindowsProperties(ERenderingAPI renderingAPI, const float Height, const float Width,
	                                     std::string&& screenTitle): API(renderingAPI), WindowHeight(Height),
	                                                                 WindowWidth(Width)
	                                                                 , ScreenTitle(std::move(screenTitle))
	{
	}

	bool WindowsProperties::OnWindowsEvent(FEvent& Event)
	{
		EventDispatcher dispatcher(Event);
		bool bSuccess{ false };
		bSuccess &= dispatcher.Dispatch<WindowResizeEvent>(DNE_BIND_SINGLE_EVENT(WindowsProperties::OnWindowsResize));

		return bSuccess;
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

	bool WindowsProperties::OnWindowsResize(WindowResizeEvent& event)
	{
		SetWidthHeight(static_cast<float>(event.GetWidth()), static_cast<float>(event.GetHeight()));

		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		return true;
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
			glfwSetFramebufferSizeCallback(CurrentWindow, [](GLFWwindow* window, int width, int height)
				{
					WindowsProperties* WindowsPro = static_cast<WindowsProperties*>(glfwGetWindowUserPointer(window));
					WindowResizeEvent window_resize_event(width, height);

					WindowsPro->EventCallBack(window_resize_event);
				});
			glfwSetWindowCloseCallback( CurrentWindow, OnWindowCloseEvent );
			glfwSetKeyCallback(CurrentWindow, [](GLFWwindow* window, int key, int scanCode, int action, int mods)
			{
					WindowsProperties* WindowsPro = static_cast<WindowsProperties*>(glfwGetWindowUserPointer(window));

					switch (action)
					{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						WindowsPro->EventCallBack(event);
						break;

					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						WindowsPro->EventCallBack(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyReleasedEvent event(key);
						WindowsPro->EventCallBack(event);
						break;
					}
					default: ;
					}


					KeyPressedEvent keyboard_event(key,0);

					WindowsPro->EventCallBack(keyboard_event);
			});

			/*Mouse call back events*/

			/*Mouse button events*/

			glfwSetMouseButtonCallback(CurrentWindow, [](GLFWwindow* window, int button, int action, int mods)
				{
					WindowsProperties* WindowsPro = static_cast<WindowsProperties*>(glfwGetWindowUserPointer(window));
					switch (action)
					{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);

						WindowsPro->EventCallBack(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						WindowsPro->EventCallBack(event);
						break;
					}
					default:;
					}
				});

			/*Mouse scroll event*/

			glfwSetScrollCallback(CurrentWindow, [](GLFWwindow* window, double xOffset, double yOffset)
				{
					WindowsProperties* WindowsPro = static_cast<WindowsProperties*>(glfwGetWindowUserPointer(window));

					MouseScrollEvent event(xOffset, yOffset);
					WindowsPro->EventCallBack(event);


				});


			/*Mouse Cursor callback event*/

			glfwSetCursorPosCallback(CurrentWindow, [](GLFWwindow* window, double xpos, double ypos)
				{
					WindowsProperties* WindowsPro = static_cast<WindowsProperties*>(glfwGetWindowUserPointer(window));

					MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
					WindowsPro->EventCallBack(event);
				});

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

	void WindowsWindow::OnWindowResizeEvent(GLFWwindow* window, int width, int height)
	{


	}

	void WindowsWindow::OnWindowCloseEvent( GLFWwindow* window )
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

