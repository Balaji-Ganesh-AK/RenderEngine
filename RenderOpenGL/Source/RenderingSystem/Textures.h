#pragma once

#include <string>

#include "utility/Defines.h"


namespace KREngine
{
	class FTexture2D
	{
	public:
		virtual ~FTexture2D() = default;
		virtual void BindTexture() = 0;
		virtual void BindTexture( int slot) const = 0;
		virtual void UnBindTexture() = 0;

		static FTexture2D* Create(std::string& texturePath);
	protected:
		virtual void LoadTextures()=0;
		std::string TexturePath{ "Content/Textures/Checkerboard.png" };
		int Width{ 0 };
		int Height{ 0 };
		int Channels{ 0 };
		uint8 MipLevel{ 0 };
		uint32 RendererID{ 0 };

	private:
		
	};
}
