#include "TransformComponent.h"

#include "GameManager.h"
#include "glm/gtx/transform.hpp"
#include "ImGUI/imgui.h"

namespace KREngine
{

	void FTransformSystem::Init()
	{

		
	}

	void FTransformSystem::Run() const
	{
		for (const FEntityHandle entity: EntityHandles)
		{
			FTransform& transform = EntityManager::GetComponent<FTransformComponent>(entity).Transform;
			auto& model_projection = EntityManager::GetComponent<FTransformComponent>(entity).ModelProjection;
			model_projection = glm::mat4(1.0f);
			model_projection = glm::translate(model_projection, transform.GetLocation().AsGLMVec3());
			model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
			model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
			model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
			model_projection = glm::scale(model_projection, transform.GetScale().AsGLMVec3());
		}
		
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

	void FTransformSystem::GUIRun()
	{

	
			{
				if(ImGui::CollapsingHeader("Transform"))
				{
					auto& transformcomponent = EntityManager::GetComponent<FTransformComponent>(0);

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
