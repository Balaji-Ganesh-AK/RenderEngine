#include "FRenderingSystem.h"
#include "WindowsWindow.h"
#include "glm/gtx/transform.hpp"


#define IMGUI_LEFT_LABEL(func, label, code) ImGui::TextUnformatted(label);ImGui::NextColumn(); ImGui::SameLine(); ImGui::SetNextItemWidth(-1);if(func) { code } ImGui::NextColumn()

//#define IMGUI_LEFT_LABEL(func, label, code) ImGui::TextUnformatted(label); ImGui::NextColumn(); ImGui::SetNextItemWidth(-1); if(func) { code } ImGui::NextColumn();

using namespace KREngine;

FRenderingSystem::FRenderingSystem( WindowsWindow * window ): WorldProjection()
{
	WindowWindow = window;

	FRenderingObject RO;

	RO.VertexArray.reset(FVertexArray::Create());

	RO.VertexBufferData.reset(FVertexBuffer::CreateVertexBuffer(pos, sizeof(pos) / sizeof(float)));
	RO.IndexBufferData.reset(FIndexBuffer::CreateIndexBuffer(indices, sizeof(indices) / sizeof(unsigned int)));
	RO.Texture2D.reset(FTexture2D::Create(DefaultTexture));
	VertexBufferLayout layout{
		BufferElement{"v_Pos", EShaderDataType::FVec3, true},
		BufferElement{"v_Color", EShaderDataType::FVec3, true},
		BufferElement{"v_Texture", EShaderDataType::FVec2, true},
	};
	RO.VertexArray->SetLayOut(layout);
	RO.VertexArray->BindBufferLayout();
	RO.Shader.reset(FShader::CreateShader(DefaultVertexShaderPath, DefaultFragmentShaderPath));
	RenderingObjectList.emplace_back(RO);


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	//FRenderingObject RO1;

	//RO1.VertexArray.reset( FVertexArray::Create() );
	//RO1.VertexBufferData.reset( FVertexBuffer::CreateVertexBuffer( testpos, sizeof( testpos ) / sizeof( float ) ) );
	//RO1.IndexBufferData.reset( FIndexBuffer::CreateIndexBuffer( indices, sizeof( indices ) / sizeof( unsigned int ) ) );
	//VertexBufferLayout layout1{
	// BufferElement{"v_Pos",EShaderDataType::FVec2,true},
	// BufferElement{"v_Color",EShaderDataType::FVec3,true}
	//};
	//RO1.VertexArray->SetLayOut( layout1 );
	//RO1.VertexArray->BindBufferLayout();
	//RO1.Shader.reset( FShader::CreateShader( DefaultVertexShaderPath, DefaultFragmentShaderPath ) );
	//RenderingObjectList.emplace_back( RO1 );
	//

	Framebuffer.reset(FFrameBuffer::CreateFrameBuffer(WindowWindow->Properties->GetWidth(),
	                                                  WindowWindow->Properties->GetHeight()));
	glfwSwapInterval(0);
}

FRenderingSystem::~FRenderingSystem()
{
	
}

