#include "TransformComponent.h"

#include "GameManager.h"

#include "glm/gtx/transform.hpp"

#include "RenderingSystem/FRenderingSystem.h"
#include "Systems/TextureSystem/TextureManager.h"

namespace KREngine
{

	void FTransformSystem::Init()
	{


	}

	void FTransformSystem::Run() const
	{
		{
			SCOPED_TIMER("Transform System ");

			 
			for (const FEntityHandle entity : EntityHandles)
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
	}

	void FTransformSystem::Stop()
	{
	}

	FTransformSystem::~FTransformSystem()
	{
	}
#ifdef  GUI
	void FTransformSystem::GUIInit()
	{

	}

	void FTransformSystem::GUIRun()
	{


	}

	void FTransformSystem::GUIStop()
	{
	
	}
#endif

}
