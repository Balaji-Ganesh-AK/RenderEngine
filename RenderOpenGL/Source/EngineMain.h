#pragma once
#include "GameManager.h"

#include "Game.h"
#include "GameManager.h"
#include "Runtime/Containers/TArray.h"
extern KREngine::FApplication* KREngine::CreateApplication();
namespace KREngine
{
	class EngineManager
	{



	public:
		static EngineManager& Get()
		{
			static EngineManager instance;
			return instance;
		}
		static void PreInit(FApplication& Application)
		{
			if(!Get().Application)
			{
				Get().Application = &Application;
		
			}
		}

		static void Init()
		{
			if (Get().Application)
			{
			
				Get().Application->InternalInit();

			}
		}
		static void Run()
		{
			if (Get().Application)
			{
				
				Get().Application->InternalRun();

			}
		}
		static void End()
		{
			if (Get().Application)
			{
				Get().Application->InternalEnd();

			}
		}
		
	private:
		EngineManager() = default;

		FApplication* Application = nullptr;

	};
}
