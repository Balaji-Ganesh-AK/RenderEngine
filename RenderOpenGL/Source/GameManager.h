#pragma once






// ReSharper disable once IdentifierTypo
#define IMGUI_LEFT_LABEL(func, label, code) ImGui::TextUnformatted(label);ImGui::NextColumn(); ImGui::SameLine(); ImGui::SetNextItemWidth(-1);if(func) { code } ImGui::NextColumn()
#include <memory>

#include "RenderOpenGL/Utility/Source/Defines.h"

namespace KREngine
{

	class FLevel;
	class FAssetManager;
	class FTransformSystem;
	class FDefaultUnLitMaterialSystem;
	class FDefaultLitMaterialSystem;
	class FShaderManager;
	class FEditorComponentPanelSystem;
	class FMaterialSystem;
	class FTextureManager;
	class FEvent;
	class WindowsWindow;
	class WindowsProperties;
	class FRenderingSystem;
	class FCameraSystem;
	class FInput;
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

		virtual void Init();
		virtual void Run();
		virtual void End();

		void SetActiveLevel(FLevel* level);
		void ChangeLevel(FLevel* newLevel);
		void OnEvent(FEvent& event);

		WindowsWindow* GetWindowsWindow() const
		{
			return WindowWindow.get();
		}

		FInput& GetInputSystem() const
		{
			return *Input;
		}
		static FTextureManager& GetTextureManager()
		{
			return *Get().TextureManager;
		}

		static FShaderManager& GetShaderManager()
		{
			return *Get().ShaderManager;
		}
		static FAssetManager& GetAssetManager()
		{
			return *Get().AssetManager;
		}
		static FLevel* GetCurrentLevel()
		{
			return Get().CurrentLevel;
		}
		static void SaveLevel()
		{
			Get().SaveLevelInternal();
		}
		static void LoadLevel()
		{
			Get().LoadLevelInternal();
		}
	private:
		
		static FApplication* Instance;
		
		void EngineInit();
		void EngineRun();
		void EngineEnd();


		void InternalInit();

		void InternalRun();

		void InternalEnd();

		void SaveLevelInternal();
		void LoadLevelInternal();

#if GUI
		void EngineGUIInit();
		void EngineGUIRun();
		void EngineGUIStop();
#endif



		std::unique_ptr<WindowsProperties> Properties;
		std::unique_ptr<WindowsWindow> WindowWindow;
		std::shared_ptr<FInput> Input;
		std::unique_ptr<FTextureManager> TextureManager;
		std::unique_ptr<FShaderManager> ShaderManager;
		std::unique_ptr<FAssetManager> AssetManager;

		FLevel* CurrentLevel = nullptr;
		bool bShowDebugProfiler{ false };


		/*Settings*/
		bool bEnableVSync{ false };
		bool bEnableWireMode{ false };
		float test{ 0.0f };



		std::shared_ptr<FEditorTagSystem> EditorTagSystem;
		std::shared_ptr<FRenderingSystem> RenderingSystem;
		std::shared_ptr<FDefaultUnLitMaterialSystem> DefaultShaderSystem;
		std::shared_ptr<FDefaultLitMaterialSystem> DefaultLitShaderSystem;
		std::shared_ptr<FStaticMeshSystem> StaticMeshSystem;
		//std::shared_ptr<FTransformSystem> TransformSystem;
		std::shared_ptr<FCameraSystem> CameraSystem;
		std::shared_ptr<FEditorComponentPanelSystem> EditorPanelSystem;
	


	};
	FApplication* CreateApplication();



}
