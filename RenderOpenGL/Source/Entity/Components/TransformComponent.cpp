#include "TransformComponent.h"

#include "GameManager.h"
#include "glm/gtx/transform.hpp"
#include "ImGUI/imgui.h"

namespace KREngine
{

	void FTransformSystem::Init()
	{

		
	}

	void FTransformSystem::Run()
	{
		

		
	}

	void FTransformSystem::Stop()
	{
	}

	FTransformSystem::~FTransformSystem()
	{
	}

	void FTransformSystem::GUIInit()
	{
		
	}

	void FTransformSystem::GUIRun(FEntityHandle entity)
	{

	
			{
				if(ImGui::CollapsingHeader("Transform"))
				{
					auto& transformcomponent = EntityManager::GetComponent<FTransformComponent>(entity);

					IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Translation", &transformcomponent.Transform.GetLocation().x), "Translation", );


					IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Rotation", &transformcomponent.Transform.GetRotation().x, 1, -360000, 360000), "Rotation", );
					IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Scale", &transformcomponent.Transform.GetScale().x, 1, -360000, 360000), "Scale", );
				}
				ImGui::Separator();
				

			}

		
		
	}

	void FTransformSystem::GUIStop()
	{
	
	}
}
