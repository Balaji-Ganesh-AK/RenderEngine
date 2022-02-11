#include "FRenderingSystem.h"

#include "GameManager.h"
#include "WindowsWindow.h"
#include "Entity/Components/TransformComponent.h"
#include "glm/gtx/transform.hpp"




using namespace KREngine;

//FRenderingSystem::FRenderingSystem( WindowsWindow * window ): WorldProjection()
//{
//	WindowWindow = window;
//
//	FRenderingObject RO;
//	FRenderingObject RO1;
//
//	RO.VertexArray.reset(FVertexArray::Create());
//	RO.Mesh = &CubeMesh;
//	RO.VertexBufferData.reset(FVertexBuffer::CreateVertexBuffer( CubeMesh.Positions, sizeof( CubeMesh.Positions ) / sizeof(float)));
//	RO.IndexBufferData.reset(FIndexBuffer::CreateIndexBuffer( CubeMesh.Indices, sizeof( CubeMesh.Indices ) / sizeof(unsigned int)));
//
//	VertexBufferLayout layout{
//		BufferElement{"v_Pos", EShaderDataType::FVec3, true},
//		BufferElement{"v_Texture", EShaderDataType::FVec2, true},
//		BufferElement{"v_Normal", EShaderDataType::FVec3, true},
//
//		//BufferElement{"v_Normal", EShaderDataType::FVec3, true},
//	};
//	RO.VertexArray->SetLayOut(layout);
//	RO.VertexArray->BindBufferLayout();
//	RO.Shader.reset(FShader::CreateShader(DefaultVertexShaderPath, DefaultFragmentShaderPath));
//
//	int slot = 0;
//	RO.Material.Init( RO.Shader, slot);
//	RenderingObjectList.emplace_back(RO);
//
//
//
//
//
//	RO1.VertexArray.reset( FVertexArray::Create() );
//
//	RO1.VertexBufferData.reset( FVertexBuffer::CreateVertexBuffer( CubeMesh.Positions, sizeof( CubeMesh.Positions ) / sizeof( float ) ) );
//	RO1.IndexBufferData.reset( FIndexBuffer::CreateIndexBuffer( CubeMesh.Indices, sizeof( CubeMesh.Indices ) / sizeof( unsigned int ) ) );
//	
//	VertexBufferLayout layout1{
//		BufferElement{"v_Pos", EShaderDataType::FVec3, true},
//		BufferElement{"v_Texture", EShaderDataType::FVec2, true},
//		BufferElement{"v_Normal", EShaderDataType::FVec3, true},
//		//BufferElement{"v_Normal", EShaderDataType::FVec3, true},
//	};
//	RO1.VertexArray->SetLayOut( layout1 );
//	RO1.VertexArray->BindBufferLayout();
//	RO1.Shader.reset( FShader::CreateShader( DefaultVertexShaderPath, DefaultFragmentShaderPath ) );
//	int slot1 = 0;
//	RO1.Material.Init( RO1.Shader, slot1);
//	RO1.Mesh = &CubeMesh;
//	
//	RenderingObjectList.emplace_back( RO1 );
//	
//
//	
//	
//	
//	//glEnable( GL_CULL_FACE );
//	//glFrontFace( GL_CW );
//	//glCullFace( GL_BACK );
//	//FRenderingObject RO1;
//
//	//RO1.VertexArray.reset( FVertexArray::Create() );
//	//RO1.VertexBufferData.reset( FVertexBuffer::CreateVertexBuffer( testpos, sizeof( testpos ) / sizeof( float ) ) );
//	//RO1.IndexBufferData.reset( FIndexBuffer::CreateIndexBuffer( indices, sizeof( indices ) / sizeof( unsigned int ) ) );
//	//VertexBufferLayout layout1{
//	// BufferElement{"v_Pos",EShaderDataType::FVec2,true},
//	// BufferElement{"v_Color",EShaderDataType::FVec3,true}
//	//};
//	//RO1.VertexArray->SetLayOut( layout1 );
//	//RO1.VertexArray->BindBufferLayout();
//	//RO1.Shader.reset( FShader::CreateShader( DefaultVertexShaderPath, DefaultFragmentShaderPath ) );
//	//RenderingObjectList.emplace_back( RO1 );
//	//
//
//	
//
//
//	//Post init
////	Material.Init();
//
//}
//
//FRenderingSystem::~FRenderingSystem()
//{
//	
//}
//
//void FRenderingSystem::GUIInit()
//{
//  
//
//
//   /* std::vector<int> test( 100000, 10 );
//
//    {
//        UTimerLog Test( "TestingLoop" );
//        for ( int x : test )
//        {
//			x++;
//            Logger::Verbose( "Testing %d", x );
//        }
//
//    	
//    }*/
//}
//
//void FRenderingSystem::GUIStop()
//{
//	
//}
//
//GLFWwindow* FRenderingSystem::GetGFLWWindow() const
//{
//	//return nullptr;
//	return WindowWindow->GetCurrentWindow();
//}
//
//
//void FRenderingSystem::GUIRun()
//{
//    
//}
//
//
//ERenderingAPI FRenderingSystem::GetRenderingAPI() const
//{
//	return RenderingAPI;
//}
//
//void FRenderingSystem::Init()
//{
//	
//}
//
//void FRenderingSystem::Run()
//{
//	SCOPED_TIMER( "Rendering Loop" );
//    GLFWwindow* window = WindowWindow->GetCurrentWindow();
//
//	
//    {
//        /* Render here */
//        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        //glfwPollEvents();
//
//        int32 DrawCallCount{ 0 };
//        //WorldProjection = glm::ortho( -Properties.GetWidth()/2, Properties.GetWidth()/2, -Properties.GetHeight()/2, Properties.GetHeight() / 2 ,-1.0f, 1.0f );
//        WorldProjection = glm::perspective( glm::radians(45.0f ), WindowWindow->Properties->GetWidth() / WindowWindow->Properties->GetHeight(), 0.1f, 100.0f );
//
//        glm::mat4 ViewProjection /*= glm::translate( glm::mat4( 1.0f ) )*/;
//
//		float camX = sin( glfwGetTime() ) * 10.0f;
//		float camY = cos( glfwGetTime() ) * 10.0f;
//		//CameraTransform.GetTransform().SetLocation( FVector( camX, 0.0, camY ) );
//		ViewProjection = glm::lookAt( CameraTransform.GetTransform().GetLocation().AsGLMVec3(), glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec3( 0.0f, -1.0f, 0.0f ) );
//		//ViewProjection = glm::lookAt(glm::vec3(camX,0.0, camY), glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec3( 0.0f, 1.0f, 0.0f ) );
//        /*ViewProjection = glm::rotate( ViewProjection, glm::radians( CameraTransform.GetGLMTransform().GetRotation().x ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
//        ViewProjection = glm::rotate( ViewProjection, glm::radians( CameraTransform.GetGLMTransform().GetRotation().y ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
//        ViewProjection = glm::rotate( ViewProjection, glm::radians( CameraTransform.GetGLMTransform().GetRotation().z ), glm::vec3( 0.0f, 0.0f, 1.0f ) );*/
//		FVector tempLocation = RenderingObjectList [1].Transform.GetLocation();
//		//TestTime += 0.000;
//		tempLocation.x = RenderingObjectList [0].Transform.GetLocation().x + cos( TestTime ) * 2;
//		tempLocation.z = RenderingObjectList [0].Transform.GetLocation().z + sin( TestTime ) * 2;
//		RenderingObjectList [1].Transform.SetLocation( tempLocation );
//		/*Needs clean up*/
//		GlobalLight.SetUseAmbientColor( bAmbientColor );
//		//auto color = Color * GlobalLight.GetShaderColor();
//		//RenderingObjectList [0].Shader->BindShader();
//		//RenderingObjectList[0].Shader->SetUniform4f( "u_ObjectColor", vec4( Color.r, Color.g, Color.b, Color.a ) );
//		//RenderingObjectList[0].Shader->SetUniformF( "material.Shininess", RenderingObjectList [0].Material.GetShininess() );
//		//RenderingObjectList[0].Shader->SetUniform4f( "u_LightColor",  vec4( GlobalLight.GetShaderColor().r, GlobalLight.GetShaderColor().g, GlobalLight.GetShaderColor().b, GlobalLight.GetShaderColor().a ) );
//		//RenderingObjectList[0].Shader->SetUniformInt( "u_Light", 1 );
//		//RenderingObjectList [0].Shader->UnBindShader();
//		//RenderingObjectList [1].Shader->BindShader();
//	
//		//RenderingObjectList[1].Shader->SetUniform4f( "u_ObjectColor", vec4( GlobalLight.GetShaderColor().r, GlobalLight.GetShaderColor().g, GlobalLight.GetShaderColor().b, GlobalLight.GetShaderColor().a ) );
//		//RenderingObjectList [1].Shader->SetUniformInt( "u_Light", 0 );
//		//RenderingObjectList [1].Shader->UnBindShader();
//        for ( const FRenderingObject& RO : RenderingObjectList )
//        {
//			int slot = 0;
//            RO.Shader->BindShader();
//			RO.Material.Bind(slot);
//			glm::mat4 ModelProjection = glm::mat4( 1.0f );
//			ModelProjection = glm::translate( ModelProjection, RO.Transform.GetLocation().AsGLMVec3() );
//			ModelProjection = glm::rotate( ModelProjection, glm::radians(RO.Transform.GetRotation().x ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
//			ModelProjection = glm::rotate( ModelProjection, glm::radians(RO.Transform.GetRotation().y ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
//			ModelProjection = glm::rotate( ModelProjection, glm::radians(RO.Transform.GetRotation().z ), glm::vec3( 0.0f, 0.0f, 1.0f ) );
//			ModelProjection = glm::scale( ModelProjection, RO.Transform.GetScale().AsGLMVec3() );
//            // RO.Shader->SetUniform4f( "u_Color", vec4( clear_color.x, clear_color.y, clear_color.z, clear_color.w ) );
//           //RO.Shader->SetUniform4f( "u_ObjectColor",vec4(Color.r,Color.g,Color.b, Color.a) );
//           // RO.Shader->SetUniform4f( "u_Color",vec4( GlobalLight.GetShaderColor().r, GlobalLight.GetShaderColor().g, GlobalLight.GetShaderColor().b, GlobalLight.GetShaderColor().a) );
//            RO.Shader->SetUniformMat4( "u_WorldProjection", WorldProjection * ViewProjection * ModelProjection );
//            RO.Shader->SetUniformMat4( "u_Model", /*ViewProjection**/ ModelProjection );
//            RO.Shader->SetUniform3f( "u_LightPos", RenderingObjectList[1].Transform.GetLocation());
//            RO.Shader->SetUniform3f( "u_CameraPos", CameraTransform.GetTransform().GetLocation());
//        	RO.Shader->SetUniform4f("u_ObjectColor", vec4(Color.r, Color.g, Color.b, Color.a));
//            RO.VertexArray->BindBuffer();
//
//            DrawCallCount++;
//            // 3 vertex two triangles.
//            ( glDrawElements( GL_TRIANGLES,  36, GL_UNSIGNED_INT, nullptr ) );
//
//            // glDrawArrays( GL_TRIANGLES, 0, 36 );
//        }
//
//        
//       // KREngine::Logger::Verbose( "Draw Call Count: %d", DrawCallCount );
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers( window );
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//}
//
//void FRenderingSystem::Stop()
//{
//    glfwTerminate();
//}
void FRenderingSystem::Init()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	/*Goes into camera component*/
	WorldProjection = glm::perspective(glm::radians(45.0f), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 100.0f);


	Shader.reset(FShader::CreateShader(DefaultVertexShaderPath, DefaultFragmentShaderPath));

	int slot = 0;
	Material.Init(Shader, slot);
	Framebuffer.reset(FFrameBuffer::CreateFrameBuffer(FApplication::Get().GetWindowsWindow()->Properties->GetWidth(),
		FApplication::Get().GetWindowsWindow()->Properties->GetHeight()));


}

