#include "TransformComponent.h"

#include "glm/gtx/transform.hpp"
namespace KREngine
{
	FTransformComponent::FTransformComponent(const FTransformComponent& other):Transform(other.Transform), ModelProjection(other.ModelProjection)
	{

	}

	void FTransformSystem::Init()
	{

		std::vector<FTransformComponent> temp;

		temp.reserve(TransformComponents.size());
		temp.insert(temp.end(), TransformComponents.begin(), TransformComponents.end());
		{

			for (FTransformComponent& transform_component : temp)
			{
				transform_component.ModelProjection = glm::mat4(1.0f);
				transform_component.ModelProjection = glm::translate(transform_component.ModelProjection, transform_component.Transform.GetLocation().AsGLMVec3());
				transform_component.ModelProjection = glm::rotate(transform_component.ModelProjection, glm::radians(transform_component.Transform.GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
				transform_component.ModelProjection = glm::rotate(transform_component.ModelProjection, glm::radians(transform_component.Transform.GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
				transform_component.ModelProjection = glm::rotate(transform_component.ModelProjection, glm::radians(transform_component.Transform.GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
				transform_component.ModelProjection = glm::scale(transform_component.ModelProjection, transform_component.Transform.GetScale().AsGLMVec3());
			}
		}

		/*Should lock it here and update here*/
		for (int i =0; i< TransformComponents.size(); i++)
		{
			TransformComponents[i] = &temp[i];
		} 
	}

	void FTransformSystem::Run()
	{
		

		std::vector<FTransformComponent> temp;

		temp.reserve(TransformComponents.size());
		temp.insert(temp.end(), TransformComponents.begin(), TransformComponents.end());
		for (FTransformComponent& transform_component : temp)
		{
			Logger::Verbose("Running on");
			transform_component.ModelProjection = glm::mat4(1.0f);
			transform_component.ModelProjection = glm::translate(transform_component.ModelProjection, transform_component.Transform.GetLocation().AsGLMVec3());
			transform_component.ModelProjection = glm::rotate(transform_component.ModelProjection, glm::radians(transform_component.Transform.GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
			transform_component.ModelProjection = glm::rotate(transform_component.ModelProjection, glm::radians(transform_component.Transform.GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
			transform_component.ModelProjection = glm::rotate(transform_component.ModelProjection, glm::radians(transform_component.Transform.GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
			transform_component.ModelProjection = glm::scale(transform_component.ModelProjection, transform_component.Transform.GetScale().AsGLMVec3());
		}

		/*Should lock it here and update here*/
		for (int i = 0; i < TransformComponents.size(); i++)
		{
			TransformComponents[i] = &temp[i];
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
		FGameSystem::GUIInit();
	}

	void FTransformSystem::GUIRun()
	{
		FGameSystem::GUIRun();
	}

	void FTransformSystem::GUIStop()
	{
		FGameSystem::GUIStop();
	}
}
