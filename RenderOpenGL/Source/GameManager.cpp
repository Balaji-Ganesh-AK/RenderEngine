
#include "GameManager.h"

#include "RenderingSystem/FRenderingSystem.h"
#define IMGUI_LEFT_LABEL(func, label, code) ImGui::TextUnformatted(label);ImGui::NextColumn(); ImGui::SameLine(); ImGui::SetNextItemWidth(-1);if(func) { code } ImGui::NextColumn()

//#define IMGUI_LEFT_LABEL(func, label, code) ImGui::TextUnformatted(label); ImGui::NextColumn(); ImGui::SetNextItemWidth(-1); if(func) { code } ImGui::NextColumn();

namespace KREngine
{

	FApplication* FApplication::Instance = nullptr;

	void FApplication::InternalInit()
	{
		EngineInit();
		EngineGUIInit();

	}

	void FApplication::InternalRun()
	{
		while(WindowWindow->IsActive())
		{
			EngineRun();
			EngineGUIRun();
		}
	

	}

	void FApplication::InternalEnd()
	{
		EngineEnd();
		EngineGUIStop();

	}
#if GUI
	void FApplication::EngineGUIInit()
	{
		const char* glsl_version = "#version 130";
		// Setup Dear ImGui context

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.IniFilename = NULL;
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
		glfwSwapInterval(0);*/


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
				ImGui::MenuItem("Exit", NULL, &AppExit);
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
				if (ImGui::MenuItem("Show Profiler", "", (bShowDebugProfiler) != 0))
				{
					bShowDebugProfiler = !bShowDebugProfiler;
				}
				ImGui::Separator();



				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}


		{
			ImGui::Begin("ScreenPort");
			if (test != WindowWindow->Properties->GetWidth())
			{
				test = WindowWindow->Properties->GetWidth();
				//Framebuffer->OnWindowResize(static_cast<float>(WindowWindow->Properties->GetWidth()), static_cast<float>(WindowWindow->Properties->GetHeight()));
			}

			//const uint32 textureID = Framebuffer->GetTextureRendererID();
			auto WindowSize = ImGui::GetWindowSize();
			//ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ static_cast<float>(WindowWindow->Properties->GetWidth()),static_cast<float>(WindowWindow->Properties->GetHeight()) }/*, ImVec2( 0, 1 ), ImVec2( 0, 1 )*/);
			ImGui::End();

			ImGui::Begin("Settings");
			/*IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Translation", &RenderingObjectList[0].Transform.GetLocation().x), "Testing", );


			IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Rotation", &RenderingObjectList[0].Transform.GetRotation().x, 1, -360000, 360000), "Rotation", );
			IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Scale", &RenderingObjectList[0].Transform.GetScale().x, 1, -360000, 360000), "Scale", );
			IMGUI_LEFT_LABEL(ImGui::DragFloat("##Angle", &TestTime, 0.01, -9, 9), "Angle", );

			IMGUI_LEFT_LABEL(ImGui::DragFloat3("##CameraTrans", &CameraTransform.GetTransform().GetLocation().x), "CameraTrans", );
			IMGUI_LEFT_LABEL(ImGui::Checkbox("##Ambient light", &bAmbientColor), "Ambient light");

			IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Diffuse", &Material.GetDiffuse().x, 0.01, -1, 1), "Diffuse", );
			IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Ambient", &Material.GetAmbient().x, 0.01, -1, 1), "Ambient", );
			IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Specluar", &Material.GetSpecular().x, 0.01, -1, 1), "Specluar", );
			IMGUI_LEFT_LABEL(ImGui::DragFloat("##Shiny", &Material.GetShininess(), 1, 256, 2), "Shiny", );


			IMGUI_LEFT_LABEL(ImGui::DragFloat3("##CameraRotation", &CameraTransform.GetTransform().GetRotation().x, 1, -360000, 360000), "CameraRotation", );

			IMGUI_LEFT_LABEL(ImGui::DragFloat3("##CameraScale", &CameraTransform.GetTransform().GetScale().x, 1, -360000, 360000), "CameraScale", );
			IMGUI_LEFT_LABEL(ImGui::DragFloat4("##ObjectColor", &Color.r, 0.01, -1, 1), "ObjectColor", );
			ImGui::ColorPicker4("Light Color", &GlobalLight.GetLightColor().r);*/
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			//ImGui::DragFloat3( "Translation", &Translation.x);
			ImGui::End();
			//    ImGui::End();

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

		Properties = std::make_unique<WindowsProperties>(WindowsProperties(ERenderingAPI::OpenGL, 1020, 1440, "Kaar Engine V 0.0.0.1"));
		WindowWindow = std::make_unique < WindowsWindow>(*Properties);
		Init();

		//	PrintCurrentMemoryUsage();

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

		{
			SCOPED_TIMER("Engine Loop");
#if GUI
			 //Framebuffer->BindBuffer();
			glfwSwapBuffers(WindowWindow->GetCurrentWindow());

			/* Poll for and process events */
			glfwPollEvents();
#endif
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