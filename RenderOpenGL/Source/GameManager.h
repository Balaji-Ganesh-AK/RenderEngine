#pragma once
#include "Systems/Systems.h"


namespace KREngine
{
	

	class FApplication
	{
	public:
		FApplication();
		virtual ~FApplication();
		//static FGameManager& Instance()
		//{
		//static FGameManager instance;
		//	return instance;
		//}


		FORCEINLINE static FApplication& Get()
		{
			return *Instance;
		}

		virtual void Init() = 0;
		virtual void Run() = 0;
		virtual void End() = 0;


		 void InternalInit();

		 void InternalRun();

		 void InternalEnd();
	

		 void RegisterSystem(std::shared_ptr<FGameSystem> GameSystem) const;

	private:
		
		static FApplication* Instance;

		void EngineInit();
		void EngineRun();
		void EngineEnd();

		KREngine::SystemManager* GameSystemManager = nullptr;
	};
	FApplication* CreateApplication();
	
}
