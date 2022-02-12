#include "Sandbox.h"

#include "GameManager.h"
#include "Entity/Components/TransformComponent.h"
#include "RenderingSystem/FRenderingSystem.h"
#include "Systems/Input/Input.h"
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
	}

	void TestGame::Run()
	{
		if(FApplication::GetInputSystem().IsKeyPressed(Input::KeyCodes::A))
		{
			Logger::Verbose("Lol");
		}
	}

	void TestGame::End()
	{
	}

	

	KREngine::FApplication* KREngine::CreateApplication()
	{
		return new TestGame();
	}

}
