#include "AssetSystem.h"

#include "fbxsdk/fileio/fbximporter.h"
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
	

	

		LoadAssets(DefaultAssetPath);
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
	//	std::filesystem::path TestModel = "../Content/Models/Test.fbx";
		
		const std::string Name = "Default";

		//const char* file = path.c_str();
		/*Add a default cube */
		AssetNameToID[Name] = 0;
		AssetMap[0] = std::make_shared<FModel>();
		AssetNameToFullPath[Name] = Name;


		/*FbxManager* FbxManagerInstance = FbxManager::Create();

		if (!FbxManagerInstance)
		{
			Logger::Error("FBX importer crash! this should not happen, contact dev!");
			return;
		}
		FbxIOSettings* IOSettings{ FbxIOSettings::Create(FbxManagerInstance, IOSROOT) };

		assert(IOSettings);
		FbxManagerInstance->SetIOSettings(IOSettings);
		FbxScene* FbxSceneInstance = FbxScene::Create(FbxManagerInstance, " Scene importer");
		if (!FbxSceneInstance)
		{
			Logger::Error("FBX importer crash! this should not happen, contact dev!");
			return;
		}*/

		////FbxImporter* Importer{FbxImporter::Create(FbxManagerInstance, "Importer")};
		//if(!(Importer && Importer->Initialize(file, -1, FbxManagerInstance->GetIOSettings()) && Importer->Import(FbxSceneInstance)))
		//{
		//	Logger::Warning("Check file name!");
		//	return;
		//}

		//Importer->Destroy();
		//float SceneScale = FbxSceneInstance->GetGlobalSettings().GetSystemUnit().GetConversionFactorTo(FbxSystemUnit::m);


		//FbxNode* Node;
	}

	void FAssetManager::GetMeshData(FbxNode* node)
	{
		//if(FbxMesh* fbx_mesh{node->GetMesh()})
		//{
		//	if (fbx_mesh->RemoveBadPolygons() < 0)
		//	{
		//		Logger::Warning("Bad polygon in mesh");
		//		return;
		//	}
		//	FbxGeometryConverter geometry_converter{ FbxManagerInstance };
		//	fbx_mesh = static_cast<FbxMesh*>(geometry_converter.Triangulate(fbx_mesh, true));

		//	if(!fbx_mesh || fbx_mesh->RemoveBadPolygons() < 0 )
		//	{
		//		return;
		//	}
		//	/*FModel Model;
		//	Model.FName = fbx_mesh->GetName();


		//	const int num_polys{fbx_mesh->GetPolygonCount()};

		//	if(num_polys <= 0 )
		//	{
		//		Logger::Warning("Polygon count = %d", num_polys);
		//		return;
		//	}

		//	const int  num_vertices{ fbx_mesh->GetControlPointsCount() };
		//	FbxVector4* vertices{ fbx_mesh->GetControlPoints() };
		//	const int num_indices{ fbx_mesh->GetPolygonVertexCount() };

		//	int* indices{ fbx_mesh->GetPolygonVertices() };

		//	Model.IndexPositions.reserve(num_indices);
		//	Model.VertexPosition.reserve(num_vertices);
		//	for(int i{0}; i < num_indices ; i ++ )*/
		//	{
		//	/*	const int vertex_index{indices[i]};

		//		if(vertex_position[vertex_index])
		//		{
		//			
		//		}*/

		//	}

		//}
	}

	void FAssetManager::ReadScene(FbxScene* Scene, FbxNode* Root)
	{
		if(!Root)
		{
			Root = Scene->GetRootNode();
			if(!Root)
			{
				return;
			}
		}

		const int number_of_nodes {Root->GetChildCount()};

		for(int i = 0; i < number_of_nodes; i ++)
		{
			FbxNode* node{Root->GetChild(i)};


			if(!node)
			{
				continue;
			}
			if(node->GetMesh())
			{
				GetMeshData(node);
			}
			else if(node->GetLodGroup())
			{
				//lod_group lod{};
				//GetMeshLODData(node, );
			}
			else
			{
				ReadScene(Scene);
			}
		}

	}

	
}
