#pragma once






// ReSharper disable once IdentifierTypo
#define IMGUI_LEFT_LABEL(func, label, code) ImGui::TextUnformatted(label);ImGui::NextColumn(); ImGui::SameLine(); ImGui::SetNextItemWidth(-1);if(func) { code } ImGui::NextColumn()
#include <memory>

namespace KREngine
{
	class FEditorComponentPanelSystem;
	class FMaterialSystem;
	class FTextureManager;
	class FEvent;
	class WindowsWindow;
	class WindowsProperties;
	class FRenderingSystem;
	class FCameraSystem;
	class FInput;
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


		static FApplication& Get()
		{
			return *Instance;
		}

		virtual void Init() = 0;
		virtual void Run() = 0;
		virtual void End() = 0;

		void OnEvent(FEvent& event);

		WindowsWindow* GetWindowsWindow() const
		{
			return WindowWindow.get();
		}
		
		FInput& GetInputSystem() 
		{
			return *Input;
		}
		static FTextureManager& GetTextureManager()
		{
			return *Get().TextureManager;
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
		std::shared_ptr<FInput> Input;
		std::unique_ptr<FTextureManager> TextureManager;

		bool bShowDebugProfiler{ false };
		bool bEnableVSync{ false };
		float test{ 0.0f };



		std::shared_ptr<FEditorTagSystem> EditorTagSystem;
		std::shared_ptr<FRenderingSystem> RenderingSystem;
		std::shared_ptr<FStaticMeshSystem> StaticMeshSystem;
		std::shared_ptr<FTransformSystem> TransformSystem;
		std::shared_ptr<FCameraSystem> CameraSystem;
		std::shared_ptr<FEditorComponentPanelSystem> EditorPanelSystem;

	};
	FApplication* CreateApplication();



}
