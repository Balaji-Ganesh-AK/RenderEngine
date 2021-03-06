#pragma once

#include "Entity/Entity.h"
#include "Runtime/Containers/FTransform.h"


namespace KREngine
{
	struct FCamera
	{
		bool bMainCamera = false;
		float CameraSpeed{ 0.05f };
		glm::mat4 ViewProjection;
		//glm::mat4 WorldProjection;
		glm::vec3 Direction{};
		glm::vec3 CameraPosition{ 0.0f,0.0f,1.0f };
		glm::vec3 CameraFront{ 0.0f,0.0f,-1.0f };
		glm::vec3 CameraUp{ 0.0f,-1.0f,0.0f };
		FVector Rotator{90.0f,0,0};

	public:
		FCamera() = default;

		explicit FCamera(bool mainCamera): bMainCamera(mainCamera), ViewProjection()//, WorldProjection()
		{
		}
	};


	struct FDebugCamera
	{
#if GUI
		FTransform CameraTransform;
#endif

	};

	class FCameraSystem : public FSystem
	{

	public:
		FCameraSystem() = default;
		~FCameraSystem() = default;
		void Init();
		void Run() ;
		void Stop();

		FCamera& GetMainCamera()  ;


#if GUI
		void GUIInit();
		void GUIStop();
		void GUIRun();
#endif
	private:
		bool bHasValid{ false };
		Vec2 LastKnowMousePos;
		FEntityHandle MainCameraEntity;


		bool bTestRest{false};
	};
}
