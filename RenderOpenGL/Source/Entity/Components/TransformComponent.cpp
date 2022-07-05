#include "TransformComponent.h"

#include "GameManager.h"

#include "glm/gtx/transform.hpp"
#include "Math/Vec3.h"

#include "RenderingSystem/FRenderingSystem.h"
#include "Systems/TextureSystem/TextureManager.h"

namespace KREngine
{
	FJson FTransformComponent::ToJson()
	{
		FJson return_json;

		return_json["Location"] = FJsonHelper::ToJson(Transform.GetLocation());
		return_json["Rotation"] = FJsonHelper::ToJson(Transform.GetRotation());
		return_json["Scale"] = FJsonHelper::ToJson(Transform.GetScale());

		return return_json;
	}

	void FTransformComponent::FromJson(FJson& json)
	{
		FVector Location; 
		FVector Scale; 
		FVector Rotation; 
		if(json.contains("Location") && json.contains("Rotation") && json.contains("Scale"))
		{
			Location = FJsonHelper::FromJson(json["Location"]);
			Rotation = FJsonHelper::FromJson(json["Rotation"]);
			Scale = FJsonHelper::FromJson(json["Scale"]);
		}
		else
		{
			Logger::Warning("Error reading transform data from map file ");
		}
		Transform.SetLocation(Location);
		Transform.SetScale(Scale);
		Transform.SetRotation(Rotation);
	}

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
				model_projection = glm::translate(model_projection, FVectorHelper::AsGLMVec3(transform.GetLocation()));
				model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
				model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
				model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
				model_projection = glm::scale(model_projection, FVectorHelper::AsGLMVec3(transform.GetScale()));
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
