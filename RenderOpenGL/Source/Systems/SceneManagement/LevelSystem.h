#pragma once
#include "Entity/Entity.h"
#include "Systems/Systems.h"


namespace KREngine
{
	class FLevel 
	{
	public:

		virtual ~FLevel() = default;
		FLevel( const std::string& mapName): MapName(mapName)
		{
			
		}
		virtual void Init() {};
		virtual void Run() {};
		virtual void End() {};
		virtual void GUIInit() {};
		virtual void GUIRun() {};
		virtual void GUIEnd() {};

		void AddEntity(FEntityHandle handle);
		void RemoveEntity(FEntityHandle handle);

		std::set<FEntityHandle> GetEntityHandles()
		{
			return EntityHandles;
		}

	protected:
		std::string MapName ="Default";
		std::set<FEntityHandle> EntityHandles;

	};
}
