#include "Sandbox.h"
#include "Entity/Entity.h"
#include "Entity/Components/TransformComponent.h"
#include "RenderingSystem/FRenderingSystem.h"
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
		entity->AddComponent(FRenderingComponent{});


		entity1 = new FEntity(EntityManager::CreateEntity(), "Static-Mesh-2");
		entity1->AddComponent(FTransformComponent{});
		entity1->AddComponent(FStaticMesh{});
		entity1->AddComponent(FRenderingComponent{});

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
