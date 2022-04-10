#include "FJson.h"

namespace KREngine
{


	FJson FJsonHelper::ToJson(const FVector& vector)
	{
		return {vector.x, vector.y, vector.z};
	}


}
