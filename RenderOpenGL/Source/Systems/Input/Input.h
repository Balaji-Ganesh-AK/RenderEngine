#pragma once
#include "Math/Vec2.h"
#include "utility/InputCodes.h"


namespace KREngine
{
	class MouseMovedEvent;
	class FEvent;
	class WindowsWindow;

	class FInput
	{
	public:
		virtual ~FInput() = default;
		virtual bool OnEvent(FEvent &event) = 0;
		static FInput* Create(WindowsWindow* pointer);

		virtual bool IsKeyPressed(Input::KeyCodes keyCode) = 0;
		virtual  bool IsMouseKeyPressed(Input::MouseCode mouseCode) = 0;
		virtual  Vec2 GetMousePosition() = 0;

		virtual void GetMousePosition(Vec2& mousePos) = 0;




		/*Event functions*/
		virtual bool OnMouseMovedEvent(MouseMovedEvent& event) = 0;

	protected:

	};


}
