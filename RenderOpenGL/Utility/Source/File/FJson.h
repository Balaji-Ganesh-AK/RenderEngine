#pragma once

#include "../../../Dependencies/nlohmann/json.hpp"
#include "../Math/Vec3.h"
#include "../../../Dependencies/glm/glm/ext/vector_float3.hpp"




using FJson = nlohmann::json;

namespace KREngine
{
	


	class FJsonHelper
	{
	public:
		static FJson ToJson(const FVector& vector);
		template<class T>
		static FJson ToJson(const std::vector<T>& vector);


		

		static FVector FromJson(FJson& json);

		//
	private:
		FJsonHelper();
	};

	template <class T>
	FJson FJsonHelper::ToJson(const std::vector<T>& vector)
	{
		FJson return_json;
		for (int i = 0; i < vector.size(); i++)
		{
			return_json += (vector[i]);

		}
		//return FJson::to_cbor(return_json);
		return return_json;
	}

	inline FJson FJsonHelper::ToJson(const FVector& vector)
	{
		return FJson{ vector.x, vector.y,vector.z};
	}

	inline FVector FJsonHelper::FromJson(FJson& json)
	{

		return FVector{ json[0], json[1], json[2] };
	}
}
