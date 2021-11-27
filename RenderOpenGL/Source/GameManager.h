#pragma once
#include "Systems/Systems.h"


namespace KREngine
{
	class FGameManager
	{
	public:
		FGameManager() = default;
		//static FGameManager& Instance()
		//{
		//static FGameManager instance;
		//	return instance;
		//}

		 void Init();

		 void Run();

		 void End();
		template <typename T>
		static void AddGame(T* game);
	private:

		void EngineInit();
		void EngineRun();
		void EngineEnd();

		KREngine::SystemManager* GameSystems = nullptr;
	};


}
