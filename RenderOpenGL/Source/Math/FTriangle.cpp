#include "FTriangle.h"

const char* KREngine::FTriangle::Print() const
{
	std::string print;
	print = TrianglePositions[0].ToString() + TrianglePositions[1].ToString() + TrianglePositions[2].ToString();
	return print.c_str();
}

bool KREngine::FTriangle::IsEdgeConnected(const FTriangle& other) const
{
	
	uint8 ConnectedCount = 0;
	for(int i =0 ; i < 3 ;i ++)
	{
		if (TrianglePositions[i] == other.TrianglePositions[0] ||
			TrianglePositions[i] == other.TrianglePositions[1] ||
			TrianglePositions[i] == other.TrianglePositions[2]
			)
		{
			ConnectedCount++;
		}
	}

	return ConnectedCount == 2;
}
