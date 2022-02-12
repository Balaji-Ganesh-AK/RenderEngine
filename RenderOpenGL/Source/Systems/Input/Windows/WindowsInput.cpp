#include "WindowsInput.h"


#include "RenderingSystem/WindowsWindow.h"

namespace KREngine
{
	WindowsInput::WindowsInput(WindowsWindow* pointer) :WindowWindow(pointer)
	{
		
	}

	bool WindowsInput::IsKeyPressed(Input::KeyCodes keyCode)
	{
		auto* window = WindowWindow->GetCurrentWindow();

		if( window )
		{
			const int state = glfwGetKey( window, static_cast< int >( keyCode ) );
			return state == GLFW_PRESS|| state == GLFW_REPEAT;
		}
		return false;
	}	 
		 
	bool WindowsInput::IsMouseKeyPressed(Input::KeyCodes mouseCode)
	{
		auto* window = WindowWindow->GetCurrentWindow();

		if ( window )
		{
			const int state = glfwGetMouseButton( window, static_cast< int >( mouseCode ) );
			return state == GLFW_PRESS;
		}
		return false;
	}	 
		 
	Vec2 WindowsInput::GetMousePosition()
	{
		auto* window = WindowWindow->GetCurrentWindow();
		Vec2 _mouse_pos_;
		double xpos, ypos;
		glfwGetCursorPos( window, &xpos, &ypos );
		_mouse_pos_.x = static_cast< float >( xpos );
		_mouse_pos_.y = static_cast< float >( ypos );
		return _mouse_pos_;
		
	}

	void WindowsInput::GetMousePosition(Vec2& mousePos)
	{
		auto* window = WindowWindow->GetCurrentWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		mousePos.x = static_cast<float>(xpos);
		mousePos.y = static_cast<float>(ypos);
	}
}
