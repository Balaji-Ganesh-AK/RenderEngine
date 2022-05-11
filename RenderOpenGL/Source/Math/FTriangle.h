#pragma once
#include <vector>
#include <unordered_map>
#include "RenderOpenGL/Utility/Source/Math/NumericLimit.h"
#include "RenderOpenGL/Utility/Source/Math/Vec3.h"

typedef uint64 FTriangleID;
constexpr  uint8 MaxTrianglePoint = 3;


namespace KREngine
{
	class FTriangle
	{
	public:


		FTriangle(const FVector& a, const FVector& b, const FVector& c, FTriangleID id): TriangleID(id)
		{
			TrianglePositions[0] = a;
			TrianglePositions[1] = b;
			TrianglePositions[2] = c;

		}

		FTriangle(std::array<FVector, 3> trianglePositions, FTriangleID id): TrianglePositions(trianglePositions), TriangleID(id)
		{
		}
		~FTriangle() = default;
	
		bool operator() (const FTriangle& lhs, const FTriangle& rhs) const
		{
			return lhs.TriangleID < rhs.TriangleID;
		}


		FTriangle& operator=(const FTriangle& other)
		{
			TriangleID = other.TriangleID;
			TrianglePositions = other.TrianglePositions;
			return *this;
		}

		bool operator<(const FTriangle& other) const
		{
			return TriangleID < other.TriangleID;
		}

		bool operator==(const FTriangle& other) const
		{
			return TriangleID  == other.TriangleID;
		}

		std::size_t operator()(const FTriangle& k) const
		{
			return std::hash<FTriangleID>()(k.GetTrianlgeID());
		}
	
		const char* Print() const;
		/*Checks if the given triangle is edge connected. i.e
		 * sharing two common vertex between triangles.
		 */
		bool IsEdgeConnected(const FTriangle& other) const;

		FTriangleID GetTrianlgeID() const
		{
	
			return TriangleID;
		}


		uint64 ClusterID = TNumericLimit<uint64>::Max();
	private:
		/*Fixed size array cause 3 points duh*/
		std::array<FVector, 3> TrianglePositions{FVector{},FVector{} ,FVector{} };

		FTriangleID TriangleID = TNumericLimit<uint64>::Max();
		

	};



	struct hash_fn
	{
		std::size_t operator()(const FTriangle& k) const
		{
			return std::hash<FTriangleID>()(k.GetTrianlgeID());
		}
	};

}
