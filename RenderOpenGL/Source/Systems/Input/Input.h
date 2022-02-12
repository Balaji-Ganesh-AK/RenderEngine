#pragma once
#include "Math/Vec2.h"


namespace KREngine
{
	class WindowsWindow;

	class FInput
	{
	public:
		virtual ~FInput() = default;

		static FInput* Create(WindowsWindow* pointer);

		virtual bool IsKeyPressed(Input::KeyCodes keyCode) = 0;
		virtual  bool IsMouseKeyPressed(Input::KeyCodes mouseCode) = 0;
		virtual  Vec2 GetMousePosition() = 0;

		virtual void GetMousePosition(Vec2& mousePos) = 0;

	protected:

	};


}
