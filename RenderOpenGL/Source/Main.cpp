#pragma once


#include "Main.h"


#include "utility/Pch.h"



#include "RenderingSystem/RenderingSystem.h"
#include "RenderingSystem/WindowsWindow.h"
#include "utility/LogTimer.h"


int main( void )
{
	KREngine::RenderingSystem::GetInstance()->Init();

	

	
	while ( true )
	{



		
		{
			UTimerLog("Rendering Loop");
			KREngine::RenderingSystem::GetInstance()->Run();
		}
	}



	//glfwTerminate();
	KREngine::RenderingSystem::GetInstance()->Stop();
	
   
}


void WindowResizeEvent(GLFWwindow* window, int width, int height)
{
    glViewport( 0, 0, width, height );
}

void InputHandler(GLFWwindow* window)
{
    if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
        glfwSetWindowShouldClose( window, true );
}



void GLClearError()
{
	while(glGetError()!=GL_NO_ERROR)
	{
		
	}
}

void GLCheckError()
{
	while(GLenum error = glGetError())
	{
        std::cout << "Open GL error" << error << std::endl;
	}
}
