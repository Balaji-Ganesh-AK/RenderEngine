#pragma once
#include "RenderingSystem/Textures.h"


namespace KREngine
{
	class OpenGLTexture2D: public FTexture2D
	{
	public:
		OpenGLTexture2D(const std::filesystem::path& texturePath);
		virtual void BindTexture() override;
		virtual void BindTexture( int slot) const override;
		virtual void UnBindTexture() override;
		~OpenGLTexture2D() override;
	protected:
		void LoadTextures() override;
	private:
		
	};

}
