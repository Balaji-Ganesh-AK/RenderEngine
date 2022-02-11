

#include "EngineMain.h"
using namespace KREngine;

//class TestGame: public FGame
//{
//public:
//	TestGame() = default;
//	virtual void Init() override{};
//	virtual void Run() override{};
//	virtual void Stop() override{};
//	void Test() {};
//};


	int main( void )
	{


		if (false)
		{
			struct TESTINGSHIT
			{
			public:
				TESTINGSHIT()
				{}
				TESTINGSHIT(int x,int y): X(x), Y(y)
				{
					Logger::Verbose( "THIS SHIT IS CREATED" );
				}
				~TESTINGSHIT()
				{
					Logger::Verbose( "DELETING THIS SHIT" );
				}
				TESTINGSHIT(const TESTINGSHIT&& other)
				{
					X = other.X;
					Y = other.Y;
					Name = other.Name;
					
				}
				TESTINGSHIT(  TESTINGSHIT& other )
				{
					X = other.X;
					Y = other.Y;
					Name = other.Name;

				}
				TESTINGSHIT& operator=(const TESTINGSHIT& other )
				{
					X = other.X;
					Y = other.Y;
					Name = other.Name;
					return *this;
				}
				
				std::string Name {"BALAJI"};
				int X;
				int Y;
			};


			std::vector<TESTINGSHIT> Test;
			Test.push_back( TESTINGSHIT( 1, 2 ) );
			Test.push_back( TESTINGSHIT( 3, 2 ) );
			Test.push_back( TESTINGSHIT( 4, 2 ) );
			Test.push_back( TESTINGSHIT( 5, 2 ) );
			Test.push_back( TESTINGSHIT( 2, 3 ) );


			for ( int i = 0; i < Test.size(); i++ )
			{
				Logger::Verbose( "Array element %d", Test [i] );
			}


			for ( int i = 0; i < Test.size(); i++ )
			{
				Logger::Verbose( "Array element %d", Test [i] );
			}

			
			
			TArray<TESTINGSHIT> IntArray;
			IntArray.Add( TESTINGSHIT (1,2));
			IntArray.Add( TESTINGSHIT (3,2));
			IntArray.Add( TESTINGSHIT (4,2));
			IntArray.Add( TESTINGSHIT (5,2));
			IntArray.Add( TESTINGSHIT (2,3));
	
			
		

			

			

			
			for(int i = 0 ; i < IntArray.GetSize(); i++)
			{
				Logger::Verbose( "Array element %d", IntArray[i].X );
			}

			IntArray.RemoveAt( 2 );

			for ( int i = 0; i < IntArray.GetSize(); i++ )
			{
				Logger::Verbose( "Hello %d", IntArray [i].X );
			}
			Logger::Verbose( "uuuuuu %d", IntArray [4] );
			//auto poi = *Test.begin();
			//Logger::Verbose( "xxxxxxx %d", int(int(&poi) + sizeof(int) * 2) );
			//int i = 100000000;
			//std::vector<int> tes( i, 1 );
			//int index = i / 2;
			//SCOPED_TIMER( "Non Optimized" );
			//{
			//	for ( int i = 0; i < i - 1; i++ )
			//	{
			//		if ( i < index )
			//			tes [i] = tes [i] + 1;
			//		else
			//			tes [i] = tes [i + 1] + 1;
			//	}
			//}
			//{

			//	SCOPED_TIMER( "Optimized" );
			//	{


			//		for ( int i = 0; i < index; i++ )
			//		{
			//			tes [i] = tes [i] + 1;
			//		}
			//		for ( int i = index + 1; i < i; i++ )
			//		{

			//			tes [i] = tes [i] + 1;
			//		}


			//		/*for ( auto& x : tes )
			//	{
			//		x += rand();
			//	}*/
			//		/*std::for_each( std::execution::par, tes.begin(), tes.end(), [] ( int& x )
			//	{
			//		x += rand();
			//	} );*/
			//	}
			//}
		}
		
		else
		{


		FApplication* Application = KREngine::CreateApplication();
		EngineManager::PreInit(*Application);

		EngineManager::Init();
		EngineManager::Run();
		EngineManager::End();
			delete Application;
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
