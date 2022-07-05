#include "Levels.h"

#include "Editor/Gizmo.h"
#include "Entity/Components/TransformComponent.h"
#include "Material/DefaultMateirals.h"
#include "Material/DefaultUnlitMaterial.h"
#include "RenderOpenGL/DevelopmentApp/Source/Sandbox.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"
#include "Runtime/Line/Line.h"
#include "Runtime/Line/Ray.h"
#include "RenderOpenGL/DevelopmentApp/Source/Boids/Boids.h"


using namespace KREngine;

LevelOne::LevelOne(const std::string& Name) : FLevel(Name)
{
}

void LevelOne::Init()
{



	//entity = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Rifle");
	//entity->AddComponent(KREngine::FTransformComponent{});
	//entity->AddComponent(KREngine::FStaticMesh{ "Rifle" });
	//entity->AddComponent(KREngine::DefaultLitMaterialComponent{});
	//const auto entity_one = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Rifle-1");
	//entity_one->AddComponent(KREngine::FTransformComponent{});
	//entity_one->AddComponent(KREngine::FStaticMesh{ "Knife" });
	//entity_one->AddComponent(KREngine::DefaultLitMaterialComponent{});


	//entity = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Rifle-2");
	//entity->AddComponent(KREngine::FTransformComponent{});
	//entity->AddComponent(KREngine::FStaticMesh{ "Rifle" });
	//entity->AddComponent(KREngine::DefaultLitMaterialComponent{});

	//entity1 = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "SkySphere");
	//entity1->AddComponent(KREngine::FTransformComponent{});
	//entity1->AddComponent(KREngine::FStaticMesh{ "Rifle" });
	//entity1->AddComponent(KREngine::DefaultLitMaterialComponent{});


	///*for(int i = 3; i < 100; i++)
	//{
	//	std::string name = "Static-Mesh--" ;
	//	name += std::to_string(i);
	//	auto temp = new FEntity(EntityManager::CreateEntity(), name);
	//	FTransform Temp;
	//	float rangeX=rand() % 50 + 0;
	//	float rangeY=rand() % 50 + 0;
	//	float rangeZ=rand() % 50 + 0;

	//	Temp.SetLocation(FVector(rangeX, rangeY, rangeZ));
	//	temp->AddComponent(FTransformComponent{ Temp });
	//	temp->AddComponent(FStaticMesh{});
	//	temp->AddComponent(DefaultLitMaterialComponent{});
	//}*/

	//CameraEntity = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Camera");
	//CameraEntity->AddComponent(KREngine::FCameraComponent{ true });
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

LevelTwo::LevelTwo(const std::string& Name) : FLevel(Name)
{
	RegisterSystem<FBoidSystem>();
	EntityManager::RegisterComponent<FBoidComponent>();

}

void LevelTwo::PreInit()
{
	FLevel::PreInit();
	ComponentUID UID;
	UID.set(EntityManager::GetComponentType<FTransformComponent>());
	UID.set(EntityManager::GetComponentType<FBoidComponent>());
	EntityManager::SetSystemComponents<FBoidSystem>(UID);
	
}

void LevelTwo::Init()
{
	FLevel::Init();

	
	
	for(int i = 3; i < 100; i++)
	{
		std::string name = "Boid--" ;
		name += std::to_string(i);
		auto temp = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), name);
		KREngine::FTransform Temp;
		float rangeX=rand() % 50 + 0;
		float rangeY=rand() % 50 + 0;
		float rangeZ=rand() % 50 + 0;
		FVector& scale = Temp.GetScale();
		scale = scale / 3;
		Temp.SetScale(scale);

		Temp.SetLocation(KREngine::FVector(rangeX, rangeY, rangeZ));
		temp->AddComponent(KREngine::FTransformComponent{ Temp });
		temp->AddComponent(KREngine::FStaticMesh{"Test"});
		temp->AddComponent(KREngine::DefaultUnLitMaterialComponent{});
		temp->AddComponent(FBoidComponent{});
	}
	//entity = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Rifle");
	//entity->AddComponent(KREngine::FTransformComponent{});
	//entity->AddComponent(KREngine::FStaticMesh{ "Test" });
	//entity->AddComponent(KREngine::DefaultUnLitMaterialComponent{});
	//entity->AddComponent(FBoidComponent{});

	//entity1 = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Rifle1");
	//entity1->AddComponent(KREngine::FTransformComponent{});
	//entity1->AddComponent(KREngine::FStaticMesh{ "Test" });
	//entity1->AddComponent(KREngine::DefaultUnLitMaterialComponent{});
	// entity1->AddComponent(FBoidComponent{});
	////entity = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Rifle3");
	////entity->AddComponent(KREngine::FTransformComponent{});
	////entity->AddComponent(KREngine::FStaticMesh{ "Test" });
	////entity->AddComponent(KREngine::DefaultUnLitMaterialComponent{});
	//entity2 = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Rifle1");
	//entity2->AddComponent(KREngine::FTransformComponent{});
	//entity2->AddComponent(KREngine::FStaticMesh{ "Test" });
	//entity2->AddComponent(KREngine::DefaultUnLitMaterialComponent{});
	//entity2->AddComponent(FBoidComponent{});

	CameraEntity = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Camera");
	CameraEntity->AddComponent(KREngine::FCameraComponent{ true });

	/*auto Ray = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Ray");
	Ray->AddComponent(KREngine::FTransformComponent{});
	Ray->AddComponent(KREngine::FRay{KREngine::FVector(0,0,1)});*/

	/*auto Line = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Line");
	Line->AddComponent(KREngine::FTransformComponent{});
	Line->AddComponent(KREngine::FLine{ KREngine::FVector(entity->GetComponent<KREngine::FTransformComponent>().Transform.GetLocation()), KREngine::FVector(10,0,0) });*/

	
}


