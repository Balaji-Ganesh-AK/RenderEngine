#include "Vec3.h"
#include "glm/detail/_noise.hpp"


namespace KREngine
{
	/*Otha remove this shit*/
	glm::vec3 FVectorHelper::AsGLMVec3(const FVector& other)
	{
		return glm::vec3{ other.x, other.y, other.z };
	}

	vec3 FVectorHelper::AsVec3(const glm::vec3& other)
	{
		return vec3{ other.x, other.y, other.z };
	}
}
