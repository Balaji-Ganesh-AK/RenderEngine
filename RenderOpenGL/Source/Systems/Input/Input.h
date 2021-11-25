#pragma once
#include "utility/Pch.h"


namespace KREngine
{
	class Vec2;
	class FInput 
	{
	public:
		virtual ~FInput() = default;
		
		virtual bool IsKeyPressed( EKeyCode keyCode ) = 0;
		virtual bool IsMouseKeyPressed( EKeyCode mouseCode ) = 0;
		virtual Vec2 GetMousePosition() = 0;
	private:


	};
}