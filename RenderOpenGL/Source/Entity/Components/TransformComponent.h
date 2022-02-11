#pragma once
#include "Entity/Entity.h"
#include "Runtime/Containers/FTransform.h"
#include "Runtime/Containers/TArray.h"


namespace KREngine
{
	struct FTransformComponent
	{
	public:
		FTransform Transform;
	};

	class FTransformSystem : public FSystem
	{
	public:				   
		 void Init();
		 void Run() ;
		 void Stop();
		~FTransformSystem();

#ifdef  GUI
		void GUIInit();
		void GUIRun(FEntityHandle entity) ;
		void GUIStop();
#endif

	};
}
