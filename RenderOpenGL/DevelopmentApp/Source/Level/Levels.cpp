#include "Levels.h"

#include "Editor/Gizmo.h"
#include "Entity/Components/TransformComponent.h"
#include "Material/DefaultMateirals.h"
#include "Material/DefaultUnlitMaterial.h"
#include "RenderOpenGL/DevelopmentApp/Source/Sandbox.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"
#include "Runtime/Line/Line.h"
#include "Runtime/Line/Ray.h"


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


}

void LevelTwo::Init()
{
	FLevel::Init();


	//for(int i = 3; i < 100; i++)
	//{
	//	std::string name = "Static-Mesh--" ;
	//	name += std::to_string(i);
	//	auto temp = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), name);
	//	KREngine::FTransform Temp;
	//	float rangeX=rand() % 50 + 0;
	//	float rangeY=rand() % 50 + 0;
	//	float rangeZ=rand() % 50 + 0;

	//	Temp.SetLocation(KREngine::FVector(rangeX, rangeY, rangeZ));
	//	temp->AddComponent(KREngine::FTransformComponent{ Temp });
	//	temp->AddComponent(KREngine::FStaticMesh{"Test"});
	//	temp->AddComponent(KREngine::DefaultLitMaterialComponent{});
	//}
	entity = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Rifle");
	entity->AddComponent(KREngine::FTransformComponent{});
	entity->AddComponent(KREngine::FStaticMesh{ "Test" });
	entity->AddComponent(KREngine::DefaultUnLitMaterialComponent{});
	//entity = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Rifle1");
	//entity->AddComponent(KREngine::FTransformComponent{});
	//entity->AddComponent(KREngine::FStaticMesh{ "Rifle" });
	//entity->AddComponent(KREngine::DefaultUnLitMaterialComponent{});
	
	CameraEntity = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Camera");
	CameraEntity->AddComponent(KREngine::FCameraComponent{ true });

	auto Ray = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Ray");
	Ray->AddComponent(KREngine::FTransformComponent{});
	Ray->AddComponent(KREngine::FRay{KREngine::FVector(0,0,1)});

	/*auto Line = new KREngine::FEntity(KREngine::EntityManager::CreateEntity(), "Line");
	Line->AddComponent(KREngine::FTransformComponent{});
	Line->AddComponent(KREngine::FLine{ KREngine::FVector(entity->GetComponent<KREngine::FTransformComponent>().Transform.GetLocation()), KREngine::FVector(10,0,0) });*/


}

void LevelTwo::Run()
{
	FLevel::Run();
	//
	//static int x = 0;
	//static int y = 0;
	//static int z = 0;
	//KREngine::FVector vector = CameraEntity->GetComponent<KREngine::FCameraComponent>().GetCameraFront() - entity->
	//	GetComponent<KREngine::FTransformComponent>().Transform.GetLocation();

	//entity->GetComponent<KREngine::FTransformComponent>().Transform.SetRotation(vector);
	////KREngine::Logger::Warning("Testing, %s", vector.ToPrint());
	////entity->GetComponent().Transform.SetRotation();

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
