#pragma once
#include <cstdint>
#include <iostream>

typedef uint8_t uint8;
typedef int8_t int8;
typedef int32_t int32;
typedef uint32_t uint32;

#define ENGINE_NAME "KREngine";



#define DASSERT(x) if(!(x)) __debugbreak();

#define GLLOGERROR(x) GLClearError();\
	x;\
	DASSERT(GLLogError(#x, __FILE__, __LINE__));

static bool GLLogError( const char* functionName, const char* file, int line )
{
	while ( GLenum error = glGetError() )
	{
		std::cout << " Open GL error " << error << "Function name: " << functionName << "File :" << file << "Line :" << line << std::endl;
		return false;
	}
	return true;
}