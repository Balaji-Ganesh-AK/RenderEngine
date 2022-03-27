
#include "GameManager.h"


#include "Entity/Components/EditorComponentUI.h"
#include "RenderingSystem/FRenderingSystem.h"
#include "Entity/Components/EditorTagComponent.h"
#include "Entity/Components/TransformComponent.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"
#include "RenderingSystem/WindowsWindow.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"
#include "Runtime/Camera/FCamera.h"
#include "Material/DefaultMateirals.h"
#include "Material/DefaultUnlitMaterial.h"
#include "Systems/AssetSystem/AssetSystem.h"
#include "Systems/Input/Input.h"
#include "Systems/ShaderSystem/ShaderSystem.h"
#include "Systems/TextureSystem/TextureManager.h"

//#define IMGUI_LEFT_LABEL(func, label, code) ImGui::TextUnformatted(label); ImGui::NextColumn(); ImGui::SetNextItemWidth(-1); if(func) { code } ImGui::NextColumn();

namespace KREngine
{

	FApplication* FApplication::Instance = nullptr;

	void FApplication::InternalInit()
	{
		EngineInit();
#ifdef  GUI
		EngineGUIInit();
#endif

	}

	void FApplication::InternalRun()
	{
		while(WindowWindow->IsActive())
		{
			EngineGUIRun();
			EngineRun();
#ifdef  GUI
		
#endif
		}
	

	}

	void FApplication::InternalEnd()
	{
		EngineEnd();
#ifdef  GUI
		EngineGUIStop();
#endif

	}
#if GUI
	void FApplication::EngineGUIInit()
	{
		const char* glsl_version = "#version 130";
		// Setup Dear ImGui context

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.IniFilename = nullptr;
		//io.IniFilename = nullptr;
		ImGui::LoadIniSettingsFromDisk("../Config/Imgui.ini");
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		ImGuiStyle* Style = &ImGui::GetStyle();
		Style->WindowPadding = ImVec2(15, 15);
		Style->WindowRounding = 5.0f;
		Style->FramePadding = ImVec2(5, 5);
		Style->FrameRounding = 4.0f;
		Style->ItemSpacing = ImVec2(12, 8);
		Style->ItemInnerSpacing = ImVec2(8, 6);
		Style->IndentSpacing = 25.0f;
		Style->ScrollbarSize = 15.0f;
		Style->ScrollbarRounding = 9.0f;
		Style->GrabMinSize = 5.0f;
		Style->GrabRounding = 3.0f;

		//Dont use
		if (0)
		{
			Style->Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
			Style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
			//Style->Colors [ImGuiCol_TextHovered] = ImVec4( 1.00f, 1.00f, 1.00f, 1.00f );
			//Style->Colors [ImGuiCol_TextActive] = ImVec4( 1.00f, 1.00f, 0.00f, 1.00f );
			Style->Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
			// Style->Colors [ImGuiCol_ChildWindowBg] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
			Style->Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
			Style->Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
			Style->Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			Style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
			Style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
			Style->Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
			Style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
			Style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
			Style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
			Style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
			Style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
			Style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
			Style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
			// Style->Colors [ImGuiCol_ComboBg] = ImVec4( 0.86f, 0.86f, 0.86f, 0.99f );
			Style->Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			Style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
			Style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			Style->Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
			Style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			Style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
			Style->Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
			Style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
			Style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			// Style->Colors [ImGuiCol_Column] = ImVec4( 0.39f, 0.39f, 0.39f, 1.00f );
			//Style->Colors [ImGuiCol_ColumnHovered] = ImVec4( 0.26f, 0.59f, 0.98f, 0.78f );
			//Style->Colors [ImGuiCol_ColumnActive] = ImVec4( 0.26f, 0.59f, 0.98f, 1.00f );
			Style->Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
			Style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
			Style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
			//Style->Colors [ImGuiCol_CloseButton] = ImVec4( 0.59f, 0.59f, 0.59f, 0.50f );
			//Style->Colors [ImGuiCol_CloseButtonHovered] = ImVec4( 0.98f, 0.39f, 0.36f, 1.00f );
			//Style->Colors [ImGuiCol_CloseButtonActive] = ImVec4( 0.98f, 0.39f, 0.36f, 1.00f );
			Style->Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
			Style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
			Style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			Style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			Style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
			//Style->Colors [ImGuiCol_TooltipBg] = ImVec4( 1.00f, 1.00f, 1.00f, 0.94f );
			// Style->Colors [ImGuiCol_ModalWindowDarkening] = ImVec4( 0.20f, 0.20f, 0.20f, 0.35f );
		}
		//GOOD
		if (1)
		{
			auto& colors = ImGui::GetStyle().Colors;
			colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

			// Headers
			colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
			colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
			colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

			// Buttons
			colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
			colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
			colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

			// Frame BG
			colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
			colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
			colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

			// Tabs
			colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
			colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
			colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

			// Title
			colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		}
		if (0)
		{
			Style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
			Style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			Style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			// Style->Colors [ImGuiCol_ChildWindowBg] = ImVec4( 0.07f, 0.07f, 0.09f, 1.00f );
			Style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
			Style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
			Style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
			Style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			Style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			Style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			Style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			Style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
			Style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
			Style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			Style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			Style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			Style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			Style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			// Style->Colors [ImGuiCol_ComboBg] = ImVec4( 0.19f, 0.18f, 0.21f, 1.00f );
			Style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			Style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
			Style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			Style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			Style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
			Style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			Style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
			Style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			Style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			// Style->Colors [ImGuiCol_Column] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
			//// Style->Colors [ImGuiCol_ColumnHovered] = ImVec4( 0.24f, 0.23f, 0.29f, 1.00f );
			// Style->Colors [ImGuiCol_ColumnActive] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
			Style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			Style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
			Style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
			// Style->Colors [ImGuiCol_CloseButton] = ImVec4( 0.40f, 0.39f, 0.38f, 0.16f );
			/// Style->Colors [ImGuiCol_CloseButtonHovered] = ImVec4( 0.40f, 0.39f, 0.38f, 0.39f );
			//  Style->Colors [ImGuiCol_CloseButtonActive] = ImVec4( 0.40f, 0.39f, 0.38f, 1.00f );
			Style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
			Style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
			Style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
			Style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
			Style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
			//   Style->Colors [ImGuiCol_ModalWindowDarkening] = ImVec4( 1.00f, 0.98f, 0.95f, 0.73f );
		}

		//  ImGui::StyleColorsDark();


		ImGui_ImplGlfw_InitForOpenGL(WindowWindow->GetCurrentWindow(), true);
		ImGui_ImplOpenGL3_Init(glsl_version);


	/*	Framebuffer.reset(FFrameBuffer::CreateFrameBuffer(WindowWindow->Properties->GetWidth(),
			WindowWindow->Properties->GetHeight()));
		*/
		glfwSwapInterval(bEnableVSync);


		EditorTagSystem->GUIInit();

		StaticMeshSystem->GUIInit();
		RenderingSystem->GUIInit();
	}

