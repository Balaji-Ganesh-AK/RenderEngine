
#include "GameManager.h"

#include "RenderingSystem/FRenderingSystem.h"


namespace KREngine
{

	FApplication* FApplication::Instance = nullptr;

	void FApplication::InternalInit()
	{
		EngineInit();

	}

	void FApplication::InternalRun()
	{
		EngineRun();

	}

	void FApplication::InternalEnd()
	{
		EngineEnd();

	}

	void FApplication::RegisterSystem(std::shared_ptr<FGameSystem> GameSystem) const
	{
		if(GameSystemManager)
		{
			if(GameSystem)
			{
				GameSystemManager->SystemsList.emplace_back((GameSystem));
			}
			
		}
		else
		{
			Logger::Error("No System Manager found!, please register the game system after engine initialization call");
		}
	}

	FApplication::FApplication()
	{
		if(Instance!=nullptr)
		{
			Instance = this;
		}
	}

	FApplication::~FApplication()
	{
	}



	void FApplication::EngineInit()
	{
		GameSystemManager = new SystemManager();
		
		//PrintCurrentMemoryUsage();
		GameSystemManager->Init();

		Init();

		//	PrintCurrentMemoryUsage();
		GameSystemManager->InitGUI();



		//std::vector<int> tes(i, 1);
		//UTimerLog Systems( "Systems Loop" );
		//{
		//	/*for (auto& x : tes )
		//	{
		//		x += rand();
		//	}*/

		//	std::for_each( std::execution::par, tes.begin(), tes.end(), [] ( int& x )
		//	{
		//		x += rand();
		//	} );
		//	
		//}
	}

	void FApplication::EngineRun()
	{
		while (GameSystemManager->GetRenderingSystem()->GetWindowsWindow()->IsActive())
		{
			{

				{
					SCOPED_TIMER("Systems Loop");
					GameSystemManager->Run();

				}
				{
					SCOPED_TIMER("Game Loop");
					Run();
				}

				{
					SCOPED_TIMER("GUI Loop");
					GameSystemManager->RunGUI();
				}

			}
			
		}
	}

	void FApplication::EngineEnd()
	{
		GameSystemManager->StopGUI();
		End();
		GameSystemManager->Stop();
		delete GameSystemManager;
		Logger::Verbose(" Engine Shutting down!");
	}

}