#include "StaticMesh.h"

#include "GameManager.h"
#include "Material/DefaultMateirals.h"
#include "Material/DefaultUnlitMaterial.h"
#include "RenderingSystem/Buffers.h"
#include "Systems/AssetSystem/AssetSystem.h"

namespace KREngine
{
	FStaticMesh::FStaticMesh()
	{
		Model = FApplication::GetAssetManager().GetModel("Default");
	}

	FStaticMesh::FStaticMesh(const std::string& Name)
	{
		Model = FApplication::GetAssetManager().GetModel(Name);
	}

	void FStaticMeshSystem::Init()
	{
	
		
	}

	void FStaticMeshSystem::Run()
	{
		
	}

	void FStaticMeshSystem::Stop()
	{
	}

	FStaticMeshSystem::~FStaticMeshSystem()
	{
	}
#ifdef  GUI
	void FStaticMeshSystem::GUIInit()
	{
		
	}

	void FStaticMeshSystem::GUIRun()
	{
		
	}

	void FStaticMeshSystem::GUIStop()
	{
	
	}

#endif

	void FStaticMeshSystem::LoadMesh()
	{
		/*Add logic here for reading */
	}

	void FStaticMeshSystem::SetUpMesh()
	{
		/*Load the vertex buffer here*/

		
	}
}
