#include "Boids.h"

#include "GameManager.h"
#include "Entity/Components/EditorTagComponent.h"
#include "Entity/Components/TransformComponent.h"
#include "RenderOpenGL/Dependencies/ImGUI/imgui.h"

using namespace KREngine;

void FBoidSystem::Init()
{
	FSystem::Init();
	Logger::Warning("Boids system started");
}

void FBoidSystem::Run()
{
	FSystem::Run();
	for (auto& boid : EntityHandles)
	{
		FBoidComponent& boid_component = EntityManager::GetComponent<FBoidComponent>(boid);
		FTransformComponent& transform_component = EntityManager::GetComponent<FTransformComponent>(boid);

		const FVector new_pos = transform_component.Transform.GetLocation() + boid_component.velocity * speed;
		transform_component.Transform.SetLocation(new_pos);
		boid_component.velocity += boid_component.acceleration;
		const FVector align = Align(boid);
		boid_component.acceleration.Add(align);

	}
}

void FBoidSystem::End()
{
	FSystem::End();
	Logger::Warning("Boids system Ending");
}

FBoidSystem::~FBoidSystem()
{
}

void FBoidSystem::GUIInit()
{
	FSystem::GUIInit();
}

void FBoidSystem::GUIRun()
{
	FSystem::GUIRun();

	if(EntityHandles.size() > 0)
	{
		ImGui::Begin("Boid system");
		SCOPED_TIMER("Boid Controls ");
		if ((ImGui::CollapsingHeader("Boid Name")))
		{
			for (FEntityHandle entity : EntityHandles)
			{
				auto& fName = EntityManager::GetComponent<FName>(entity);
				FBoidComponent& boid_component = EntityManager::GetComponent<FBoidComponent>(entity);
				
				ImGui::BulletText("%s", fName.Name.c_str());
			}
		}

		if ((ImGui::CollapsingHeader("Boid Settings")))
		{
			FBoidComponent& boid_component = EntityManager::GetComponent<FBoidComponent>(0);
			IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Accleration", &boid_component.acceleration.x, 0.0001f, -1.00000, 1.00000, "%.5f"), "Accleration", );
			IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Velocity ", &boid_component.velocity.x, 0.0001f, -1.00000, 1.00000, "%.5f"), "velocity", );
			IMGUI_LEFT_LABEL(ImGui::DragFloat("##Speed ", &speed, 1.0f), "Speed");
			IMGUI_LEFT_LABEL(ImGui::DragFloat("##Preception ", &Preception, 1.0f), "Preception");

			
		}
		ImGui::End();
	}
}

void FBoidSystem::GUIEnd()
{
}

#pragma optimize("", off)
FVector FBoidSystem::Align(FEntityHandle i_boid)
{
	FVector sterring;
	int total{0};
	auto& parentBoidTransform = EntityManager::GetComponent<FTransformComponent>(i_boid).Transform;
	auto& parentBoid = EntityManager::GetComponent<FBoidComponent>(i_boid);
	for(auto& boid: EntityHandles)
	{
		auto& currentBoidTransform = EntityManager::GetComponent<FTransformComponent>(i_boid).Transform;
		auto& currentBoid = EntityManager::GetComponent<FBoidComponent>(i_boid);
		const auto distance = parentBoidTransform.GetLocation().DistanceSqrt(currentBoidTransform.GetLocation());

		if(boid!= i_boid && distance < sqrt(Preception) )
		{
			sterring.Add(currentBoid.velocity);
			total++;
		}

		
	}
	if(total > 0)
	{
		sterring.Divide(static_cast<float>(total));
		sterring.Subtract(parentBoid.velocity);
		/*long double z =(long double(sterring.z) - long double(parentBoid.velocity.z));
		sterring.z = z;*/
	}
	return sterring;
	
}

#pragma optimize("", on)