#include "Sandbox.h"



#include "Entity/Entity.h"
#include "Entity/Components/TransformComponent.h"
#include "Level/Levels.h"
#include "Material/DefaultMateirals.h"
#include "Material/DefaultUnlitMaterial.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"
#include "Runtime/Camera/FCameraComponent.h"



namespace KREngine
{
	KREngine::TestGame::TestGame()
	{
		auto* level = new LevelOne("Wew");
		auto* levelone = new LevelTwo("LevelOne");
		auto* instance = new InstanceStaticMeshTestMap("InstanceStaticMeshTestMap");
		SetActiveLevel(levelone);
	}



	KREngine::FApplication* KREngine::CreateApplication()
	{
		return new TestGame();
	}

}
