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