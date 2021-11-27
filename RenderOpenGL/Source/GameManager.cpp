
#include "GameManager.h"

#include "RenderingSystem/FRenderingSystem.h"


namespace KREngine
{
	void FGameManager::Init()
	{
		EngineInit();
	}

	void FGameManager::Run()
	{
		EngineRun();
	}

	void FGameManager::End()
	{
		EngineEnd();
	}
	template <typename T>
	void FGameManager::AddGame(T* game) 
	{
		


		if ( game )
		{
			if ( dynamic_cast< FGame* >( game ) )
			{

				Instance().GameSystems->GameLoop = std::make_shared<T>( *game );
			}
			else
			{
				Logger::Fatal( "Trying to add a empty game!" );
			}
		}

	}

	void FGameManager::EngineInit()
	{
		GameSystems = new SystemManager();

		//PrintCurrentMemoryUsage();
		GameSystems->Init();
		//	PrintCurrentMemoryUsage();
		GameSystems->InitGUI();

		int i = 10000000;

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

	void FGameManager::EngineRun()
	{
		while ( GameSystems->GetRenderingSystem()->GetWindowsWindow()->IsActive() )
		{
			{
				SCOPED_TIMER( "Systems Loop" );
				GameSystems->Run();
				GameSystems->RunGUI();

			}
		}
	}

	void FGameManager::EngineEnd()
	{
		GameSystems->StopGUI();
		GameSystems->Stop();
		delete GameSystems;
		Logger::Verbose( " Engine Shutting down!" );
	}
}