void FRenderingSystem::Run()
{
#if GUI
	Framebuffer->BindBuffer();
#endif
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glfwPollEvents();
	
	  int32 DrawCallCount{ 0 };
	        //WorldProjection = glm::ortho( -Properties.GetWidth()/2, Properties.GetWidth()/2, -Properties.GetHeight()/2, Properties.GetHeight() / 2 ,-1.0f, 1.0f );
	WorldProjection = glm::perspective( glm::radians(45.0f ), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 100.0f );
	
	glm::mat4 ViewProjection /*= glm::translate( glm::mat4( 1.0f ) )*/;
	ViewProjection = glm::lookAt(CameraTransform.GetTransform().GetLocation().AsGLMVec3(), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));



	int slot = 0;
	Shader->BindShader();
	Material.Bind(slot);

	for(const FEntityHandle Entity : EntityHandles)
	{
		
		auto& static_mesh = EntityManager::GetComponent<FStaticMesh>(Entity);
		auto& transform = EntityManager::GetComponent<FTransformComponent>(Entity).Transform;
		glm::mat4 ModelProjection = glm::mat4(1.0f);
		ModelProjection = glm::translate(ModelProjection, transform.GetLocation().AsGLMVec3());
		ModelProjection = glm::rotate(ModelProjection, glm::radians(transform.GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
		ModelProjection = glm::rotate(ModelProjection, glm::radians(transform.GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
		ModelProjection = glm::rotate(ModelProjection, glm::radians(transform.GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
		ModelProjection = glm::scale(ModelProjection, transform.GetScale().AsGLMVec3());
		// Shader->SetUniform4f( "u_Color", vec4( clear_color.x, clear_color.y, clear_color.z, clear_color.w ) );
	   //Shader->SetUniform4f( "u_ObjectColor",vec4(Color.r,Color.g,Color.b, Color.a) );
	   // Shader->SetUniform4f( "u_Color",vec4( GlobalLight.GetShaderColor().r, GlobalLight.GetShaderColor().g, GlobalLight.GetShaderColor().b, GlobalLight.GetShaderColor().a) );
		Shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * ModelProjection);
		Shader->SetUniformMat4("u_Model", /*ViewProjection**/ ModelProjection);
		/*Shader->SetUniform3f("u_LightPos", RenderingObjectList[1].Transform.GetLocation());*/
		Shader->SetUniform3f("u_CameraPos", CameraTransform.GetTransform().GetLocation());
		Shader->SetUniform4f("u_ObjectColor", vec4(Color.r, Color.g, Color.b, Color.a));
		
		static_mesh.VertexArray->BindBuffer();

		DrawCallCount++;
		// 3 vertex two triangles.
		(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr));

		// glDrawArrays( GL_TRIANGLES, 0, 36 );
	}
	Framebuffer->UnBindBuffer();

	
}

void FRenderingSystem::Stop()
{
}

void FRenderingSystem::GUIInit()
{
}

void FRenderingSystem::GUIStop()
{
}

void FRenderingSystem::GUIRun()
{
	ImGui::Begin("ScreenPort");
	if (test != FApplication::Get().GetWindowsWindow()->Properties->GetWidth())
	{
		test = FApplication::Get().GetWindowsWindow()->Properties->GetWidth();
		Framebuffer->OnWindowResize(static_cast<float>(FApplication::Get().GetWindowsWindow()->Properties->GetWidth()), static_cast<float>(FApplication::Get().GetWindowsWindow()->Properties->GetHeight()));
	}

	const uint32 textureID = Framebuffer->GetTextureRendererID();
	auto WindowSize = ImGui::GetWindowSize();
	ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ static_cast<float>(FApplication::Get().GetWindowsWindow()->Properties->GetWidth()),static_cast<float>(FApplication::Get().GetWindowsWindow()->Properties->GetHeight()) }/*, ImVec2( 0, 1 ), ImVec2( 0, 1 )*/);
	ImGui::End();
}
