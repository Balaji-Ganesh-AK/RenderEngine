#pragma once
#include "utility/Pch.h"


namespace KREngine
{
	class FRenderingSystem;
	class WindowsInput : public FInput
	{
	public:
		WindowsInput( std::shared_ptr<FRenderingSystem> renderingSystem );
		~WindowsInput() {};
		virtual bool IsKeyPressed( EKeyCode keyCode) override;
		virtual bool IsMouseKeyPressed( EKeyCode mouseCode) override;
		virtual Vec2 GetMousePosition() override;
	private:
		std::shared_ptr<FRenderingSystem> RenderingSystem;
	};
}
