#include "LevelSystem.h"


namespace  KREngine
{
	void FLevel::AddEntity(FEntityHandle handle)
	{
		EntityHandles.emplace(handle);
	}

	void FLevel::RemoveEntity(FEntityHandle handle)
	{
		EntityHandles.erase(handle);
	}
}
