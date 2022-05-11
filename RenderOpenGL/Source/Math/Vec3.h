#pragma once
#include "glm/gtx/vec_swizzle.hpp"
#include "RenderOpenGL/Utility/Source/Math/Vec3.h"
namespace  KREngine
{
	

	class FVectorHelper
	{
	public:
		static glm::vec3 AsGLMVec3(const FVector& other);

		static vec3  AsVec3(const glm::vec3& other);
	};

	
	;

}
