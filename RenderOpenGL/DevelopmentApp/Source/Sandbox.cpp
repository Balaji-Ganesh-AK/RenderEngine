#include "Sandbox.h"



#include "Entity/Entity.h"
#include "Entity/Components/TransformComponent.h"
#include "Material/DefaultMateirals.h"
#include "Material/DefaultUnlitMaterial.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"
#include "Runtime/Camera/FCamera.h"



namespace KREngine
{
	TestGame::TestGame()
	{
		
	}

	void TestGame::Init()
	{
		entity = new FEntity(EntityManager::CreateEntity(), "Static-Mesh-1");
		entity->AddComponent(FTransformComponent{});
		entity->AddComponent(FStaticMesh{});
		entity->AddComponent(FPointLight{});
		entity->AddComponent(DefaultLitMaterialComponent{});
		
		
		

		entity1 = new FEntity(EntityManager::CreateEntity(), "Static-Mesh-2");
		entity1->AddComponent(FTransformComponent{});
		entity1->AddComponent(FStaticMesh{ });
		entity1->AddComponent(DefaultLitMaterialComponent{});


		/*for(int i = 3; i < 100; i++)
		{
			std::string name = "Static-Mesh--" ;
			name += std::to_string(i);
			auto temp = new FEntity(EntityManager::CreateEntity(), name);
			FTransform Temp;
			float rangeX=rand() % 50 + 0;
			float rangeY=rand() % 50 + 0;
			float rangeZ=rand() % 50 + 0;

			Temp.SetLocation(FVector(rangeX, rangeY, rangeZ));
			temp->AddComponent(FTransformComponent{ Temp });
			temp->AddComponent(FStaticMesh{});
			temp->AddComponent(DefaultLitMaterialComponent{});
		}*/

		CameraEntity = new FEntity(EntityManager::CreateEntity(), "Camera");
		CameraEntity->AddComponent(FCamera{true});
	}

	void TestGame::Run()
	{
		
	}

	void TestGame::End()
	{
	}

	

	KREngine::FApplication* KREngine::CreateApplication()
	{
		return new TestGame();
	}

}
