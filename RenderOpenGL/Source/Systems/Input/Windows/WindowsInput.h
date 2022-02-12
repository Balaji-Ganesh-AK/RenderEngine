#pragma once
#include "Systems/Input/Input.h"
#include "utility/Pch.h"

namespace KREngine
{
	class WindowsInput : public FInput
	{
	public:
		WindowsInput(WindowsWindow* pointer);
		~WindowsInput()
		{
			
		}
		virtual bool IsKeyPressed(Input::KeyCodes keyCode) override;
		virtual bool IsMouseKeyPressed(Input::KeyCodes mouseCode) override;
		virtual Vec2 GetMousePosition() override;
		void GetMousePosition(Vec2& mousePos) override;
	private:
		WindowsWindow* WindowWindow;
	};
}
