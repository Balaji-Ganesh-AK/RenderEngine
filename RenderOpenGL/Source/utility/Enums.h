#pragma once
#include "Defines.h"

enum class ERenderingAPI:
	uint8
{
	OpenGL,
	Vulkan
};


enum class DrawMode:
	uint8
{
	Static,
	Moveable
};

enum class EEventType :
	uint8
{
	None = 0,

	//----------KeyBoardEvent----------//
	KeyReleased,
	KeyPressed,

	//----------MouseEvents----------//
	MouseButtonPressed,
	MouseButtonReleased,
	MouseMoved,
	MouseScroll,


	//----------WindowEvents----------//
	WindowClose,
	WindowCreate,
	WindowResize,
	
};

enum EEventCategory
{
	None = 0,
	EventCategoryWindow = BIT(0),
	EventCategoryKeyboard = BIT(1),
	EventCategoryMouse = BIT(2)
};


enum class EShaderType : uint8
{
	VertexShader = 0,
	FragmentShader = 1,
	None

};