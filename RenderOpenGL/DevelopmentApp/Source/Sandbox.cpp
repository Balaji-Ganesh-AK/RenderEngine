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
		auto* level = new LevelOne("Wew");
		auto* levelone = new LevelTwo("LevelOne");

		SetActiveLevel(levelone);
	}


	LevelOne::LevelOne(const std::string& Name): FLevel(Name)
	{
	}

	void LevelOne::Init()
	{
		


		entity = new FEntity(EntityManager::CreateEntity(), "Rifle");
		entity->AddComponent(FTransformComponent{});
		entity->AddComponent(FStaticMesh{ "Rifle" });
		entity->AddComponent(DefaultLitMaterialComponent{});
		const auto entity_one = new FEntity(EntityManager::CreateEntity(), "Rifle-1");
		entity_one->AddComponent(FTransformComponent{});
		entity_one->AddComponent(FStaticMesh{ "Knife" });
		entity_one->AddComponent(DefaultLitMaterialComponent{});


		entity = new FEntity(EntityManager::CreateEntity(), "Rifle-2");
		entity->AddComponent(FTransformComponent{});
		entity->AddComponent(FStaticMesh{ "Rifle" });
		entity->AddComponent(DefaultLitMaterialComponent{});

		entity1 = new FEntity(EntityManager::CreateEntity(), "SkySphere");
		entity1->AddComponent(FTransformComponent{});
		entity1->AddComponent(FStaticMesh{ "Rifle" });
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
		CameraEntity->AddComponent(FCamera{ true });
	}

	void LevelOne::Run() 
	{
		
	}

	void LevelOne::End()
	{
	}

	void LevelOne::GUIInit()
	{
	}

	void LevelOne::GUIRun()
	{
	}

	void LevelOne::GUIEnd()
	{
	}

	LevelTwo::LevelTwo(const std::string& Name): FLevel(Name)
	{

	
	}

	void LevelTwo::Init()
	{
		FLevel::Init();

		entity = new FEntity(EntityManager::CreateEntity(), "Knife");
		entity->AddComponent(FTransformComponent{});
		entity->AddComponent(FStaticMesh{ "Knife" });
		entity->AddComponent(FPointLight{});
		entity->AddComponent(DefaultLitMaterialComponent{});

		/*entity = new FEntity(EntityManager::CreateEntity(), "MushRoom");
		entity->AddComponent(FTransformComponent{});
		entity->AddComponent(FStaticMesh{ "Mushroom" });
		entity->AddComponent(FPointLight{});
		entity->AddComponent(DefaultLitMaterialComponent{});


		entity = new FEntity(EntityManager::CreateEntity(), "TwoMeshTest");
		entity->AddComponent(FTransformComponent{});
		entity->AddComponent(FStaticMesh{ "TwoMeshTest" });
		entity->AddComponent(FPointLight{});
		entity->AddComponent(DefaultLitMaterialComponent{});

		entity = new FEntity(EntityManager::CreateEntity(), "backpack");
		entity->AddComponent(FTransformComponent{});
		entity->AddComponent(FStaticMesh{ "backpack" });
		entity->AddComponent(FPointLight{});
		entity->AddComponent(DefaultLitMaterialComponent{});

		entity = new FEntity(EntityManager::CreateEntity(), "Gorilla");
		entity->AddComponent(FTransformComponent{});
		entity->AddComponent(FStaticMesh{ "Gorilla" });
		entity->AddComponent(FPointLight{});
		entity->AddComponent(DefaultLitMaterialComponent{});*/

		CameraEntity = new FEntity(EntityManager::CreateEntity(), "Camera");
		CameraEntity->AddComponent(FCamera{ true });
	}

	void LevelTwo::Run()
	{
		FLevel::Run();
	}

	void LevelTwo::End()
	{
		FLevel::End();
	}

	void LevelTwo::GUIInit()
	{
		FLevel::GUIInit();
	}

	void LevelTwo::GUIRun()
	{
		FLevel::GUIRun();
	}

	void LevelTwo::GUIEnd()
	{
		FLevel::GUIEnd();
	}


	KREngine::FApplication* KREngine::CreateApplication()
	{
		return new TestGame();
	}

}
