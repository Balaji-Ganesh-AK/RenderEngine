#include"TextureManager.h"

#include "RenderingSystem/Textures.h"
#include "utility/CommonInclude.h"
#include "utility/LogTimer.h"
#include "utility/File/Logger.h"

namespace KREngine
{
	FTextureManager* FTextureManager::Create()
	{
		return new FTextureManager();
	}

	void FTextureManager::Init()
	{

		{
			FScopedTimer Texture{ "Loading texture" };
			for (const std::filesystem::directory_entry& texture_path : std::filesystem::recursive_directory_iterator(DefaultTexturePath))
			{
				for (const std::string& it : AllowedExtenstion)
				{
					if (texture_path.path().extension().compare(it))
					{
						Logger::Verbose("..... Loading texture from file ....%s", texture_path.path().generic_string().c_str());
						FTexture2D* texture_id = FTexture2D::Create(texture_path.path().generic_string());
						TextureNameToID[texture_path.path().filename().string()] = texture_id->RendererID;
						TextureMap[texture_id->RendererID].reset(texture_id);
						TextureNameToFullPath[texture_path.path().filename().string()] = texture_path.path();
					}

				}
			}

		}
	}

	void FTextureManager::BindTexture(uint32 textureID)
	{
		if(TextureMap.contains(textureID))
		{
			TextureMap[textureID]->BindTexture();
		}
		
	}

	FTextureManager::FTextureManager()
	{
	}

	void FTextureManager::LoadTexture(const std::string path)
	{
	}
}
