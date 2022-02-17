#include "Textures.h"

#include "RenderingAPI/OpenGL/Textures/OpenGLTexture.h"


namespace KREngine
{
	FTexture2D* FTexture2D::Create(const std::string& texturePath)
	{
		return new OpenGLTexture2D( texturePath );
	}

	
}
