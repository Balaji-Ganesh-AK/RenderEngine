#pragma once
#include <cstdint>

typedef uint8_t uint8;
typedef int8_t int8;
typedef int32_t int32;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef int8_t int16;
typedef uint64_t uint64;
typedef int64_t int64;



#define ENGINE_NAME "KREngine"
#define FORCE_INLINE __forceinline

#define DASSERT(x) if(!(x)) __debugbreak();

#define BIT(x) (1<<x)



#define OBJ_Extension ".obj"
#define DefaultTexturePath "../Content/Textures"
#define DefaultAssetPath "../Content/Assets"
#define DefaultShaderFolderPath "../Content/Shaders"
#define DefaultCompliedShaderFolderPath "/Binaries/Shaders"

//#define GLLOGERROR(x) GLClearError();\
//	x;\
//	DASSERT(GLLogError(#x, __FILE__, __LINE__));
//
//static bool GLLogError( const char* functionName, const char* file, int line )
//{
//	while ( GLenum error = glGetError() )
//	{
//		std::cout << " Open GL error " << error << "Function name: " << functionName << "File :" << file << "Line :" << line << std::endl;
//		return false;
//	}
//	return true;
//}
