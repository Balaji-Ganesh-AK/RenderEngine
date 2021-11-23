#include "utility/Pch.h"
#include <crtdbg.h>

#include "Systems/Systems.h"
#include "RenderingSystem/FRenderingSystem.h"
//#include "utility/Globals.h"



using namespace KREngine;

	int main( void )
	{
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
		{
			
			
			SystemManager* GameSystems = new SystemManager();

			//PrintCurrentMemoryUsage();
			GameSystems->Init();
		//	PrintCurrentMemoryUsage();
			GameSystems->InitGUI();

			int i = 10000000;

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

			
			
			while ( GameSystems->GetRenderingSystem()->GetWindowsWindow()->IsActive() )
			{
				{

					SCOPED_TIMER( "Systems Loop");
					GameSystems->Run();
					GameSystems->RunGUI();

				}
			}
			GameSystems->StopGUI();
			GameSystems->Stop();
			delete GameSystems;
			Logger::Verbose( " Engine Shuting down!" );
		}
		_CrtDumpMemoryLeaks();
		

	}



//
//void WindowResizeEvent(GLFWwindow* window, int width, int height)
//{
//    glViewport( 0, 0, width, height );
//}
//
//void InputHandler(GLFWwindow* window)
//{
//    if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
//        glfwSetWindowShouldClose( window, true );
//}
//
//
//
//void GLClearError()
//{
//	while(glGetError()!=GL_NO_ERROR)
//	{
//		
//	}
//}
//
//void GLCheckError()
//{
//	while(GLenum error = glGetError())
//	{
//        std::cout << "Open GL error" << error << std::endl;
//	}
//}
