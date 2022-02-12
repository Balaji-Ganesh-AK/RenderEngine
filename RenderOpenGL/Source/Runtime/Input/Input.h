// ReSharper disable CppClangTidyModernizeUseNodiscard
#pragma once


namespace KREngine
{

	//class FInput
	//{
	//public:
	//	~FInput() = default;
	//	FInput(const std::shared_ptr<WindowsWindow>& pointer): WindowWindow(pointer)
	//	{
	//	}

	//	bool IsKeyPressed(Input::KeyCodes key) const
	//	{
	//		return IsKeyPressed(static_cast<int>(key));

	//	}

	//	inline bool IsMousePressed(Input::Mouse mouseButton) const
	//	{
	//		return  IsMousePressed(mouseButton);
	//	
	//	}

	//	float GetMouseX() const
	//	{
	//		auto window = WindowWindow.get()->GetCurrentWindow();
	//		double xpos, ypos;
	//		glfwGetCursorPos(window, &xpos, &ypos);
	//		return static_cast<float>(xpos);
	//	}

	//	float GetMouseY() const
	//	{
	//		auto window = WindowWindow.get()->GetCurrentWindow();
	//		double xpos, ypos;
	//		glfwGetCursorPos(window, &xpos, &ypos);
	//		return static_cast<float>(ypos);
	//	}

	//	Vec2 GetMousePosition() const
	//	{
	//		auto window = WindowWindow.get()->GetCurrentWindow();
	//		Vec2 _mouse_pos_;
	//		double xpos, ypos;
	//		glfwGetCursorPos(window, &xpos, &ypos);
	//		_mouse_pos_.x = static_cast<float>(xpos);
	//		_mouse_pos_.y = static_cast<float>(ypos);
	//		return _mouse_pos_;
	//	}

	//protected:

	//private:
	//	//inliic bool IsKeyRepeat(int KeyCode) { return _instance_->IsKeyRepeatImp(KeyCode); };
	//	inline bool IsMousePressed(int mouseButton)
	//	{
	//		auto window = WindowWindow.get()->GetCurrentWindow();
	//		const auto state = glfwGetMouseButton(window, mouseButton);
	//		return state == GLFW_PRESS || state == GLFW_REPEAT;
	//	}

	//	bool IsKeyPressed(int keyCode) const
	//	{
	//		auto window = WindowWindow.get()->GetCurrentWindow();
	//		const auto state = glfwGetKey(window, keyCode);
	//		return state == GLFW_PRESS || state == GLFW_REPEAT;
	//	}
	//	std::shared_ptr<WindowsWindow> WindowWindow;
	//};

}

