#pragma once
#include "Entity/Entity.h"
#include "Runtime/Containers/FTransform.h"
#include "Runtime/Containers/TArray.h"


namespace KREngine
{
	class FTransformComponent
	{
	public:
		FTransform Transform;
		glm::mat4 ModelProjection{};

		FTransformComponent() {}
		FTransformComponent(const FTransformComponent &other);

		FTransformComponent(const FTransformComponent* other)
		{
			if(other)
			{
				Transform = other->Transform;
				ModelProjection = other->ModelProjection;
			}
			else
			{
				Logger::Error("Cant be empty");
			}
		}

		FTransformComponent& operator= (const FTransformComponent& other)
		{
			if(this == &other)
			{
				return *this;
			}

			Transform = (other.Transform);
			ModelProjection = (other.ModelProjection);
			return *this;
		}

	};

	class FTransformSystem: public FGameSystem
	{
	public:
		virtual void Init() override;
		virtual void Run() override;
		virtual void Stop() override;
		~FTransformSystem() override;

#ifdef  GUI
		void GUIInit() override;
		void GUIRun() override;
		void GUIStop() override;
#endif

	private:
		//TArray<FTransformComponent> TransformComponents;
		std::vector<FTransformComponent*> TransformComponents;

	};
}
