#pragma once
#include "RenderingSystem/Textures.h"
#include "utility/Pch.h"

namespace KREngine
{
	class OpenGLTexture2D: public FTexture2D
	{
	public:
		OpenGLTexture2D(std::string& TexturePath);
		virtual void BindTexture() override;
		virtual void UnBindTexture() override;
		~OpenGLTexture2D() override;
	protected:
		void LoadTextures() override;
	private:
		
	};

}
