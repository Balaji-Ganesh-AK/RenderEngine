#include "FCamera.h"


#include "GameManager.h"
#include "glm/ext/matrix_clip_space.hpp"

#include "Systems/Input/Input.h"
#include "glm/ext/matrix_transform.hpp"
#include "RenderingSystem/WindowsWindow.h"

namespace KREngine
{

	// FTransform FCamera::GetGLMTransform() const
	//{
	//	FTransform temp = CameraTransform;
	//	temp.SetLocation( FVector( temp.GetLocation().x, temp.GetLocation().y, temp.GetLocation().z ) );
	//	return temp;
	//}

	 void FCameraSystem::Init()
	 {
		 for (const FEntityHandle entityHandle : EntityHandles)
		 {
			 auto& camera = EntityManager::GetComponent<FCamera>(entityHandle);


			 if(camera.bMainCamera)
			 {
				 bHasValid = true;
				 MainCameraEntity = entityHandle;
				// camera.WorldProjection = glm::perspective(glm::radians(45.0f), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 100.0f);
				 float sensitivity = 0.1f;

				 Vec2 current_mouse_pos;
				 FApplication::Get().GetInputSystem().GetMousePosition(current_mouse_pos);
				 float xoffset = current_mouse_pos.x - LastKnowMousePos.x;
				 float yoffset = LastKnowMousePos.y - current_mouse_pos.y;
				 LastKnowMousePos = current_mouse_pos;
				 camera.Rotator.x -= (xoffset * sensitivity);
				 camera.Rotator.y += (yoffset * sensitivity);


				 if (camera.Rotator.y > 89.0f)
					 camera.Rotator.y = 89.0f;
				 if (camera.Rotator.y < -89.0f)
					 camera.Rotator.y = -89.0f;


				 camera.Direction.x = cos(glm::radians(camera.Rotator.x) * cos(glm::radians(camera.Rotator.y)));
				 camera.Direction.y = sin(glm::radians(camera.Rotator.y));
				 camera.Direction.z = sin(glm::radians(camera.Rotator.x)) * cos(glm::radians(camera.Rotator.y));
				 camera.CameraFront = glm::normalize(camera.Direction);
				 break;
			 }
		 }
	 }

	 void FCameraSystem::Run()
	 {


		 {
			 SCOPED_TIMER("Camera loop");

			 if (bHasValid)
			 {
				 FCamera& MainCamera = EntityManager::GetComponent<FCamera>(MainCameraEntity);
				 if (FApplication::Get().GetInputSystem().IsMouseKeyPressed(Input::MouseCode::Button2))
				 {

					 if (!bTestRest)
					 {
						 FApplication::Get().GetInputSystem().GetMousePosition(LastKnowMousePos);
						 bTestRest = true;
					 }
					 Vec2 current_mouse_pos;
					 FApplication::Get().GetInputSystem().GetMousePosition(current_mouse_pos);

					 float sensitivity = 0.1f;


					 float xoffset = current_mouse_pos.x - LastKnowMousePos.x;
					 float yoffset = LastKnowMousePos.y - current_mouse_pos.y;
					 LastKnowMousePos = current_mouse_pos;
					 MainCamera.Rotator.x -= (xoffset * sensitivity);
					 MainCamera.Rotator.y += (yoffset * sensitivity);


					 if (MainCamera.Rotator.y > 89.0f)
						 MainCamera.Rotator.y = 89.0f;
					 if (MainCamera.Rotator.y < -89.0f)
						 MainCamera.Rotator.y = -89.0f;


					 MainCamera.Direction.x = cos(glm::radians(MainCamera.Rotator.x) * cos(glm::radians(MainCamera.Rotator.y)));
					 MainCamera.Direction.y = sin(glm::radians(MainCamera.Rotator.y));
					 MainCamera.Direction.z = sin(glm::radians(MainCamera.Rotator.x)) * cos(glm::radians(MainCamera.Rotator.y));
					 MainCamera.CameraFront = glm::normalize(MainCamera.Direction);

					 if (FApplication::Get().GetInputSystem().IsKeyPressed(Input::KeyCodes::W))
					 {
						 MainCamera.CameraPosition += MainCamera.CameraSpeed * MainCamera.CameraFront;
					 }
					 if (FApplication::Get().GetInputSystem().IsKeyPressed(Input::KeyCodes::S))
					 {
						 MainCamera.CameraPosition -= MainCamera.CameraSpeed * MainCamera.CameraFront;
					 }
					 if (FApplication::Get().GetInputSystem().IsKeyPressed(Input::KeyCodes::A))
					 {
						 MainCamera.CameraPosition -= glm::normalize(glm::cross(MainCamera.CameraFront, MainCamera.CameraUp)) * MainCamera.CameraSpeed;
					 }
					 if (FApplication::Get().GetInputSystem().IsKeyPressed(Input::KeyCodes::D))
					 {
						 MainCamera.CameraPosition += glm::normalize(glm::cross(MainCamera.CameraFront, MainCamera.CameraUp)) * MainCamera.CameraSpeed;
					 }
				 }
				 else
				 {
					 bTestRest = false;
				 }

			 }



			 for (const FEntityHandle entityHandle : EntityHandles)
			 {
				 auto& camera = EntityManager::GetComponent<FCamera>(entityHandle);


				 camera.ViewProjection = glm::lookAt(camera.CameraPosition,
					 (camera.CameraPosition + camera.CameraFront), camera.CameraUp);
			 }
		 }
	 }

	 void FCameraSystem::Stop()
	 {
	 }

	 FCamera FCameraSystem::GetMainCamera() 
	 {
	 	FCamera MainCamera;
		if(bHasValid)
		{
			MainCamera = EntityManager::GetComponent<FCamera>(MainCameraEntity);
			if (!MainCamera.bMainCamera)
			{
				for (const FEntityHandle entityHandle : EntityHandles)
				{
					FCamera& camera = EntityManager::GetComponent<FCamera>(entityHandle);
					if (camera.bMainCamera)
					{
						MainCameraEntity = entityHandle;
						MainCamera = camera;
						break;
					}
				}
			}
			
		}
		return MainCamera;
		
	 }

	 void FCameraSystem::GUIInit()
	 {
	 }

	 void FCameraSystem::GUIStop()
	 {
	 }

	 void FCameraSystem::GUIRun()
	 {
	 }
}
