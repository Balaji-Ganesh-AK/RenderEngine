#include "AssetSystem.h"

#include "fbxsdk/fileio/fbximporter.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"
#include "utility/File/Logger.h"

namespace KREngine
{

	const char* FbxNodeAttributeToString(FbxNodeAttribute::EType type) {
		switch (type) {
		case FbxNodeAttribute::eUnknown: return "unidentified";
		case FbxNodeAttribute::eNull: return "null";
		case FbxNodeAttribute::eMarker: return "marker";
		case FbxNodeAttribute::eSkeleton: return "skeleton";
		case FbxNodeAttribute::eMesh: return "Mesh";
		case FbxNodeAttribute::eNurbs: return "nurbs";
		case FbxNodeAttribute::ePatch: return "patch";
		case FbxNodeAttribute::eCamera: return "camera";
		case FbxNodeAttribute::eCameraStereo: return "stereo";
		case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
		case FbxNodeAttribute::eLight: return "light";
		case FbxNodeAttribute::eOpticalReference: return "optical reference";
		case FbxNodeAttribute::eOpticalMarker: return "marker";
		case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
		case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
		case FbxNodeAttribute::eBoundary: return "boundary";
		case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
		case FbxNodeAttribute::eShape: return "shape";
		case FbxNodeAttribute::eLODGroup: return "lodgroup";
		case FbxNodeAttribute::eSubDiv: return "subdiv";
		case FbxNodeAttribute::eCachedEffect: break;
		case FbxNodeAttribute::eLine: break;
		default: return "unknown";
		}
		return {};
	}
	FAssetManager* FAssetManager::Create()
	{
		return new FAssetManager();
	} 

	void FAssetManager::Init()
	{
	

		FbxManagerInstance = FbxManager::Create();

		if (!FbxManagerInstance)
		{
			Logger::Error("FBX importer crash! this should not happen, contact dev!");
			return;
		}
		FbxIOSettings* IOSettings{ FbxIOSettings::Create(FbxManagerInstance, IOSROOT) };

		assert(IOSettings);
		FbxManagerInstance->SetIOSettings(IOSettings);
		FbxSceneInstance = FbxScene::Create(FbxManagerInstance, " Scene importer");
		if (!FbxSceneInstance)
		{
			Logger::Error("FBX importer crash! this should not happen, contact dev!");
			return;
		}
		std::string Path = DefaultAssetPath "/"  "Test.fbx";
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
		std::filesystem::path TestModel = "../Content/Models/Test.fbx";
		
		const std::string Name = "Default";
		const std::string Test = TestModel.generic_string().c_str();
		const char* file = Test.c_str();
		/*Add a default cube */
		AssetNameToID[Name] = 0;
		AssetMap[0] = std::make_shared<FModel>();
		AssetNameToFullPath[Name] = Name;


		FbxImporter* Importer = FbxImporter::Create(FbxManagerInstance, "Importing assets");

		// Use the first argument as the filename for the importer.
		if (!Importer->Initialize(file, -1, FbxManagerInstance->GetIOSettings())) {
			Logger::Verbose("Call to FbxImporter::Initialize() failed.\n");
			Logger::Error("Error when importing assets: %s\n\n", Importer->GetStatus().GetErrorString());
			return;
		}
		
		ReadScene(Importer);

	}

	void FAssetManager::GetMeshData(FbxNode* node)
	{
		
	}
	void FAssetManager::ReadScene(FbxImporter* Importer)
	{
		
		Importer->Import(FbxSceneInstance);

		FbxNode* root = FbxSceneInstance->GetRootNode();

		if(root)
		{
			Logger::Loader("Reading from root %s \n", root->GetName());
			for (int i =0 ; i < root->GetChildCount(); i ++)
			{
				ReadNode(root->GetChild(i));
			}
		}
		else
		{
			Logger::Warning("No root Node found %s", Importer->GetScene()->GetName() );
		}
		
	}

	void FAssetManager::ReadNode(FbxNode* Node)
	{
		const char* nodeName = Node->GetName();
		FbxDouble3 translation = Node->LclTranslation.Get();
		FbxDouble3 rotation = Node->LclRotation.Get();
		FbxDouble3 scaling = Node->LclScaling.Get();

		if(Node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::EType::eMesh)
		{
			FbxMesh* mesh = static_cast<FbxMesh*>(Node->GetNodeAttribute());
			Logger::Verbose("Reading from mesh : %s \n", mesh->GetName());

			Logger::Verbose("Control points? ");
			FbxVector4* controlPoints = mesh->GetControlPoints();
			for (int i = 0; i < mesh->GetControlPointsCount(); i++)
			{
				Logger::Verbose(" Control points {%f, %f, %f}", controlPoints[i][0], controlPoints[i][1], controlPoints[i][2]);

				for (int j = 0; j < mesh->GetElementNormalCount(); j++)
				{
					FbxGeometryElementNormal* normals = mesh->GetElementNormal(j);
					if (normals->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
					{
						Logger::Verbose(" normal points {%f, %f, %f}", normals->GetDirectArray()[0], normals->GetDirectArray()[i][1], normals->GetDirectArray()[i][2]);
						//Logger::Verbose(" normal points {%f, %f, %f}", normals->GetDirectArray().GetAt(i)[0], normals->GetDirectArray().GetAt(i)[1], normals->GetDirectArray().GetAt(i)[2]);
					}
				}
				const int lPolySize = mesh->GetPolygonSize(i);
				int counter = 0;
				FbxStringList lUVSetNameList;
				mesh->GetUVSetNames(lUVSetNameList);
				const char* lUVSetName = lUVSetNameList.GetStringAt(counter);
				const FbxGeometryElementUV* lUVElement = mesh->GetElementUV(lUVSetName);
				if (lUVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
				{
					for (int x = 0; x < lPolySize; x++)
					{
						//if(counter < 0 )//"Index count here")
						//{
						//	
						//}

						FbxVector2 uv;
						//lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyIndexCounter) : lPolyIndexCounter;
						int uvindex = counter;

						uv = lUVElement->GetDirectArray().GetAt(uvindex);
						Logger::Verbose(" Tex corrd : %f, %f", uv[0], uv[1]);
						counter++;
					}
				}
				
			}
			
		}
		else
		{
			Logger::Warning("Scene contains un supported type %s", FbxNodeAttributeToString(Node->GetNodeAttribute()->GetAttributeType()));
		}
	}
}
