#pragma once
#include <memory>

#include "Rigidbody.h"


namespace KREngine
{
	class FPhysicsSystem
	{
	public:

		static FPhysicsSystem* Create();

		void Init()		;
		void Run()		;
		void End()		;
		void GUIInit()	;
		void GUIRun()	;
		void GUIEnd()	;

	private:
		FPhysicsSystem();
		std::vector<std::shared_ptr<FSystem>> PhysicsSystems;

		std::shared_ptr<FRigidBodySystem> RigidBody;
	};
	
}
