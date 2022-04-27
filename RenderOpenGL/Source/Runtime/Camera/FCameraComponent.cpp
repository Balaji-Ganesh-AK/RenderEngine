#include "FCameraComponent.h"


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

	FJson FCameraComponent::ToJson()
	{
		FJson return_json;
		return_json["CameraPosition"] = { CameraPosition.x, CameraPosition.y, CameraPosition.z };
		return_json["CameraFront"] = { CameraFront.x, CameraFront.y, CameraFront.z };
		return_json["CameraUp"] = { CameraUp.x, CameraUp.y, CameraUp.z };
		return_json["Rotator"] = { Rotator.x, Rotator.y, Rotator.z};
		return_json["MainCamera"] = bMainCamera;
		return_json["Direction"] = { Direction.x, Direction.y, Direction.z };


		return return_json;
	}

	void FCameraComponent::FromJson(FJson& json)
	{
		if (json.contains("CameraPosition"))
		{
			CameraPosition = glm::vec3{ json["CameraPosition"][0],json["CameraPosition"][1] ,json["CameraPosition"][2] };
			
		}
		if (json.contains("CameraFront"))
		{
			CameraFront = glm::vec3{ json["CameraFront"][0],json["CameraFront"][1] ,json["CameraFront"][2] };

		}
		if (json.contains("Rotator"))
		{
			Rotator = FVector{ json["Rotator"][0],json["Rotator"][1] ,json["Rotator"][2] };

		}
		if (json.contains("Direction"))
		{
			Direction = glm::vec3{ json["Direction"][0],json["Direction"][1] ,json["Direction"][2] };
		}
		if (json.contains("MainCamera"))
		{
			bMainCamera = static_cast<bool>(json["MainCamera"]);
		}
	
	}

	void FCameraSystem::Init()
	 {
		 for (const FEntityHandle entityHandle : EntityHandles)
		 {
			 auto& camera = EntityManager::GetComponent<FCameraComponent>(entityHandle);


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
				 FCameraComponent& MainCamera = EntityManager::GetComponent<FCameraComponent>(MainCameraEntity);
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
				 auto& camera = EntityManager::GetComponent<FCameraComponent>(entityHandle);


				 camera.ViewProjection = glm::lookAt(camera.CameraPosition,
					 (camera.CameraPosition + camera.CameraFront), camera.CameraUp);
			 }
		 }
	 }

	 void FCameraSystem::Stop()
	 {
	 }

	 FCameraComponent& FCameraSystem::GetMainCamera() 
	 {
		if(bHasValid)
		{
			MainCamera = EntityManager::GetComponent<FCameraComponent>(MainCameraEntity);
			if (!MainCamera.bMainCamera)
			{
				for (const FEntityHandle entityHandle : EntityHandles)
				{
					FCameraComponent& camera = EntityManager::GetComponent<FCameraComponent>(entityHandle);
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
#ifdef  GUI
	 void FCameraSystem::GUIInit()
	 {
	 }

	 void FCameraSystem::GUIStop()
	 {
	 }

	 void FCameraSystem::GUIRun()
	 {
	 }
#endif

}
