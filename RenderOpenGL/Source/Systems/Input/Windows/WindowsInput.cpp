#include "WindowsInput.h"

#include "RenderingSystem/WindowsWindow.h"
#include "Systems/Event/FEvent.h"


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
		 
	bool WindowsInput::IsMouseKeyPressed(Input::MouseCode mouseCode)
	{
		auto* window = WindowWindow->GetCurrentWindow();
		if ( window  )
		{
			const int state = glfwGetMouseButton( window, static_cast< int >( mouseCode ) );
			return state == GLFW_PRESS;
		}
		return false;
	}

	bool WindowsInput::IsMouseKeyPressedInViewPort(Input::MouseCode mouseCode)
	{
		auto* window = WindowWindow->GetCurrentWindow();
		auto [mouse_x, mouse_y] = ImGui::GetMousePos();
		const bool insideViewport = mouse_x >= MinBounds.x && mouse_x <= MaxBounds.x &&
									mouse_y >= MinBounds.y && mouse_y <= MaxBounds.y;
		if (window && insideViewport)
		{
			const int state = glfwGetMouseButton(window, static_cast<int>(mouseCode));
			return state == GLFW_PRESS;
		}
		return false;
	}

	Vec2 WindowsInput::GetMousePosition()
	{
		/*Return the cursor position in framebuffer texel space (origin bottom-left, for glReadPixels).
		 *The scene image is drawn at the window/framebuffer resolution, so the panel-relative position
		 *maps 1:1 to framebuffer texels; only Y must be flipped, and by the FRAMEBUFFER height (not the
		 *ImGui panel height, which is what the previous code used).*/
		auto [mouse_x, mouse_y] = ImGui::GetMousePos();
		mouse_x -= MinBounds.x;
		mouse_y -= MinBounds.y;
		const float frameBufferHeight = WindowWindow->Properties->GetHeight();
		mouse_y = frameBufferHeight - mouse_y;
		return Vec2(mouse_x, mouse_y);
	}

	void WindowsInput::GetMousePosition(Vec2& mousePos)
	{
		mousePos = MousePos;
	}

	bool WindowsInput::OnEvent(FEvent& event)
	{
		EventDispatcher dispatcher(event);
		bool bSuccess{ false };
		bSuccess &= dispatcher.Dispatch<MouseMovedEvent>(DNE_BIND_SINGLE_EVENT(WindowsInput::OnMouseMovedEvent));
		return bSuccess;
	}

	bool WindowsInput::OnMouseMovedEvent(MouseMovedEvent& event)
	{
		
		MousePos.x = event.GetMouseX();
		MousePos.y = event.GetMouseY();
		
		return true;
	}
}
