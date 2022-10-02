#pragma once
#include "Entity/Entity.h"



namespace KREngine
{

	struct FRigidBody
	{
	
		FVector Gravity{ 0,-0.1f, 0 };
		FVector Acceleration{ 0,0,0 };
		FVector Velocity{ 0,0,0 };

		FVector Force{0.0f,0,0};
		float Mass = 100.0f;
		FVector Drag{0,0,0};
		float KD =10.0f;
		
	};

	class FRigidBodySystem: public FSystem
	{
	public:
		~FRigidBodySystem() override;
		void Init() override;
		void Run() override;
		void End() override;
		void GUIInit() override;
		void GUIRun() override;
		void GUIEnd() override;

	private:
		void TempBlock( FVector& pos, FVector& vel);
	};
}
