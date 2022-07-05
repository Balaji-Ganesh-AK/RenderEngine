#pragma once
#include "Entity/Entity.h"
#include "Material/DefaultMateirals.h"


namespace KREngine
{
	struct FFoliageInstance
	{
		FDefaultLitMaterial Material{ "../Content/Shaders/Source/DefaultLitVertexShader.GLSL" , "../Content/Shaders/Source/DefaultLitFragmentShader.GLSL" };
		FGeometryID GeometryId;
		FFoliageInstanceID InstanceId;
	};

	class FFoliageSystem: public FSystem
	{
	public:
		void Init() override;
		void Run(const FCameraComponent& mainCamera, const std::shared_ptr<FRenderer>& renderer) ;
		void End() override;
	};
}
