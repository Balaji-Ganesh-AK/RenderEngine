#include "utility/Globals.h"
#include "Systems.h"
#include "RenderingSystem/FRenderingSystem.h"
#include "RenderingSystem/WindowsWindow.h"

//#include "utility/Globals.h"

namespace KREngine
{

	void SystemManager::Init()
	{
		RenderingSystem->Init();
		/*for( std::vector<std::shared_ptr<FGameSystem>>::value_type GameSystem : SystemsList)
		{
			GameSystem->Init();
		}*/
	}

	void SystemManager::Run()
	{
		RenderingSystem->Run();
		/*for ( std::vector<std::shared_ptr<FGameSystem>>::value_type GameSystem : SystemsList )
		{
			
		}*/
	}

	void SystemManager::Stop()
	{
		RenderingSystem->Stop();
		/*for ( std::vector<std::shared_ptr<FGameSystem>>::value_type GameSystem : SystemsList )
		{
			
		}*/
	}

#if GUI
  	void SystemManager::InitGUI()
	{
		RenderingSystem->GUIInit();
		/*for ( std::vector<std::shared_ptr<FGameSystem>>::value_type GameSystem : SystemsList )
		{
			
		}*/
	}

	void SystemManager::RunGUI()
	{

		SCOPED_TIMER( "GUI LOOP" );
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		bool bT = true;
		static bool opt_fullscreen = true;
		static bool rtest = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if ( opt_fullscreen )
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos( viewport->WorkPos );
			ImGui::SetNextWindowSize( viewport->WorkSize );
			ImGui::SetNextWindowViewport( viewport->ID );
			ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
			ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if ( dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode )
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if ( !opt_padding )
			ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0.0f, 0.0f ) );
		ImGui::Begin( "Kaar Engine v 0.0.1", &opt_fullscreen, window_flags );
		if ( !opt_padding )
			ImGui::PopStyleVar();

		if ( opt_fullscreen )
			ImGui::PopStyleVar( 2 );

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if ( io.ConfigFlags & ImGuiConfigFlags_DockingEnable )
		{
			const ImGuiID dockspace_id = ImGui::GetID( "MyDockSpace" );
			ImGui::DockSpace( dockspace_id, ImVec2( 0.0f, 0.0f ), dockspace_flags );
		}

		if ( ImGui::BeginMenuBar() )
		{
			if ( ImGui::BeginMenu( "Options" ) )
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem( "Exit", NULL, &rtest );
				//ImGui::MenuItem( "Padding", NULL, &opt_padding );
				//ImGui::Separator();

				if ( ImGui::MenuItem( "Flag: NoSplit", "", ( dockspace_flags & ImGuiDockNodeFlags_NoSplit ) != 0 ) ) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
				if ( ImGui::MenuItem( "Flag: NoResize", "", ( dockspace_flags & ImGuiDockNodeFlags_NoResize ) != 0 ) ) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
				if ( ImGui::MenuItem( "Flag: NoDockingInCentralNode", "", ( dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode ) != 0 ) ) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
				if ( ImGui::MenuItem( "Flag: AutoHideTabBar", "", ( dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar ) != 0 ) ) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
				if ( ImGui::MenuItem( "Flag: PassthruCentralNode", "", ( dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode ) != 0, opt_fullscreen ) ) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
				ImGui::Separator();



				ImGui::EndMenu();
			}

			if ( ImGui::BeginMenu( "Windows" ) )
			{
				if ( ImGui::MenuItem( "Show Profiler", "", ( bShowDebugProfiler ) != 0 ) )
				{
					bShowDebugProfiler = !bShowDebugProfiler;
				}
				ImGui::Separator();



				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}


		
		RenderingSystem->GUIRun();



		/*Post Update*/
		if( bShowDebugProfiler )
			EProfileDebugger::Instance().GUIRun();


		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );



		if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent( backup_current_context );
		}
	}

	void SystemManager::StopGUI()
	{
		RenderingSystem->GUIStop();
		/*for (std::vector<std::shared_ptr<FGameSystem>>::value_type GameSystem : SystemsList )
		{
			
		}*/
	}

	SystemManager::SystemManager()
	{
		Properties = std::make_unique<WindowsProperties>( WindowsProperties( ERenderingAPI::OpenGL, 1020, 1440, "Kaar Engine V 0.0.0.1" ) );
		WindowWindow = std::make_unique < WindowsWindow>( *Properties.get() );
		RenderingSystem = std::make_shared<FRenderingSystem>( WindowWindow.get() );

		InputSystem = std::make_unique<WindowsInput>(RenderingSystem);
	}
#endif


	/*void SystemManager::Register( std::shared_ptr<FGameSystem> system )
	{
		if(system)
		{
			SystemsList.push_back( system );
		}
	}*/

	FRenderingSystem* SystemManager::GetRenderingSystem() const
	{
		return RenderingSystem.get();
	}

	WindowsInput* SystemManager::GetInput() const
	{
		return InputSystem.get();
	}
}
