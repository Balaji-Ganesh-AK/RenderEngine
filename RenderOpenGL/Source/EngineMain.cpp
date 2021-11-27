

#include "Game.h"
#include "GameManager.h"
using namespace KREngine;

class TestGame: public FGame
{
public:
	TestGame() = default;
	virtual void Init() override{};
	virtual void Run() override{};
	virtual void Stop() override{};
	void Test() {};
};

	int main( void )
	{
		
		{
			FGameManager* Manager = new FGameManager();
			Manager->Init();
			Manager->Run();
			Manager->End();

			delete Manager;
		}

		

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
