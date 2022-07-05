// ReSharper disable CppClangTidyModernizeUseNodiscard
#pragma once
#include <functional>
#include <sstream>

#include "utility/Enums.h"


namespace KREngine
{
	
#define DNE_BIND_SINGLE_EVENT(fn) std::bind(&fn, this, std::placeholders::_1)
	class FEvent
	{
	public:
		virtual ~FEvent() = default;
		bool bHandled = false;

		virtual EEventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryValue() const = 0;
		virtual std::string ToString() const { return GetName(); }


		bool IsInEventCategory(EEventCategory category) const
		{
			return GetCategoryValue() & category;
		}

	};



	using EventCallBackFn = std::function<void(FEvent&)>;
#define EVENT_CLASS_TYPE(type) static EEventType GetStaticType(){return EEventType::type;}\
	virtual EEventType GetEventType() const override{return GetStaticType();}\
	virtual const char* GetName() const override{return #type;}


#define EVENT_CLASS_CATEGORY(cat) virtual int GetCategoryValue() const override{return cat;};

	/*class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			:_event_(event)
		{

		}
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if(_event_.GetEventType() == T::GetStaticType())
			{
				_event_.handled = func(static_cast<T&>(_event_));
				return true;
			}
			return false;
		}

	private:
		Event& _event_;
	};*/
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(FEvent& event)
			:Event(event)
		{

		}
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (Event.GetEventType() == T::GetStaticType())
			{
				Event.bHandled = func(*static_cast<T*>(&Event));
				return true;
			}
			return false;
		}

	private:
		FEvent& Event;
	};

	class KeyboardEvent : public FEvent
	{
	public:
		KeyboardEvent(int keyCode) :KeyCode(keyCode) {}
	protected:
		

		int KeyCode;
	};
	class KeyPressedEvent : public KeyboardEvent
	{
	public:

		KeyPressedEvent(int key, int repeat) :KeyboardEvent(key), RepeatedCount(repeat) {}
		int GetRepeatCount() const { return RepeatedCount; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Pressed Event: " << KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard)

	private:
		int RepeatedCount = 0;


	};
	class KeyReleasedEvent : public KeyboardEvent
	{

	public:
		KeyReleasedEvent(int keyCode) :KeyboardEvent(keyCode)
		{}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Released Event: " << KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard)


	};





	/*Mouse Event*/
	class MouseMovedEvent :public FEvent
	{
	public:
		MouseMovedEvent(float x, float y) :
			MouseX(x), MouseY(y)
		{}

		float GetMouseX() const { return MouseX; }
		float GetMouseY() const { return MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << MouseX << ", " << MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse)

	private:
		float MouseX, MouseY;
	};


	class MouseScrollEvent :public FEvent
	{
	public:
		MouseScrollEvent(double x, double y) :
			MouseOffsetX(x), MouseOffsetY(y)
		{}

		double GetMouseX() const { return MouseOffsetX; }
		double GetMouseY() const { return MouseOffsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Scrolled event: " << MouseOffsetX << ", " << MouseOffsetY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScroll)
		EVENT_CLASS_CATEGORY(EventCategoryMouse)

	private:
		double MouseOffsetX;
		double MouseOffsetY;
	};


	class MouseButtonPressedEvent :public FEvent
	{
	public:
		MouseButtonPressedEvent(int mouseCode) :MouseCode(mouseCode)
		{}

		int GetMouseButton() const { return MouseCode; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Pressed Event: " << MouseCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
		EVENT_CLASS_CATEGORY(EventCategoryMouse)

	private:

		int MouseCode = 0;
	};
	class MouseButtonReleasedEvent :public FEvent
	{
	public:
		MouseButtonReleasedEvent(const int mouseCode) :MouseCode(mouseCode)
		{}
		int GetMouseButton() const { return MouseCode; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button Released Event: " << MouseCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
		EVENT_CLASS_CATEGORY(EventCategoryMouse)
	private:

		int MouseCode = 0;
	};

	/*Windows Event*/
	class WindowCreateEvent :public FEvent
	{
	public:
		WindowCreateEvent(unsigned int width, unsigned int height) :
			Width(width), Height(height)
		{}

		unsigned int GetWidth() const { return Width; }
		unsigned int GetHeight() const { return Height; }

		EVENT_CLASS_TYPE(WindowCreate)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)

	private:
		unsigned int Width, Height;
	};


	class WindowResizeEvent :public FEvent
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) :
			Width(width), Height(height)
		{}

		unsigned int GetWidth() const { return Width; }
		unsigned int GetHeight() const { return Height; }


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Resize Event: " << Width << "," << Height;
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)

	private:
		unsigned int Width, Height;
	};


	class WindowCloseEvent :public FEvent
	{
	public:
		WindowCloseEvent() = default;

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Windows Closed!";
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)



	};
}
