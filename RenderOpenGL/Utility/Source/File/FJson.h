#pragma once

#include "../../../Dependencies/nlohmann/json.hpp"
#include "../Math/Vec3.h"

using FJson = nlohmann::json;

namespace KREngine
{
	class Vec2;

	class FJsonHelper
	{
	public:
		static FJson ToJson(const FVector& vector);
		template<class T>
		static FJson ToJson(const std::vector<T>& vector);
		
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
}