	void FApplication::EngineGUIRun()
	{
		//Framebuffer->UnBindBuffer();



		SCOPED_TIMER("GUI LOOP");
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static bool opt_fullscreen = true;
		static bool AppExit = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Kaar Engine v 0.0.1", &opt_fullscreen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			const ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		ImGui::BeginMenuBar();
		{
			if(ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem( "Padding", NULL, &opt_padding );
				//ImGui::Separator();

				if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
				ImGui::Separator();



				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Windows"))
			{
				
				


				ImGui::EndMenu();
			}
			

			if (ImGui::BeginMenu("Settings"))
			{
			
				if (ImGui::MenuItem("Enable V-Sync", "", (bEnableVSync) != 0))
				{
					bEnableVSync = !bEnableVSync;
					glfwSwapInterval(bEnableVSync);
				}
				ImGui::Separator();



				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}


		{
		//	TransformSystem->GUIInit();
			RenderingSystem->GUIRun();

			ImGui::Begin("World Outliner");
			EditorTagSystem->GUIRun();
			ImGui::End();

			ImGui::Begin("Properties Panel");
			EditorPanelSystem->GUIRun();

			ImGui::End();
			ImGui::Begin("Content Browser");
			ImGui::End();

			//DefaultLitShaderSystem->GUIRun();

			ImGui::Begin("Actor menu");
			ImGui::End();

			ImGui::Begin("Profiler");
			IMGUI_LEFT_LABEL(ImGui::Checkbox("##AShow Profiler", &bShowDebugProfiler), "Show Profiler");
			ImGui::Separator();
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			
			ImGui::End();


		}


		/*Post Update*/
		if (bShowDebugProfiler)
			EProfileDebugger::Instance().GUIRun();


		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}






	}

	void FApplication::EngineGUIStop()
	{
		ImGui::SaveIniSettingsToDisk("../Config/Imgui.ini");
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
#endif



	FApplication::FApplication()
	{
		if(Instance==nullptr)
		{
			Instance = this;

		}
	}

	FApplication::~FApplication()
	{
	}


	void FApplication::OnEvent(FEvent& event)
	{
		EventDispatcher dispatcher(event);
		Properties->OnWindowsEvent(event);
		Input->OnEvent(event);
	}

	void FApplication::EngineInit()
	{
		Properties = std::make_unique<WindowsProperties>(WindowsProperties(ERenderingAPI::OpenGL, 1020, 1440, "Kaar Engine V 0.0.0.1"));
		Properties->EventCallBack = std::bind(&FApplication::OnEvent, this, std::placeholders::_1);
		WindowWindow = std::make_unique< WindowsWindow>(*Properties);

		/*Load everything before starting the GUI*/
		/*Loading textures needs GLFW for OPENGL*/
		/*TODO: Create a sync for each loading and make each manager run its own thread*/
		{

			TextureManager.reset(FTextureManager::Create());
			TextureManager->Init();
			ShaderManager.reset(FShaderManager::Create());
			ShaderManager->Init();
			AssetManager.reset(FAssetManager::Create());
			AssetManager->Init();
		}

		Input.reset(FInput::Create(WindowWindow.get()));





		EntityManager::RegisterComponent<FName>();
		EntityManager::RegisterComponent<FTransformComponent>();
		EntityManager::RegisterComponent<FCamera>();
		EntityManager::RegisterComponent<DefaultLitMaterialComponent>();
		EntityManager::RegisterComponent<DefaultUnLitMaterialComponent>();
		EntityManager::RegisterComponent<FStaticMesh>();
		EntityManager::RegisterComponent<FPointLight>();
		

		//EntityManager::RegisterSystem<FStaticMeshSystem>();
		//StaticMeshSystem = EntityManager::RegisterSystem<FStaticMeshSystem>();
		//DefaultShaderSystem = EntityManager::RegisterSystem<FDefaultUnLitMaterialSystem>();
		//DefaultLitShaderSystem = EntityManager::RegisterSystem<FDefaultLitMaterialSystem>();
		EditorTagSystem = EntityManager::RegisterSystem<FEditorTagSystem>();
		RenderingSystem = std::make_shared<FRenderingSystem>();
		/*TransformSystem = EntityManager::RegisterSystem<FTransformSystem>();*/
	

		
	
		CameraSystem = EntityManager::RegisterSystem<FCameraSystem>();
		EditorPanelSystem = EntityManager::RegisterSystem<FEditorComponentPanelSystem>();


		{
			ComponentUID UID;
			UID.set(EntityManager::GetComponentType<FName>());
			EntityManager::SetSystemComponents<FEditorTagSystem>(UID);
		}
		{
			ComponentUID UID;
			UID.set(EntityManager::GetComponentType<FStaticMesh>());

			ComponentUID OUID;
			OUID.set(EntityManager::GetComponentType<DefaultLitMaterialComponent>());
			OUID.set(EntityManager::GetComponentType<DefaultUnLitMaterialComponent>());
			EntityManager::SetSystemComponents<FStaticMeshSystem>(UID, OUID);
		}

		//{
		//	ComponentUID UID;
		//	UID.set(EntityManager::GetComponentType<FTransformComponent>());
		//	//UID.set(EntityManager::GetComponentType<DefaultLitMaterialComponent>());
		//	UID.set(EntityManager::GetComponentType<DefaultUnLitMaterialComponent>());
		//	UID.set(EntityManager::GetComponentType<FStaticMesh>());
		//	EntityManager::SetSystemComponents<FRenderingSystem>(UID);
		//}

		/*Default unlit shader*/
		{
			ComponentUID UID;
			UID.set(EntityManager::GetComponentType<FTransformComponent>());
			UID.set(EntityManager::GetComponentType<FStaticMesh>());
			UID.set(EntityManager::GetComponentType<DefaultUnLitMaterialComponent>());
			EntityManager::SetSystemComponents<FDefaultUnLitMaterialSystem>(UID);
		}
		/*Default lit shader */
		{
			ComponentUID UID;
			UID.set(EntityManager::GetComponentType<FTransformComponent>());
			UID.set(EntityManager::GetComponentType<FStaticMesh>());
			UID.set(EntityManager::GetComponentType<DefaultLitMaterialComponent>());
			ComponentUID OUID;
			OUID.set(EntityManager::GetComponentType<FPointLight>());
			EntityManager::SetSystemComponents<FDefaultLitMaterialSystem>(UID, OUID);
		}
		
		{
			ComponentUID UID;
			UID.set(EntityManager::GetComponentType<FTransformComponent>());
			EntityManager::SetSystemComponents<FTransformSystem>(UID);
		}

		{
			ComponentUID UID;
			UID.set(EntityManager::GetComponentType<FCamera>());
			EntityManager::SetSystemComponents<FCameraSystem>(UID);
		}

		{
			ComponentUID UID;
			UID.set(EntityManager::GetComponentType<FTransformComponent>());
			//UID.set(EntityManager::GetComponentType<DefaultLitMaterialComponent>());
			//UID.set(EntityManager::GetComponentType<DefaultUnLitMaterialComponent>());
			EntityManager::SetSystemComponents<FEditorComponentPanelSystem>(UID);
		}
		

		

		Init();
		CameraSystem->Init();
		/*shader init*/
		
		//DefaultShaderSystem->Init();
		
		//EntityManager::GetSystem<FStaticMeshSystem>()->Init();
	
		
		RenderingSystem->Init();
		

	}

	void FApplication::EngineRun()
	{

		{
			SCOPED_TIMER("Engine Loop");
			EditorTagSystem->Run();
			CameraSystem->Run();
			RenderingSystem->Run(CameraSystem->GetMainCamera());
		}
		{
			SCOPED_TIMER("Game Loop");
			Run();
		}
	}

	void FApplication::EngineEnd()
	{
		End();


		Logger::Verbose(" Engine Shutting down!");
	}

}