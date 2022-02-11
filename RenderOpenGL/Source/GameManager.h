#pragma once


#include "Systems/Systems.h"

// ReSharper disable once IdentifierTypo
#define IMGUI_LEFT_LABEL(func, label, code) ImGui::TextUnformatted(label);ImGui::NextColumn(); ImGui::SameLine(); ImGui::SetNextItemWidth(-1);if(func) { code } ImGui::NextColumn()
namespace KREngine
{
	class FTransformSystem;
	class FStaticMeshSystem;
	class FEditorTagSystem;


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


		WindowsWindow* GetWindowsWindow() const
		{
			return WindowWindow.get();
		}
		

		 

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


		bool bShowDebugProfiler{ false };
		bool bEnableVSync{ false };
		float test{ 0.0f };


		FEntity* entity{};

		std::shared_ptr<FEditorTagSystem> EditorTagSystem;
		std::shared_ptr<FRenderingSystem> RenderingSystem;
		std::shared_ptr<FStaticMeshSystem> StaticMeshSystem;
		std::shared_ptr<FTransformSystem> TransformSystem;
	};
	FApplication* CreateApplication();



}
