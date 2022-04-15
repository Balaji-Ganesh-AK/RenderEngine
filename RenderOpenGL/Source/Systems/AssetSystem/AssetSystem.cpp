#include "AssetSystem.h"

#include "RenderOpenGL/Utility/Source/File/FileHelper.h"
#include "RenderOpenGL/Utility/Source/File/FJson.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"
#include "utility/File/Logger.h"




namespace KREngine
{

	FAssetManager* FAssetManager::Create()
	{
		return new FAssetManager();
	} 

	void FAssetManager::Init()
	{
		std::string Path = DefaultContentPath;
		LoadAssets(Path);
	}

	std::shared_ptr<FModel> FAssetManager::GetModel(const std::string& name)
	{
		return AssetMap[AssetNameToID[name]];
	
	}

	FAssetManager::FAssetManager()
	{
	}

	void FAssetManager::LoadAssets(const std::string path)
	{
		AssetNameToID["Default"] = AssetCount;
		AssetMap[AssetCount] = std::make_shared<FModel>();
		AssetNameToFullPath["Default"] = "Default";
		AssetCount++;

		for (const std::filesystem::directory_entry& asset_path : std::filesystem::recursive_directory_iterator(path))
		{
			for (const std::string& it : AllowedExtenstion)
			{
				if (asset_path.path().extension().compare(it) == 0 )
				{
					/*TODO make is better*/
					Logger::Verbose("Reading %s", asset_path.path().generic_string().c_str());
					EFileExtension file_extension = StringToFileExtension(it);
					switch (file_extension)
					{
					case EFileExtension::StaticMesh:
						ReadStaticMesh(asset_path.path().generic_string());
						break;
					case EFileExtension::UnKnown:
					default:
						Logger::Error("Error reading unknown file type");
						
					}
				}
			}
		}

	}

	void FAssetManager::ReadStaticMesh(const std::string path)
	{
		std::ifstream input(path, std::ios::binary);
		std::vector<uint8_t> static_mesh_data(std::istreambuf_iterator<char>(input), {});
		FJson json = FJson::from_cbor((static_mesh_data));
		
		std::string Name;
		FModel static_mesh_model;
		if (json.contains("Name"))
		{
			Name = json["Name"];
			Logger::Verbose("Reading static mesh from file : %s", Name.c_str());
		}
		else
		{
			Logger::Warning("The static mesh file has no name, file: %s", path.c_str());
		}
		if (json.contains("VertexPosition"))
		{
		/*	const std::string name = json["VertexPosition"];
			Logger::Verbose("Reading static mesh from file : %s", name.c_str());*/

			for(int i =0;i<json["VertexPosition"].size() ; i = i+ 3)
			{
				float x = json["VertexPosition"][i + 0];
				float y = json["VertexPosition"][i + 1 ];
				float z = json["VertexPosition"][i + 2];
				static_mesh_model.VertexPositionBuffer.emplace_back(x,y,z);
			}
			for (int i = 0; i < json["Normal"].size(); i = i + 3)
			{
				float x = json["Normal"][i + 0];
				float y = json["Normal"][i + 1];
				float z = json["Normal"][i + 2];
				static_mesh_model.NormalBuffer.emplace_back(x, y, z);
			}
			for (int i = 0; i < json["TexCord"].size(); i = i + 2)
			{
				float x = json["TexCord"][i + 0];
				float y = json["TexCord"][i + 1];
				static_mesh_model.TextureCordBuffer.emplace_back(x, y);
			}

			for (int i = 0; i < json["Indices"].size(); i++)
			{
				float x = json["Indices"][i];
				static_mesh_model.IndexPositions.emplace_back(x);
			}
		}
		else
		{
			Logger::Error("The static mesh file has no vertex position, file: %s", path.c_str());
		}



		AssetNameToID[Name] = AssetCount;
		AssetMap[AssetCount] = std::make_shared<FModel>(static_mesh_model);
		AssetNameToFullPath[Name] = path;
		AssetCount++;
	}
}
