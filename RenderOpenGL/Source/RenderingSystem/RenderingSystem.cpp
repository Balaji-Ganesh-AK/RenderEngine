
#include "RenderingSystem.h"
#include "WindowsWindow.h"

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
    VertexBufferLayout layout{
	  BufferElement{"v_Pos",EShaderDataType::FVec2,false},
	  //BufferElement{"v_Color",EShaderDataType::FVec3,false}
    };
    RO.VertexArray->SetLayOut( layout );
    RO.VertexArray->BindBufferLayout();
    RO.Shader.reset(FShader::CreateShader( DefaultVertexShaderPath, DefaultFragmentShaderPath ));
    RenderingObjectList.emplace_back( RO );


   /* FRenderingObject RO1;

    RO1.VertexArray.reset( FVertexArray::Create() );
    RO1.VertexBufferData.reset( FVertexBuffer::CreateVertexBuffer( pos, sizeof( pos ) / sizeof( float ) ) );
    RO1.IndexBufferData.reset( FIndexBuffer::CreateIndexBuffer( indices, sizeof( indices ) / sizeof( unsigned int ) ) );

    RO1.VertexArray->BindBufferLayout();
    RO1.Shader.reset( FShader::CreateShader( DefaultVertexShaderPath, DefaultFragmentShaderPath ) );
    RenderingObjectList.emplace_back( RO1 );*/
}

void RenderingSystem::Init()
{
  
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
           // RO.Shader->SetUniform4f( "u_Color", vec4( Color.r, Color.g, Color.b, Color.a ) );
            RO.VertexArray->BindBuffer();
            DrawCallCount++;
            ( glDrawElements( GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr ) );
        }

        std::cout << "Draw Call Count:" << DrawCallCount<<std::endl;

        /* Swap front and back buffers */
        glfwSwapBuffers( window );

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void RenderingSystem::Stop()
{

    glfwTerminate();
    
}
