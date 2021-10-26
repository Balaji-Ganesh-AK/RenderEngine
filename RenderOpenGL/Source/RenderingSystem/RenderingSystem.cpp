
#include "RenderingSystem.h"
#include "WindowsWindow.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"

using namespace KREngine;




#pragma region  Globals
    RenderingSystem* RenderingSystem::Instance = new RenderingSystem();
#pragma endregion 
RenderingSystem::RenderingSystem()
{
    Properties = WindowsProperties::DefaultOpenGl();
    WindowWindow = WindowsWindow( Properties );
    FRenderingObject RO;

    RO.VertexArray.reset(FVertexArray::Create());

    RO.VertexBufferData.reset( FVertexBuffer::CreateVertexBuffer( pos, sizeof( pos )/ sizeof(float) ) );
    RO.IndexBufferData.reset( FIndexBuffer::CreateIndexBuffer( indices, sizeof( indices )  / sizeof( unsigned int ) ));
    RO.Texture2D.reset( FTexture2D::Create( DefaultTexture ) );
    VertexBufferLayout layout{
	  BufferElement{"v_Pos",EShaderDataType::FVec2,true},
	  BufferElement{"v_Color",EShaderDataType::FVec3,true},
	  BufferElement{"v_Texture",EShaderDataType::FVec2,true}
    };
    RO.VertexArray->SetLayOut( layout );
    RO.VertexArray->BindBufferLayout();
    RO.Shader.reset(FShader::CreateShader( DefaultVertexShaderPath, DefaultFragmentShaderPath ));
    RenderingObjectList.emplace_back( RO );



    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
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
}

void RenderingSystem::Init()
{

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    const char* glsl_version = "#version 130";
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); ( void ) io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL( KREngine::RenderingSystem::GetInstance()->GetGFLWWindow(), true );


    ImGui_ImplOpenGL3_Init( glsl_version );
}

void RenderingSystem::Run()
{
    GLFWwindow* window = WindowWindow.GetCurrentWindow();
   
    {
        /* Render here */
        glClear( GL_COLOR_BUFFER_BIT );

        Color.r += 0.001f;
        if ( Color.r > 0.9 )
        {
            Color.r = 0.1f;
        }
        Color.b += 0.001f;
        if ( Color.b > 0.9 )
        {
            Color.b = 0.1f;
        }
        Color.g += 0.001f;
        if ( Color.g > 0.9 )
        {
            Color.g = 0.1f;
        }

        int32 DrawCallCount {0};
    	
        for(const FRenderingObject& RO: RenderingObjectList)
        {
            RO.Shader->BindShader();
            RO.Texture2D->BindTexture();
            RO.Shader->SetUniform4f( "u_Color", vec4( clear_color.x, clear_color.y, clear_color.z, clear_color.w ) );
            RO.VertexArray->BindBuffer();
 
            DrawCallCount++;
            ( glDrawElements( GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr ) );
        }

        std::cout << "Draw Call Count:" << DrawCallCount<<std::endl;



        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin( "Hello, world!" );                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text( "This is some useful text." );               // Display some text (you can use a format strings too)
                ImGui::Checkbox( "Demo Window", &show_demo_window );      // Edit bools storing our window open/close state
                ImGui::Checkbox( "Another Window", &show_another_window );

                ImGui::SliderFloat( "float", &f, 0.0f, 1.0f );            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3( "clear color", ( float* ) &clear_color ); // Edit 3 floats representing a color

                if ( ImGui::Button( "Button" ) )                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text( "counter = %d", counter );

                ImGui::Text( "Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate );
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

        }
    	
        /* Swap front and back buffers */
        glfwSwapBuffers( window );

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void RenderingSystem::Stop()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    
}