void FRenderingSystem::GUIInit()
{
    const char* glsl_version = "#version 130";
    // Setup Dear ImGui context

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); ( void ) io;
	io.IniFilename = NULL;
	//io.IniFilename = nullptr;
	ImGui::LoadIniSettingsFromDisk( "../Config/Imgui.ini" );
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGuiStyle* Style = &ImGui::GetStyle();
	Style->WindowPadding = ImVec2( 15, 15 );
    Style->WindowRounding = 5.0f;
    Style->FramePadding = ImVec2( 5, 5 );
    Style->FrameRounding = 4.0f;
    Style->ItemSpacing = ImVec2( 12, 8 );
    Style->ItemInnerSpacing = ImVec2( 8, 6 );
    Style->IndentSpacing = 25.0f;
    Style->ScrollbarSize = 15.0f;
    Style->ScrollbarRounding = 9.0f;
    Style->GrabMinSize = 5.0f;
    Style->GrabRounding = 3.0f;


    if (0)
    {
	    Style->Colors [ImGuiCol_Text] = ImVec4( 0.00f, 0.00f, 0.00f, 1.00f );
	    Style->Colors [ImGuiCol_TextDisabled] = ImVec4( 0.60f, 0.60f, 0.60f, 1.00f );
	    //Style->Colors [ImGuiCol_TextHovered] = ImVec4( 1.00f, 1.00f, 1.00f, 1.00f );
	    //Style->Colors [ImGuiCol_TextActive] = ImVec4( 1.00f, 1.00f, 0.00f, 1.00f );
	    Style->Colors [ImGuiCol_WindowBg] = ImVec4( 0.94f, 0.94f, 0.94f, 1.00f );
	    // Style->Colors [ImGuiCol_ChildWindowBg] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	    Style->Colors [ImGuiCol_Border] = ImVec4( 0.00f, 0.00f, 0.00f, 0.39f );
	    Style->Colors [ImGuiCol_BorderShadow] = ImVec4( 1.00f, 1.00f, 1.00f, 0.10f );
	    Style->Colors [ImGuiCol_FrameBg] = ImVec4( 1.00f, 1.00f, 1.00f, 1.00f );
	    Style->Colors [ImGuiCol_FrameBgHovered] = ImVec4( 0.26f, 0.59f, 0.98f, 0.40f );
	    Style->Colors [ImGuiCol_FrameBgActive] = ImVec4( 0.26f, 0.59f, 0.98f, 0.67f );
	    Style->Colors [ImGuiCol_TitleBg] = ImVec4( 0.96f, 0.96f, 0.96f, 1.00f );
	    Style->Colors [ImGuiCol_TitleBgCollapsed] = ImVec4( 1.00f, 1.00f, 1.00f, 0.51f );
	    Style->Colors [ImGuiCol_TitleBgActive] = ImVec4( 0.82f, 0.82f, 0.82f, 1.00f );
	    Style->Colors [ImGuiCol_MenuBarBg] = ImVec4( 0.86f, 0.86f, 0.86f, 1.00f );
	    Style->Colors [ImGuiCol_ScrollbarBg] = ImVec4( 0.98f, 0.98f, 0.98f, 0.53f );
	    Style->Colors [ImGuiCol_ScrollbarGrab] = ImVec4( 0.69f, 0.69f, 0.69f, 0.80f );
	    Style->Colors [ImGuiCol_ScrollbarGrabHovered] = ImVec4( 0.49f, 0.49f, 0.49f, 0.80f );
	    Style->Colors [ImGuiCol_ScrollbarGrabActive] = ImVec4( 0.49f, 0.49f, 0.49f, 1.00f );
	    // Style->Colors [ImGuiCol_ComboBg] = ImVec4( 0.86f, 0.86f, 0.86f, 0.99f );
	    Style->Colors [ImGuiCol_CheckMark] = ImVec4( 0.26f, 0.59f, 0.98f, 1.00f );
	    Style->Colors [ImGuiCol_SliderGrab] = ImVec4( 0.26f, 0.59f, 0.98f, 0.78f );
	    Style->Colors [ImGuiCol_SliderGrabActive] = ImVec4( 0.26f, 0.59f, 0.98f, 1.00f );
	    Style->Colors [ImGuiCol_Button] = ImVec4( 0.26f, 0.59f, 0.98f, 0.40f );
	    Style->Colors [ImGuiCol_ButtonHovered] = ImVec4( 0.26f, 0.59f, 0.98f, 1.00f );
	    Style->Colors [ImGuiCol_ButtonActive] = ImVec4( 0.06f, 0.53f, 0.98f, 1.00f );
	    Style->Colors [ImGuiCol_Header] = ImVec4( 0.26f, 0.59f, 0.98f, 0.31f );
	    Style->Colors [ImGuiCol_HeaderHovered] = ImVec4( 0.26f, 0.59f, 0.98f, 0.80f );
	    Style->Colors [ImGuiCol_HeaderActive] = ImVec4( 0.26f, 0.59f, 0.98f, 1.00f );
	    // Style->Colors [ImGuiCol_Column] = ImVec4( 0.39f, 0.39f, 0.39f, 1.00f );
	    //Style->Colors [ImGuiCol_ColumnHovered] = ImVec4( 0.26f, 0.59f, 0.98f, 0.78f );
	    //Style->Colors [ImGuiCol_ColumnActive] = ImVec4( 0.26f, 0.59f, 0.98f, 1.00f );
	    Style->Colors [ImGuiCol_ResizeGrip] = ImVec4( 1.00f, 1.00f, 1.00f, 0.00f );
	    Style->Colors [ImGuiCol_ResizeGripHovered] = ImVec4( 0.26f, 0.59f, 0.98f, 0.67f );
	    Style->Colors [ImGuiCol_ResizeGripActive] = ImVec4( 0.26f, 0.59f, 0.98f, 0.95f );
	    //Style->Colors [ImGuiCol_CloseButton] = ImVec4( 0.59f, 0.59f, 0.59f, 0.50f );
	    //Style->Colors [ImGuiCol_CloseButtonHovered] = ImVec4( 0.98f, 0.39f, 0.36f, 1.00f );
	    //Style->Colors [ImGuiCol_CloseButtonActive] = ImVec4( 0.98f, 0.39f, 0.36f, 1.00f );
	    Style->Colors [ImGuiCol_PlotLines] = ImVec4( 0.39f, 0.39f, 0.39f, 1.00f );
	    Style->Colors [ImGuiCol_PlotLinesHovered] = ImVec4( 1.00f, 0.43f, 0.35f, 1.00f );
	    Style->Colors [ImGuiCol_PlotHistogram] = ImVec4( 0.90f, 0.70f, 0.00f, 1.00f );
	    Style->Colors [ImGuiCol_PlotHistogramHovered] = ImVec4( 1.00f, 0.60f, 0.00f, 1.00f );
	    Style->Colors [ImGuiCol_TextSelectedBg] = ImVec4( 0.26f, 0.59f, 0.98f, 0.35f );
	    //Style->Colors [ImGuiCol_TooltipBg] = ImVec4( 1.00f, 1.00f, 1.00f, 0.94f );
	    // Style->Colors [ImGuiCol_ModalWindowDarkening] = ImVec4( 0.20f, 0.20f, 0.20f, 0.35f );
    }
    if (1)
	{
        auto& colors = ImGui::GetStyle().Colors;
        colors [ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

        // Headers
        colors [ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors [ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors [ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Buttons
        colors [ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors [ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors [ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Frame BG
        colors [ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors [ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors [ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Tabs
        colors [ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors [ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
        colors [ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
        colors [ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors [ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

        // Title
        colors [ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors [ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors [ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}
    if(0)
    {
	    Style->Colors [ImGuiCol_Text] = ImVec4( 0.80f, 0.80f, 0.83f, 1.00f );
	    Style->Colors [ImGuiCol_TextDisabled] = ImVec4( 0.24f, 0.23f, 0.29f, 1.00f );
	    Style->Colors [ImGuiCol_WindowBg] = ImVec4( 0.06f, 0.05f, 0.07f, 1.00f );
	    // Style->Colors [ImGuiCol_ChildWindowBg] = ImVec4( 0.07f, 0.07f, 0.09f, 1.00f );
	    Style->Colors [ImGuiCol_PopupBg] = ImVec4( 0.07f, 0.07f, 0.09f, 1.00f );
	    Style->Colors [ImGuiCol_Border] = ImVec4( 0.80f, 0.80f, 0.83f, 0.88f );
	    Style->Colors [ImGuiCol_BorderShadow] = ImVec4( 0.92f, 0.91f, 0.88f, 0.00f );
	    Style->Colors [ImGuiCol_FrameBg] = ImVec4( 0.10f, 0.09f, 0.12f, 1.00f );
	    Style->Colors [ImGuiCol_FrameBgHovered] = ImVec4( 0.24f, 0.23f, 0.29f, 1.00f );
	    Style->Colors [ImGuiCol_FrameBgActive] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
	    Style->Colors [ImGuiCol_TitleBg] = ImVec4( 0.10f, 0.09f, 0.12f, 1.00f );
	    Style->Colors [ImGuiCol_TitleBgCollapsed] = ImVec4( 1.00f, 0.98f, 0.95f, 0.75f );
	    Style->Colors [ImGuiCol_TitleBgActive] = ImVec4( 0.07f, 0.07f, 0.09f, 1.00f );
	    Style->Colors [ImGuiCol_MenuBarBg] = ImVec4( 0.10f, 0.09f, 0.12f, 1.00f );
	    Style->Colors [ImGuiCol_ScrollbarBg] = ImVec4( 0.10f, 0.09f, 0.12f, 1.00f );
	    Style->Colors [ImGuiCol_ScrollbarGrab] = ImVec4( 0.80f, 0.80f, 0.83f, 0.31f );
	    Style->Colors [ImGuiCol_ScrollbarGrabHovered] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
	    Style->Colors [ImGuiCol_ScrollbarGrabActive] = ImVec4( 0.06f, 0.05f, 0.07f, 1.00f );
	    // Style->Colors [ImGuiCol_ComboBg] = ImVec4( 0.19f, 0.18f, 0.21f, 1.00f );
	    Style->Colors [ImGuiCol_CheckMark] = ImVec4( 0.80f, 0.80f, 0.83f, 0.31f );
	    Style->Colors [ImGuiCol_SliderGrab] = ImVec4( 0.80f, 0.80f, 0.83f, 0.31f );
	    Style->Colors [ImGuiCol_SliderGrabActive] = ImVec4( 0.06f, 0.05f, 0.07f, 1.00f );
	    Style->Colors [ImGuiCol_Button] = ImVec4( 0.10f, 0.09f, 0.12f, 1.00f );
	    Style->Colors [ImGuiCol_ButtonHovered] = ImVec4( 0.24f, 0.23f, 0.29f, 1.00f );
	    Style->Colors [ImGuiCol_ButtonActive] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
	    Style->Colors [ImGuiCol_Header] = ImVec4( 0.10f, 0.09f, 0.12f, 1.00f );
	    Style->Colors [ImGuiCol_HeaderHovered] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
	    Style->Colors [ImGuiCol_HeaderActive] = ImVec4( 0.06f, 0.05f, 0.07f, 1.00f );
	    // Style->Colors [ImGuiCol_Column] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
	    //// Style->Colors [ImGuiCol_ColumnHovered] = ImVec4( 0.24f, 0.23f, 0.29f, 1.00f );
	    // Style->Colors [ImGuiCol_ColumnActive] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
	    Style->Colors [ImGuiCol_ResizeGrip] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	    Style->Colors [ImGuiCol_ResizeGripHovered] = ImVec4( 0.56f, 0.56f, 0.58f, 1.00f );
	    Style->Colors [ImGuiCol_ResizeGripActive] = ImVec4( 0.06f, 0.05f, 0.07f, 1.00f );
	    // Style->Colors [ImGuiCol_CloseButton] = ImVec4( 0.40f, 0.39f, 0.38f, 0.16f );
	    /// Style->Colors [ImGuiCol_CloseButtonHovered] = ImVec4( 0.40f, 0.39f, 0.38f, 0.39f );
	    //  Style->Colors [ImGuiCol_CloseButtonActive] = ImVec4( 0.40f, 0.39f, 0.38f, 1.00f );
	    Style->Colors [ImGuiCol_PlotLines] = ImVec4( 0.40f, 0.39f, 0.38f, 0.63f );
	    Style->Colors [ImGuiCol_PlotLinesHovered] = ImVec4( 0.25f, 1.00f, 0.00f, 1.00f );
	    Style->Colors [ImGuiCol_PlotHistogram] = ImVec4( 0.40f, 0.39f, 0.38f, 0.63f );
	    Style->Colors [ImGuiCol_PlotHistogramHovered] = ImVec4( 0.25f, 1.00f, 0.00f, 1.00f );
	    Style->Colors [ImGuiCol_TextSelectedBg] = ImVec4( 0.25f, 1.00f, 0.00f, 0.43f );
	    //   Style->Colors [ImGuiCol_ModalWindowDarkening] = ImVec4( 1.00f, 0.98f, 0.95f, 0.73f );
    }
	
  //  ImGui::StyleColorsDark();


    ImGui_ImplGlfw_InitForOpenGL( FRenderingSystem::GetGFLWWindow(), true );
    ImGui_ImplOpenGL3_Init( glsl_version );



   /* std::vector<int> test( 100000, 10 );

    {
        UTimerLog Test( "TestingLoop" );
        for ( int x : test )
        {
			x++;
            Logger::Verbose( "Testing %d", x );
        }

    	
    }*/
}

void FRenderingSystem::GUIStop()
{
	ImGui::SaveIniSettingsToDisk( "../Config/Imgui.ini" );
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

GLFWwindow* FRenderingSystem::GetGFLWWindow() const
{
	//return nullptr;
	return WindowWindow->GetCurrentWindow();
}


void FRenderingSystem::GUIRun()
{
    Framebuffer->UnBindBuffer();
    

    ImGui::Begin( "ScreenPort" );
    if ( test != WindowWindow->Properties->GetWidth() )
    {
        test = WindowWindow->Properties->GetWidth();
        Framebuffer->OnWindowResize( static_cast< float >( WindowWindow->Properties->GetWidth() ), static_cast< float >( WindowWindow->Properties->GetHeight() ) );
    }

    const uint32 textureID = Framebuffer->GetTextureRendererID();
    ImGui::Image( reinterpret_cast< void* >( textureID ), ImVec2{ static_cast< float >( WindowWindow->Properties->GetWidth() ),static_cast< float >( WindowWindow->Properties->GetHeight() ) } );
    ImGui::End();

    ImGui::Begin( "Settings" );
    IMGUI_LEFT_LABEL( ImGui::DragFloat3( "##Translation", &Transform.GetLocation().x ), "Testing", );

    IMGUI_LEFT_LABEL( ImGui::DragFloat3( "##Rotation", &Transform.GetRotation().x, 1, -360000, 360000 ), "Rotation", );
    IMGUI_LEFT_LABEL( ImGui::DragFloat3( "##Scale", &Transform.GetScale().x, 1, -360000, 360000 ), "Scale", );

    IMGUI_LEFT_LABEL( ImGui::DragFloat3( "##CameraTrans", &CameraTransform.GetLocation().x ), "CameraTrans", );

    IMGUI_LEFT_LABEL( ImGui::DragFloat3( "##CameraRotation", &CameraTransform.GetRotation().x, 1, -360000, 360000 ), "CameraRotation", );
    IMGUI_LEFT_LABEL( ImGui::DragFloat3( "##CameraScale", &CameraTransform.GetScale().x, 1, -360000, 360000 ), "CameraScale", );
    IMGUI_LEFT_LABEL( ImGui::DragFloat4( "##ObjectColor", &Color.r, 0.01, -1, 1 ), "GlobalLight", );
	ImGui::ColorPicker4( "Global Light",&GlobalLight.GetLightColor().r);
    ImGui::Text( "Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate );
    //ImGui::DragFloat3( "Translation", &Translation.x);
    ImGui::End();
//    ImGui::End();



   
}


ERenderingAPI FRenderingSystem::GetRenderingAPI() const
{
	return RenderingAPI;
}

void FRenderingSystem::Init()
{
	WorldProjection = glm::perspective( glm::radians( 45.0f ), WindowWindow->Properties->GetWidth() / WindowWindow->Properties->GetHeight(), 0.1f, 100.0f );
}

void FRenderingSystem::Run()
{
	SCOPED_TIMER( "Rendering Loop" );
    GLFWwindow* window = WindowWindow->GetCurrentWindow();
#if GUI
    Framebuffer->BindBuffer();
#endif
	
    {
        /* Render here */
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glfwPollEvents();

        int32 DrawCallCount{ 0 };
        //WorldProjection = glm::ortho( -Properties.GetWidth()/2, Properties.GetWidth()/2, -Properties.GetHeight()/2, Properties.GetHeight() / 2 ,-1.0f, 1.0f );
        WorldProjection = glm::perspective( glm::radians( 45.0f ), WindowWindow->Properties->GetWidth() / WindowWindow->Properties->GetHeight(), 0.1f, 100.0f );

        glm::mat4 ViewProjection = glm::translate( glm::mat4( 1.0f ), CameraTransform.GetLocation().AsGLMVec3() );
        ViewProjection = glm::rotate( ViewProjection, glm::radians( CameraTransform.GetRotation().x ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
        ViewProjection = glm::rotate( ViewProjection, glm::radians( CameraTransform.GetRotation().y ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
        ViewProjection = glm::rotate( ViewProjection, glm::radians( CameraTransform.GetRotation().z ), glm::vec3( 0.0f, 0.0f, 1.0f ) );
        glm::mat4 ModelProjection= glm::mat4( 1.0f );
        ModelProjection = glm::translate( ModelProjection, Transform.GetLocation().AsGLMVec3() );
        ModelProjection = glm::rotate( ModelProjection, glm::radians( Transform.GetRotation().x ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
        ModelProjection = glm::rotate( ModelProjection, glm::radians( Transform.GetRotation().y ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
        ModelProjection = glm::rotate( ModelProjection, glm::radians( Transform.GetRotation().z ), glm::vec3( 0.0f, 0.0f, 1.0f ) );
        ModelProjection = glm::scale( ModelProjection, Transform.GetScale().AsGLMVec3() );

        for ( const FRenderingObject& RO : RenderingObjectList )
        {
            RO.Shader->BindShader();
            RO.Texture2D->BindTexture();
            // RO.Shader->SetUniform4f( "u_Color", vec4( clear_color.x, clear_color.y, clear_color.z, clear_color.w ) );
            RO.Shader->SetUniform4f( "u_ObjectColor",vec4(Color.r,Color.g,Color.b, Color.a) );
            RO.Shader->SetUniform4f( "u_Color",vec4( GlobalLight.GetShaderColor().r, GlobalLight.GetShaderColor().g, GlobalLight.GetShaderColor().b, GlobalLight.GetShaderColor().a) );
            RO.Shader->SetUniformMat4( "u_WorldProjection", WorldProjection * ViewProjection * ModelProjection );
            RO.VertexArray->BindBuffer();

            DrawCallCount++;
            // 3 vertex two triangles.
            ( glDrawElements( GL_TRIANGLES, sizeof( indices ) / sizeof( uint32 ), GL_UNSIGNED_INT, nullptr ) );

            // glDrawArrays( GL_TRIANGLES, 0, 36 );
        }
        
       // KREngine::Logger::Verbose( "Draw Call Count: %d", DrawCallCount );

        /* Swap front and back buffers */
        glfwSwapBuffers( window );

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void FRenderingSystem::Stop()
{
    glfwTerminate();
}
