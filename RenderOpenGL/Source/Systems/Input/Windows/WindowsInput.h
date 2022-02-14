#pragma once
#include "Systems/Input/Input.h"

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
		virtual bool IsMouseKeyPressed(Input::MouseCode mouseCode) override;
		virtual Vec2 GetMousePosition() override;
		void GetMousePosition(Vec2& mousePos) override;
		bool OnEvent(FEvent& event) override;
		bool OnMouseMovedEvent(MouseMovedEvent& event) override;
	private:
		WindowsWindow* WindowWindow;
		Vec2 MousePos;
		std::bitset< static_cast<int>(Input::KeyCodes::Count)> KeyCodes;
	};
}
