#pragma once
#include "../Defines.h"


#define KR_UINT64_MAX ((uint64)	0xffffffffffffffff)
#define KR_UINT64_MIN ((uint64)	0x0000000000000000)



#define KR_UINT32_MAX ((uint32)	0xffffffff)
#define KR_UINT32_MIN ((uint32)	0x00000000)

#define KR_FLOAT_MIN ((float) 1.17549e-38 )
#define KR_FLOAT_MAX ((float) 3.40282e+38 )
	

/* Numeric type traits

*/

 /**
  * Helper class to map a numeric type to its limits
  */
template <typename Type>
struct TNumericLimit;

template<>
struct TNumericLimit<uint64>
{
	typedef uint64 NumericType;

	static constexpr NumericType Min()
	{
		return KR_UINT64_MIN;
	}

	static constexpr NumericType Max()
	{
		return KR_UINT64_MAX;
	}

	static constexpr NumericType Lowest()
	{
		return Min();
	}
};


template<>
struct TNumericLimit<uint32>
{
	typedef uint32 NumericType;

	static constexpr NumericType Min()
	{
		return KR_UINT32_MIN;
	}

	static constexpr NumericType Max()
	{
		return KR_UINT32_MAX;
	}

	static constexpr NumericType Lowest()
	{
		return Min();
	}
};

template<>
struct TNumericLimit<float>
{
	typedef uint32 NumericType;

	static constexpr NumericType Min()
	{
		return KR_FLOAT_MIN;
	}

	static constexpr NumericType Max()
	{
		return KR_FLOAT_MAX;
	}

	static constexpr NumericType Lowest()
	{
		return Min();
	}
};