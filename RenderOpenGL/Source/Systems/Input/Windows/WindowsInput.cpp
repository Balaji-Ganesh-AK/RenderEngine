#include "WindowsInput.h"

#include "RenderingSystem/FRenderingSystem.h"

namespace KREngine
{
	WindowsInput::WindowsInput(std::shared_ptr<KREngine::FRenderingSystem> renderingSystem)
	{
		RenderingSystem = renderingSystem;
	}

	bool WindowsInput::IsKeyPressed( EKeyCode keyCode)
	{
		GLFWwindow* window = RenderingSystem->GetGFLWWindow();

		if( window )
		{
			const int state = glfwGetKey( window, static_cast< int >( keyCode ) );
			return state == GLFW_PRESS|| state == GLFW_REPEAT;
		}
		return false;
	}	 
		 
	bool WindowsInput::IsMouseKeyPressed( EKeyCode mouseCode)
	{
		GLFWwindow* window = RenderingSystem->GetGFLWWindow();

		if ( window )
		{
			const int state = glfwGetMouseButton( window, static_cast< int >( mouseCode ) );
			return state == GLFW_PRESS;
		}
		return false;
	}	 
		 
	KREngine::Vec2 WindowsInput::GetMousePosition()
	{
		GLFWwindow* window = RenderingSystem->GetGFLWWindow();
		Vec2 _mouse_pos_;
		double xpos, ypos;
		glfwGetCursorPos( window, &xpos, &ypos );
		_mouse_pos_.x = static_cast< float >( xpos );
		_mouse_pos_.y = static_cast< float >( ypos );
		return _mouse_pos_;
		return Vec2();
	}
}
