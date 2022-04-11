#pragma once
#include <type_traits>
#include <concepts>
#include "Vec3.h"
namespace KREngine
{
	//Primary
	template<class T> struct is_f_vector : std::false_type {};

	//specialization
	template<> struct is_f_vector<void> : std::true_type {};


	template<class T>
	constexpr  auto pi = static_cast<T>(3.1415926535897932384626433);

	template<class T> constexpr T absolute(T val)
	{
		return val < 0 ? -val : val;
	}

	template <std::floating_point T> constexpr auto  epsilon = static_cast<T>(0.000001);
	constexpr  bool close_enough (std::integral auto a, std::integral auto b)
	{
		 return a == b;
	}
	constexpr bool close_enough(std::floating_point auto a, std::floating_point auto b)
	{
		return absolute(a - b) <= epsilon<std::common_type_t<decltype(a), decltype(b)>>;
	}


}