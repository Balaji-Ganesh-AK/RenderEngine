#pragma once
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <fbxsdk.h>

#include "fbxsdk/scene/geometry/fbxnode.h"

#include "Math/Vec3.h"




namespace KREngine
{


	


	struct FStaticMesh;
	struct FModel
	{
		uint32 Indices[3 * 4 * 3] = {

			/**Front*/		 0, 1, 3,
			/**Front*/		3, 1, 2,

			/**Back*/		 1, 5, 2,
			/**Back*/		2, 5, 6,

			/**SideRight*/		 5, 4, 6,
			/**SideRight*/		6, 4, 7,

			/**SideLeft*/		 4, 0, 7, 
			/**SideLeft*/		7, 0, 3,

			/**UP*/				  3, 2, 7,
			/**UP*/				 7, 2, 6,

			/**DOWN*/			 4, 5, 0,
			/**DOWN*/			 0, 5, 1
		};

		

		std::vector<uint32> TexIndices
		{
			0,1,2,

			3,1,2,
			 //0, 1, 2,
				//2, 3, 0,


		};

		std::vector<uint32> IndexPositions{

			/**Front*/		 0, 1, 2,
			/**Front*/		2, 3, 0,

			/**Back*/		 1, 5, 2,
			/**Back*/		2, 5, 6,

			/**SideRight*/		 5, 4, 6,
			/**SideRight*/		6, 4, 7,

			/**SideLeft*/		 4, 0, 7,
			/**SideLeft*/		7, 0, 3,

			/**UP*/				  3, 2, 7,
			/**UP*/				 7, 2, 6,

			/**DOWN*/			 4, 5, 0,
			/**DOWN*/			 0, 5, 1
		};

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

		/*	{-1, -1, -1},
			{1, -1, -1},
			{1, 1, -1},
			{-1, 1, -1},
			{-1, -1, 1},
			{1, -1, 1},
			{1, 1, 1},
			{-1, 1, 1}*/

			//{-1, -1, -1}, //0
			//{1, -1, -1}, //1
			//{1, 1, -1}, //2
			//{-1, 1, -1}, //3

			//{-1, -1, 1}, //4
			//{1, -1, 1}, //5 
			//{1, 1, 1}, //6
			//{-1, 1, 1}, //7

			//{0.0f,0.0f,1.0f}, 8 4
			//{0.0f,0.0f,0.0f}, 9 
			//{0.0f,1.0f,0.0f}, 10 3
			//{0.0f,1.0f,1.0f}, 11 7
			 
			//{1.0f,0.0f,0.0f}, 12 1
			//{1.0f,0.0f,1.0f}, 13 5
			//{1.0f,1.0f,1.0f}, 14  6
			//{1.0f,1.0f,0.0f}, 15 2

			//{0.0f,1.0f,0.0f}, 16 3
			//{1.0f,1.0f,0.0f}, 17 2
			//{1.0f,1.0f,1.0f}, 18 6
			//{0.0f,1.0f,1.0f}, 19 7

			//{0.0f,0.0f,1.0f}, 20	4
			//{1.0f,0.0f,1.0f},	21	5
			//{1.0f,0.0f,0.0f},	22	1
			//{0.0f,0.0f,0.0f},	23  0
		};
		std::vector<FVector> VertexPositionBuffer =
		{
		};
		std::vector<Vec2> TextureCordBuffer =
		{

		};
		std::vector<FVector> NormalBuffer =
		{

		};
		std::vector<FVector> Normal =
		{
			{0.0f,0.0f,1.0f},
			{0.0f,0.0f,1.0f},
			{0.0f,0.0f,1.0f},
			{0.0f,0.0f,1.0f},

			{0.0f,1.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,1.0f,0.0f},

	/*		{-1.0f,0.0f,0.0f},
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
			{ 0.0f,-1.0f,0.0f},*/
		};

		std::vector<Vec2> TexCord =
		{


			{0,0},
			{1,0},
			{1, 1},
			{0, 1},


		/*	{0.0f, 0.0f},
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
			{ 0.0f, 1.0f},*/
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
		void ReadScene(FbxImporter* Importer);

		void ReadNode(FbxNode* Node);

		std::unordered_map<std::string, uint32> AssetNameToID;

		std::unordered_map<uint32, std::shared_ptr<FModel>> AssetMap;

		std::unordered_map < std::string, std::filesystem::path> AssetNameToFullPath;

		std::vector<std::string>AllowedExtenstion{ ".obj", ".fbx" };

		double SceneScale;

		FbxManager* FbxManagerInstance;
		FbxScene* FbxSceneInstance;
	};

	
}
