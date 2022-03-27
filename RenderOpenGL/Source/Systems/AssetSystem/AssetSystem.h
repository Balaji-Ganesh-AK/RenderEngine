#pragma once
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <fbxsdk.h>

#include "fbxsdk/scene/geometry/fbxnode.h"

#include "Math/Vec3.h"
#include "utility/Defines.h"



namespace KREngine
{
	struct FStaticMesh;
	struct FModel
	{
		uint32 Indices[3 * 4 * 3] = {
			/**Front*/		0,1,2,
			/**Front*/		2,3,0,

			/**Back*/		4,5,6,
			/**Back*/		6,7,4,

			/**SideRight*/		8,9,10,
			/**SideRight*/		10,11,8,

			/**SideLeft*/		12,13,14,
			/**SideLeft*/		14,15,12,

			/**UP*/				16,17,18,
			/**UP*/				18,19,16,

			/**DOWN*/			20,21,22,
			/**DOWN*/			22,23,20
		};

		//std::vector<uint32> IndexPositions{
		//	/**Front*/		0,1,2,
		//	/**Front*/		2,3,0,

		//	/**Back*/		4,5,6,
		//	/**Back*/		6,7,4,

		//	/**SideRight*/		8,9,10,
		//	/**SideRight*/		10,11,8,

		//	/**SideLeft*/		12,13,14,
		//	/**SideLeft*/		14,15,12,

		//	/**UP*/				16,17,18,
		//	/**UP*/				18,19,16,

		//	/**DOWN*/			20,21,22,
		//	/**DOWN*/			22,23,20

		//};

		std::vector<FVector> VertexPosition =
		{
			{0.0f,0.0f,0.0f},
			{1.0f,0.0f,0.0f},
			{1.0f,1.0f,0.0f},
			{0.0f,1.0f,0.0f},

			{0.0f,0.0f,1.0f},
			{1.0f,0.0f,1.0f},
			{1.0f,1.0f,1.0f},
			{0.0f,1.0f,1.0f},

			{0.0f,0.0f,1.0f},
			{0.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,1.0f,1.0f},

			{1.0f,0.0f,0.0f},
			{1.0f,0.0f,1.0f},
			{1.0f,1.0f,1.0f},
			{1.0f,1.0f,0.0f},

			{0.0f,1.0f,0.0f},
			{1.0f,1.0f,0.0f},
			{1.0f,1.0f,1.0f},
			{0.0f,1.0f,1.0f},

			{0.0f,0.0f,1.0f},
			{1.0f,0.0f,1.0f},
			{1.0f,0.0f,0.0f},
			{0.0f,0.0f,0.0f},
		};


		std::vector<FVector> Normal =
		{
			{0.0f,0.0f,-1.0f},
			{0.0f,0.0f,-1.0f},
			{0.0f,0.0f,-1.0f},
			{0.0f,0.0f,-1.0f},

			{0.0f,0.0f,1.0f},
			{0.0f,0.0f,1.0f},
			{0.0f,0.0f,1.0f},
			{0.0f,0.0f,1.0f},

			{-1.0f,0.0f,0.0f},
			{-1.0f,0.0f,0.0f},
			{-1.0f,0.0f,0.0f},
			{-1.0f,0.0f,0.0f},

			{1.0f,0.0f,0.0f},
			{1.0f,0.0f,0.0f},
			{1.0f,0.0f,0.0f},
			{1.0f,0.0f,0.0f},

			{ 0.0f,1.0f,0.0f},
			{ 0.0f,1.0f,0.0f},
			{ 0.0f,1.0f,0.0f},
			{ 0.0f,1.0f,0.0f},

			{ 0.0f,-1.0f,0.0f},
			{ 0.0f,-1.0f,0.0f},
			{ 0.0f,-1.0f,0.0f},
			{ 0.0f,-1.0f,0.0f},
		};

		std::vector<Vec2> TexCord =
		{
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},

			{1.0f, 0.0f},
			{0.0f, 0.0f},
			{0.0f, 1.0f},
			{1.0f, 1.0f},

			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},

			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},

			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},

			{ 0.0f, 0.0f},
			{ 1.0f, 0.0f},
			{ 1.0f, 1.0f},
			{ 0.0f, 1.0f},
		};

		std::string FName; 
	};
	class FAssetManager
	{
	public:
		static FAssetManager* Create();

		void Init();

		std::shared_ptr<FModel> GetModel(const std::string& name);

	private:


		FAssetManager();
		void LoadAssets(const std::string path);
		void GetMeshData(FbxNode* node);
		void ReadScene(FbxScene* Scene, FbxNode* Root=nullptr );

		std::unordered_map<std::string, uint32> AssetNameToID;

		std::unordered_map<uint32, std::shared_ptr<FModel>> AssetMap;

		std::unordered_map < std::string, std::filesystem::path> AssetNameToFullPath;

		std::vector<std::string>AllowedExtenstion{ ".obj", ".fbx" };



	//	FbxManager* FbxManagerInstance;
	};
}
