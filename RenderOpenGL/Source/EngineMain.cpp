
#include "utility/EngineCore.h"
#include "EngineMain.h"
using namespace KREngine;

	int main( void )
	{
		{
			FApplication* Application = KREngine::CreateApplication();
			EngineManager::PreInit(*Application);

			EngineManager::Init();
			EngineManager::Run();
			EngineManager::End();

			delete Application;
		}
	}


