#pragma once
#include "Entity/Entity.h"
#include "RenderOpenGL/Utility/Source/File/FJson.h"
#include "Systems/Systems.h"


namespace KREngine
{
	class FLevel 
	{
	public:

		virtual ~FLevel() = default;
		std::string& GetMapName()
		{
			return MapName;
		}

		FJson ToJson();
		void FromJson(FJson json);
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

		friend std::ostream& operator << (std::ostream& out, const FLevel& obj);
		

		std::set<FEntityHandle> GetEntityHandles()
		{
			return EntityHandles;
		}

	protected:
		const uint8 FormatVersion = 1;
		std::string MapName ="Default";
		std::set<FEntityHandle> EntityHandles;

	};
}
