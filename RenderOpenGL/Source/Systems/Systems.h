#pragma once


#include "utility/Pch.h"
#include "Input/Windows/WindowsInput.h"
#include "RenderingSystem/WindowsWindow.h"
#include "utility/CommonUtilityClass.h"
#include "Entity/Entity.h"
#include "Game.h"

namespace KREngine
{
	class FRenderingSystem;

	

//	class Test : INonCopyableClass
//	{
//	public:
//
//		Test();
//		
//		/* Runs the initialization code on all the registered systems. All systems will have to be registered.
//		 * Note : Systems can be unregistered any time.
//		 */
//		void Init() const;
//
//		/* Runs all the systems which are registered.  */
//		void Run() const;
//
//		/*Runs the destructor on all the registered systems.*/
//		void Stop() const;
//
//		/* Updates the GUI */
//#if GUI
//		void InitGUI() const;
//
//		void RunGUI();
//
//		void StopGUI() const;
//#endif
//		
//		FRenderingSystem* GetRenderingSystem() const;
//		WindowsInput* GetInput() const;
//		
//	private:
//
//		friend class FApplication;
//		
//	//	void Register( std::shared_ptr<FGameSystem> system);
//		//WindowsProperties Prop;
//		
//	
//		std::shared_ptr<FRenderingSystem> RenderingSystem;
//		std::unique_ptr<WindowsInput> InputSystem;
//
//
//		std::vector<std::shared_ptr<FGameSystem>> SystemsList;
//		//std::vector<FGameSystem*> SystemsList;
//		//std::vector<FGameSystem> SystemsList;
//		//std::vector<std::shared_ptr<FGameSystem>> SystemsList;
//		//
//		//
//	private:
//		
//	};


}
