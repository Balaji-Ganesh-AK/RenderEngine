#include "StaticMesh.h"

#include "Material/DefaultMateirals.h"
#include "Material/DefaultUnlitMaterial.h"
#include "RenderingSystem/Buffers.h"
namespace KREngine
{

	void FStaticMeshSystem::Init()
	{


		/*TODO: extract this function to read the file and return the layout used fo this mesh*/
		VertexBufferLayout layout{
						BufferElement{"v_Pos", EShaderDataType::FVec3, true},
						BufferElement{"v_Texture", EShaderDataType::FVec2, true},
						BufferElement{"v_Normal", EShaderDataType::FVec3, true},
						//BufferElement{"v_Normal", EShaderDataType::FVec3, true},
		};

		/*TODO fetch all the entities with static mesh component
		 * TODO: Should work for runtime after setting up event system.
		 */
		for (const FEntityHandle& entity: EntityHandles)
		{
			auto& static_mesh = EntityManager::GetComponent<FStaticMesh>(entity);
		
			static_mesh.VertexArray = FVertexArray::Create();
			//static_mesh.VertexBufferData.reset(FVertexBuffer::CreateVertexBuffer(static_mesh.Positions, sizeof(static_mesh.Positions) / sizeof(float)));
			//static_mesh.IndexBufferData.reset(FIndexBuffer::CreateIndexBuffer(static_mesh.Indices, sizeof(static_mesh.Indices) / sizeof(unsigned int)));
			static_mesh.VertexBufferData = FVertexBuffer::CreateVertexBuffer(static_mesh.Positions, sizeof(static_mesh.Positions) / sizeof(float));
			static_mesh.IndexBufferData = FIndexBuffer::CreateIndexBuffer(static_mesh.Indices, sizeof(static_mesh.Indices) / sizeof(unsigned int));

			static_mesh.VertexArray->SetLayOut(layout);
			static_mesh.VertexArray->BindBufferLayout();
		}
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
