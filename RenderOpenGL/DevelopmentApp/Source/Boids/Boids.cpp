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

	

		const FVector align = Align(boid);
		const FVector cohesion = Cohesion(boid);
		const FVector sep = Separation(boid);
		//boid_component.acceleration.Add(align);
		//boid_component.acceleration.Add(cohesion);
		boid_component.acceleration.Add(sep);
		boid_component.velocity.Add(boid_component.acceleration);
		float acc_mag = boid_component.velocity.Magnitude();
		float new_acc_mag = std::clamp(acc_mag,-0.01f, 0.01f);
		boid_component.velocity.SetMagnitude(new_acc_mag);
	

		FVector new_pos = transform_component.Transform.GetLocation() + boid_component.velocity * speed;

		EdgeLimit(new_pos);
		transform_component.Transform.SetLocation(new_pos);
		boid_component.acceleration = FVector::Zero();

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
#ifdef GUI
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
			IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Max Limit ", &Max.x), "Max Limit", );
			IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Min Limit ", &Min.x), "Min Limit", );
			IMGUI_LEFT_LABEL(ImGui::DragFloat("##Speed ", &speed, 1.0f), "Speed");
			IMGUI_LEFT_LABEL(ImGui::DragFloat("##Preception ", &Preception, 1.0f), "Preception");

			
		}
		ImGui::End();
	}
}

void FBoidSystem::GUIEnd()
{
}
#endif

#pragma optimize("", off)
FVector FBoidSystem::Align(FEntityHandle i_boid)
{
	FVector sterring {FVector::Zero()};
	int total{0};
	auto& parentBoidTransform = EntityManager::GetComponent<FTransformComponent>(i_boid).Transform;
	auto& parentBoid = EntityManager::GetComponent<FBoidComponent>(i_boid);
	for(auto& boid: EntityHandles)
	{
		auto& currentBoidTransform = EntityManager::GetComponent<FTransformComponent>(boid).Transform;
		auto& currentBoid = EntityManager::GetComponent<FBoidComponent>(boid);
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
		
	}
	return sterring;
	
}

FVector FBoidSystem::Cohesion(FEntityHandle i_boid)
{
	FVector sterring{ FVector::Zero() };
	int total{ 0 };
	auto& boid_transform = EntityManager::GetComponent<FTransformComponent>(i_boid).Transform;
	auto& parentBoid = EntityManager::GetComponent<FBoidComponent>(i_boid);
	for (auto& boid : EntityHandles)
	{
		auto& currentBoidTransform = EntityManager::GetComponent<FTransformComponent>(boid).Transform;
		auto& currentBoid = EntityManager::GetComponent<FBoidComponent>(boid);
		const auto distance = boid_transform.GetLocation().DistanceSqrt(currentBoidTransform.GetLocation());

		if (boid != i_boid && distance < sqrt(Preception_Cohesion))
		{
			sterring.Add(currentBoidTransform.GetLocation());
			total++;
		}


	}
	if (total > 0)
	{
		sterring.Divide(static_cast<float>(total));
		sterring.Subtract(boid_transform.GetLocation());

	}
	return sterring;
}

FVector FBoidSystem::Separation(FEntityHandle i_boid)
{
	FVector sterring{ FVector::Zero() };
	int total{ 0 };
	auto& boid_transform = EntityManager::GetComponent<FTransformComponent>(i_boid).Transform;
	auto& parentBoid = EntityManager::GetComponent<FBoidComponent>(i_boid);
	for (auto& boid : EntityHandles)
	{
		auto& currentBoidTransform = EntityManager::GetComponent<FTransformComponent>(boid).Transform;
		auto& currentBoid = EntityManager::GetComponent<FBoidComponent>(boid);
		const auto distance = boid_transform.GetLocation().Distance(currentBoidTransform.GetLocation());

		if (boid != i_boid && distance < (Preception_Sep))
		{
			auto diff = currentBoidTransform.GetLocation(); ;
			diff.Subtract(boid_transform.GetLocation());
			diff.Divide(distance);
			sterring.Add(diff);
			total++;
		}


	}
	if (total > 0)
	{
		sterring.Divide(static_cast<float>(total));
		sterring.Subtract(parentBoid.velocity);

	}
	return sterring;
}

void FBoidSystem::EdgeLimit(FVector& pos)
{

	if(pos.x > Max.x)
	{
		pos.x = Min.x;
	}
	else if (pos.x < Min.x)
	{
		pos.x = Max.x;
	}

	if (pos.y > Max.y)
	{
		pos.y = Min.y;
	}
	else if (pos.y < Min.y)
	{
		pos.y = Max.y;
	}


	if (pos.z > Max.z)
	{
		pos.z = Min.z;
	}
	else if (pos.z < Min.z)
	{
		pos.z = Max.z;
	}
}

#pragma optimize("", on)
