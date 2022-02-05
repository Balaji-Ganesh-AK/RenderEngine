#pragma once
#include "RenderingSystem/Buffers.h"
#include "Systems/Systems.h"


namespace KREngine
{
	

	class FApplication
	{
		friend class EngineManager;
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


		
	

		 void RegisterSystem(std::shared_ptr<FGameSystem> GameSystem) const;

	private:
		
		static FApplication* Instance;

		void EngineInit();
		void EngineRun();
		void EngineEnd();


		void InternalInit();

		void InternalRun();

		void InternalEnd();


#if GUI
		void EngineGUIInit();
		void EngineGUIRun();
		void EngineGUIStop();
#endif



		std::unique_ptr<WindowsProperties> Properties;
		std::unique_ptr<WindowsWindow> WindowWindow;
		std::shared_ptr<FFrameBuffer> Framebuffer;

		bool bShowDebugProfiler{ false };
		float test{ 0.0f };
	};
	FApplication* CreateApplication();



}
