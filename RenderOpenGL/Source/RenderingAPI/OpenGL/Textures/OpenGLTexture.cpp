#include "OpenGLTexture.h"
#include "utility/GLFWIncludes.h"
#include "ThirdParty/stb_image.h"
#include "utility/KRELogger.h"

namespace KREngine
{
	OpenGLTexture2D::OpenGLTexture2D(const std::filesystem::path& texturePath)
	{
		TexturePath = texturePath.generic_string();
		DisplayName = texturePath.filename().string();
		OpenGLTexture2D::LoadTextures();
		OpenGLTexture2D::BindTexture();
	}

	void OpenGLTexture2D::BindTexture() 
	{
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, RendererID );


		//glActiveTexture( GL_TEXTURE0 +slot );
		//glBindTexture( GL_TEXTURE_2D, RendererID );
	}

	void OpenGLTexture2D::BindTexture(int slot) const
	{
		glActiveTexture( GL_TEXTURE0 +  slot );
		glBindTexture( GL_TEXTURE_2D, RendererID );
	}

	void OpenGLTexture2D::UnBindTexture()
	{
		//glBindTexture( GL_TEXTURE_2D, 0);

	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures( 1, &RendererID );
	}

	void OpenGLTexture2D::LoadTextures()
	{
		stbi_set_flip_vertically_on_load( true );
		stbi_uc* textureData = stbi_load(TexturePath.c_str(), &Width, &Height, &Channels, 4);
		
		glGenTextures( 1,&RendererID );
		glBindTexture( GL_TEXTURE_2D, RendererID );

	
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

		if(textureData )
		{	
			glTexImage2D( GL_TEXTURE_2D, MipLevel, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData );
			glGenerateMipmap( GL_TEXTURE_2D );
			stbi_image_free( textureData );
		}
		else
		{
			KRELogger::Error( "Failed to load the texture." );
		}

		
	}
}
