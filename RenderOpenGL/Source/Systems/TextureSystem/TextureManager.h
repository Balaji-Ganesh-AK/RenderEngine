#pragma once
#include "Runtime/Containers/TArray.h"
#include "utility/CommonInclude.h"
#include "utility/Defines.h"


namespace KREngine
{
	class FTexture2D;

	class FTextureManager
	{
	public:

		static FTextureManager* Create();

		/*Loads in all the textures*/
		/*TODO Currently only reads form the texture folder, future la it should read from everywhere*/
		void Init();

		// ReSharper disable once CppMemberFunctionMayBeConst
		uint32 GetTextureID(const std::string& textureName) 
		{
			return TextureNameToID[textureName];
		}
		std::shared_ptr<FTexture2D> GetTexture(const std::string& textureName)
		{
			return TextureMap[TextureNameToID[textureName]];
		}


		std::shared_ptr<FTexture2D> GetTexture(const std::filesystem::path& textureName)
		{
			for(auto& texture: TextureNameToFullPath)
			{
				if(texture.first == textureName)
				{
					return TextureMap[TextureNameToID[texture.first]];
				}
			}
			return nullptr;
		}
		std::shared_ptr<FTexture2D> GetTexture(uint32 textureID)
		{
			return TextureMap[textureID];
		}

		void BindTexture( uint32 textureID);

		uint32 TextureCount () const
		{
			return TextureMap.size();
		}

		bool HasTextureName(const std::string& textureName) const
		{
			return TextureNameToID.contains(textureName);
		}


		void GetTextureNames(std::vector<std::string>& outVector) const
		{
			outVector.reserve(TextureNameToID.size());
			for(const std::pair<const std::string, unsigned>& name : TextureNameToID)
			{
				outVector.push_back(name.first);
			}
		}

	private:
		FTextureManager();
		void LoadTexture(const std::string path);
		std::unordered_map<std::string, uint32> TextureNameToID;

		std::unordered_map<uint32, std::shared_ptr<FTexture2D>> TextureMap;

		std::unordered_map < std::string, std::filesystem::path> TextureNameToFullPath;

		std::vector<std::string>AllowedExtenstion{ ".png", "jpg"};

	};


}
