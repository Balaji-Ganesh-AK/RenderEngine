#include "Vec3.h"
#include "glm/detail/_noise.hpp"


namespace KREngine
{

	glm::vec3 VectorHelper::AsGLMVec3(const FVector& other)
	{
		return glm::vec3{ other.x, other.y, other.z };
	}

	vec3 VectorHelper::AsVec3(const glm::vec3& other)
	{
		return vec3{ other.x, other.y, other.z };
	}
}
