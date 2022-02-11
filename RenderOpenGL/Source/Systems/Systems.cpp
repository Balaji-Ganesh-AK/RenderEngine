
#include "RenderingSystem/FRenderingSystem.h"
#include "RenderingSystem/WindowsWindow.h"
#include "Systems.h"


#include "GameManager.h"
#include "Entity/Components/TransformComponent.h"
#include "GLFW/glfw3.h"


//#include "utility/Globals.h"

namespace KREngine
{

//	void Test::Init() const
//	{
//		RenderingSystem->Init();
//
//		for (const std::shared_ptr<FGameSystem>& system : SystemsList)
//		{
//			system->Init();
//		}
//	
//	}
//
//	void Test::Run() const
//	{
//		RenderingSystem->Run();
//		for (const std::shared_ptr<FGameSystem>& system : SystemsList)
//		{
//			system->Run();
//		}
//	}
//
//	void Test::Stop() const
//	{
//		RenderingSystem->Stop();
//		for (const std::shared_ptr<FGameSystem>& system : SystemsList)
//		{
//			system->Stop();
//		}
//	}
//
//#if GUI
//  	void Test::InitGUI() const
//    {
//		//RenderingSystem->GUIInit();
//
//		for (const std::shared_ptr<FGameSystem>& system : SystemsList)
//		{
//			system->GUIInit();
//		}
//	}
//
//	void Test::RunGUI()
//	{
//
//		
//	}
//
//	void Test::StopGUI() const
//	{
//		//RenderingSystem->GUIStop();
//		for (const std::shared_ptr<FGameSystem>& system : SystemsList)
//		{
//			system->GUIStop();
//		}
//	}
//#endif
//	Test::Test()
//	{
//		
//		//RenderingSystem = std::make_shared<FRenderingSystem>( WindowWindow.get() );
//
//		InputSystem = std::make_unique<WindowsInput>(RenderingSystem);
//
//
//		/*Game systems*/
//		std::shared_ptr<FStaticMeshSystem> System = std::make_shared<FStaticMeshSystem>();
//		SystemsList.emplace_back(System);
//
//		std::shared_ptr<FTransformSystem> TransformSystem = std::make_shared<FTransformSystem>();
//		SystemsList.emplace_back(TransformSystem);
//	}
//
//
//
//	/*void Test::Register( std::shared_ptr<FGameSystem> system )
//	{
//		if(system)
//		{
//			SystemsList.push_back( system );
//		}
//	}*/
//
//	FRenderingSystem* Test::GetRenderingSystem() const
//	{
//		return RenderingSystem.get();
//	}
//
//	WindowsInput* Test::GetInput() const
//	{
//		return InputSystem.get();
//	}
}