void LevelTwo::Run()
{
	FLevel::Run();
	
	
	//a.position.x = entity->GetComponent<KREngine::FTransformComponent>().Transform.GetLocation().x;
	//a.position.y  = entity->GetComponent<KREngine::FTransformComponent>().Transform.GetLocation().y;
	////a.velo.x = 0;
	////a.velo.y = 0;

	//b.position.x = entity1->GetComponent<KREngine::FTransformComponent>().Transform.GetLocation().x;
	//b.position.y = entity1->GetComponent<KREngine::FTransformComponent>().Transform.GetLocation().y;
	////b.velo.x = 00;
	////b.velo.y = 0;


	//c.position.x = entity2->GetComponent<KREngine::FTransformComponent>().Transform.GetLocation().x;
	//c.position.y = entity2->GetComponent<KREngine::FTransformComponent>().Transform.GetLocation().y;

	//const game_object_t t(a);
	//const game_object_t t1(b);
	//const game_object_t t2(c);

	//MoveTo(&t, &t1);
	//MoveTo(&t1,&t2);

	//entity1->GetComponent<KREngine::FTransformComponent>().Transform.SetLocation(FVector{ t1.position.x, t1.position.y,0 });
	//entity2->GetComponent<KREngine::FTransformComponent>().Transform.SetLocation(FVector{  t2.position.x, t2.position.y,0 });
	

	

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



void LevelTwo::MoveTo(const game_object_t* Target, const game_object_t* Follower)
{
	vec2_t accleration(0,0);
	vec2_t desired = Target->position.Subtract(Follower->position);

	float mag = desired.Magnitude();
	float new_mag = std::min(mag, 100.0f);
	desired.SetMagnitue(new_mag);

	vec2_t desired_velocity = desired.Multiply(1 * 0.001);
	vec2_t steering = desired_velocity.Subtract(Follower->velocity);
	accleration.Add(steering);
	
	float acc_mag = accleration.Magnitude();
	//Since we have to limit the magnitude of acceleration to 10 units per frame^2
	// Since there's no limit per frame, we can use sqrt of 10 per frame. 
	//This would not work if we cant have per frame limitation, then would have to 
	float new_acc_mag = std::min(acc_mag, 3.162277f);
	accleration.SetMagnitue(new_acc_mag);

	//Check if the follower has reached the target, checking with a epsilon value
	if (Follower->position.Distance(Target->position) > 0.01f)
	{
		//has not reached the target location
		//Remove the const
		game_object_t* non_const_follower = const_cast<game_object_t*>(Follower);
		accleration.Add(steering);
		non_const_follower->velocity.Add(accleration);
		non_const_follower->position.Add(non_const_follower->velocity);
	}
	else
	{
		//has reached the target location
	}
	
	

}

void LevelTwo::Test()
{
	KREngine::Logger::Warning("Testing");
}

InstanceStaticMeshTestMap::InstanceStaticMeshTestMap(const std::string& Name): FLevel(Name)
{
}

InstanceStaticMeshTestMap::~InstanceStaticMeshTestMap()
{
}

void InstanceStaticMeshTestMap::Init()
{
	FLevel::Init();

	/*auto* entity = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Test");
	entity->AddComponent(KREngine::FTransformComponent{});
	entity->AddComponent(KREngine::FStaticMesh{ "Test" });
	entity->AddComponent(KREngine::FPointLight{});
	entity->AddComponent(KREngine::DefaultLitMaterialComponent{});

	entity = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Light");
	entity->AddComponent(KREngine::FTransformComponent{});
	entity->AddComponent(KREngine::FStaticMesh{ "Rifle" });
	entity->AddComponent(KREngine::FPointLight{});
	entity->AddComponent(KREngine::DefaultLitMaterialComponent{});

	KREngine::FEntity* CameraEntity = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Camera");
	CameraEntity->AddComponent(KREngine::FCameraComponent{ true });*/
}

void InstanceStaticMeshTestMap::Run()
{
}

void InstanceStaticMeshTestMap::End()
{
}

void InstanceStaticMeshTestMap::GUIInit()
{
}

void InstanceStaticMeshTestMap::GUIRun()
{
}

void InstanceStaticMeshTestMap::GUIEnd()
{
}
