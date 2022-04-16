#include "Entity.h"

#include "GameManager.h"
#include "Components/EditorTagComponent.h"
#include "Systems/SceneManagement/LevelSystem.h"

namespace KREngine
{
	

	FEntityHandler::FEntityHandler()
	{

		for(FEntityHandle index =0; index < MAX_ENTITIES; index++ )
		{
			AvailableHandles.emplace(index);
		}

	}

	FEntityHandler::~FEntityHandler()
	{
	}

	FEntityHandle FEntityHandler::CreateEntity()
	{
		 FEntityHandle entity = MAX_ENTITIES + 1;
		if(EntityCount < MAX_ENTITIES)
		{
			entity = AvailableHandles.front();
			AvailableHandles.pop();
			EntityCount++;

		}
		else
		{
			Logger::Fatal("MAX NUMBER OF ENTITES REACHED!, increase the entity max count via ");
		}


		return entity;
	}

	void FEntityHandler::DestroyEntity(FEntityHandle entityHandle)
	{
		if(entityHandle < MAX_ENTITIES)
		{
			ComponentUIDList[entityHandle].reset();
			AvailableHandles.push(entityHandle);
			--EntityCount;
		}
		else
		{
			Logger::Fatal(" can't delete unknown entity");
		}
	}

	void FEntityHandler::SetComponentUID(FEntityHandle EntityHandle, ComponentUID componentUID)
	{
		if(EntityHandle < MAX_ENTITIES)
		{
			ComponentUIDList[EntityHandle] = componentUID;
		}
		else
		{
			Logger::Fatal("can't set!! unknown entity");
		}
	}

	ComponentUID FEntityHandler::GetComponentUID(FEntityHandle entityHandle)
	{
		if (entityHandle < MAX_ENTITIES)
		{
			return ComponentUIDList[entityHandle];
		}
		else
		{
			Logger::Fatal("can't delete unknown entity");
		}
		return {};
	}

	uint64 FEntityHandler::GetEntityCount() const
	{
		return EntityCount;
	}

	EntityManager::~EntityManager()
	{
	}

	EntityManager::EntityManager()
	= default;

	FEntityHandle EntityManager::CreateEntityInternal()
	{
		return EntityHandler.CreateEntity();
	}



	uint64 EntityManager::EntityCountInternal() const
	{
		return EntityHandler.GetEntityCount();
	}


	FEntity::FEntity(const FEntityHandle& handle,const std::string name): EntityHandle(handle)
	{

		std::string entity_with_count = name;
		/*Adding a default name for all the entity*/
		if(name.empty())
		{
			entity_with_count = "Entity_" + std::to_string(EntityManager::EntityCount());
		}
		FLevel* level = FApplication::GetCurrentLevel();
		if(level)
		{
			level->AddEntity(handle);
		}
		else
		{
			Logger::Fatal("No level registered in game! , make sure your are not adding entity in the constructor!");
		}
		EntityManager::AddComponent(handle, FName{ name });
	}

	FEntity::~FEntity()
	{
	}


}
