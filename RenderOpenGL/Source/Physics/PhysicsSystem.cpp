

#include "PhysicsSystem.h"

#include "Rigidbody.h"
#include "Entity/Components/TransformComponent.h"


namespace KREngine
{
	FPhysicsSystem* FPhysicsSystem::Create()
	{
		return new FPhysicsSystem();
	}
	FPhysicsSystem::FPhysicsSystem()
	{
		

		auto system = EntityManager::RegisterSystem<FRigidBodySystem>();
		PhysicsSystems.push_back(system);
	}
	void FPhysicsSystem::Init()
	{
		

		for(auto& systems : PhysicsSystems)
		{
			systems->Init();
		}
	}

	void FPhysicsSystem::Run()
	{
		for (auto& systems : PhysicsSystems)
		{
			systems->Run();
		}
	}
	

	void FPhysicsSystem::End()
	{
		for (auto& systems : PhysicsSystems)
		{
			systems->End();
		}
	}

	void FPhysicsSystem::GUIInit()
	{
		for (auto& systems : PhysicsSystems)
		{
			systems->GUIInit();
		}
	}

	void FPhysicsSystem::GUIRun()
	{
		for (auto& systems : PhysicsSystems)
		{
			systems->GUIRun();
		}
	}

	void FPhysicsSystem::GUIEnd()
	{
		for (auto& systems : PhysicsSystems)
		{
			systems->GUIEnd();
		}
	}

	
}
