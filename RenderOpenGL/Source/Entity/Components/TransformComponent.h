#pragma once
#include "Entity/Entity.h"
#include "RenderOpenGL/Utility/Source/File/FJson.h"
#include "Runtime/Containers/FTransform.h"


namespace KREngine
{

	

	struct FTransformComponent
	{
	public:
		FTransform Transform;
		glm::mat4 ModelProjection;
	public:
		FTransformComponent(const FTransform& transform): Transform(transform)
		{
			
		}
		FTransformComponent() = default;

		FJson ToJson();
		void FromJson(FJson& json);
	};

	class FTransformSystem : public FSystem
	{
	public:				   
		 void Init();
		 void Run() const;
		 void Stop();
		~FTransformSystem();

#ifdef  GUI
		void GUIInit();
		void GUIRun() ;
		void GUIStop();
#endif

	};
}
