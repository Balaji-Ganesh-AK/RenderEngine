#include "Entity.h"

namespace KREngine
{
	

	EntityManager::EntityManager()
	{

		for(FEntityHandle index =0; index < MAX_ENTITIES; index++ )
		{
			AvailableHandles.emplace(index);
		}

		EntityIDLookUp.reserve(MAX_ENTITIES);
	}

	FEntityHandle EntityManager::CreateEntity()
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

	FEntity::FEntity(const FEntityHandle& handle): EntityHandle(handle)
	{

	}

	FEntity::~FEntity()
	{
	}


}
