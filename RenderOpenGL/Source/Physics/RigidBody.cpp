#include "Rigidbody.h"
#include "Entity/Components/TransformComponent.h"
#include "ImGUI/imgui.h"
#include "RenderOpenGL/Utility/Source/Time.h"


namespace KREngine
{

	FRigidBodySystem::~FRigidBodySystem()
	{
	}

	void FRigidBodySystem::Init()
	{
		FSystem::Init();
		for (auto& entity : EntityHandles)
		{
			auto& transform = EntityManager::GetComponent<FTransformComponent>(entity).Transform;
			auto& rigidBody = EntityManager::GetComponent<FRigidBody>(entity);
			rigidBody.Force = rigidBody.Gravity * rigidBody.Mass;
			const auto force = rigidBody.Force / rigidBody.Mass;
			rigidBody.Acceleration.Add(force);
		}
	}

	void FRigidBodySystem::Run()
	{
		FSystem::Run();
		for(auto& entity : EntityHandles)
		{
			auto& transform = EntityManager::GetComponent<FTransformComponent>(entity).Transform;
			auto& rigidBody = EntityManager::GetComponent<FRigidBody>(entity);
			rigidBody.Velocity.Add(rigidBody.Acceleration );
			//rigidBody.Velocity.SetMagnitude(0.1f);
			transform.SetLocation(transform.GetLocation().Add(rigidBody.Velocity * Time::GetDeltaTime()));
			TempBlock(transform.GetLocation(), rigidBody.Velocity);

			//const auto& gravity = rigidBody.Gravity;
			//const auto& currentVelo = rigidBody.Velocity;
			//const auto drag = currentVelo * -(rigidBody.KD);
		
			//const auto total_force = rigidBody.Force + drag;
			//auto accleration = total_force / rigidBody.Mass;
			////accleration.Add(gravity);

			//rigidBody.Acceleration = accleration;
			//const auto next_velocity = currentVelo + (rigidBody.Acceleration * Time::GetDeltaTime());
			//const auto avg_velocity = (currentVelo + next_velocity) / 2;
			//rigidBody.Drag = drag;

			////rigidBody.Velocity.Add(rigidBody.Acceleration);

			//const FVector new_pos = transform.GetLocation() + avg_velocity * Time::GetDeltaTime() ;
			//transform.SetLocation(new_pos);
			//rigidBody.Velocity = next_velocity;

			//if(total_force.Magnitude() > 0.0001f)
			//{
			//	rigidBody.Force.Add(total_force);
			//}
			//else
			//{
			//	rigidBody.Force.Add(FVector::Zero());
			//}
			//rigidBody.Acceleration = FVector::Zero();





		}
	}

	void FRigidBodySystem::End()
	{
		FSystem::End();
	}

	void FRigidBodySystem::GUIInit()
	{
		FSystem::GUIInit();
	}

	void FRigidBodySystem::GUIRun()
	{
		FSystem::GUIRun();

		
	}

	void FRigidBodySystem::GUIEnd()
	{
		FSystem::GUIEnd();
	}

	void FRigidBodySystem::TempBlock(FVector& pos, FVector& vel)
	{
	
			/*if (pos.y  >= 100.0 )
			{
				pos.y = 100;
					vel.y = -1 * vel.y;

			}
			else */if (pos.y < 0.0)
			{
				pos.y = 0.0;
				vel.y = -1 * vel.y;

			}
	}
}
