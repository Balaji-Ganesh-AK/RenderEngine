#pragma once
#include "Runtime/Containers/FTransform.h"
#include "utility/Defines.h"


namespace KREngine
{
	class FMesh
	{
	public:
		void SetTransform(const FTransform&  transform);
		void SetLocation(const FVector& location);
		void SetRotation( const FRotation& rotation );
		void SetScale( const FVector& scale );



		void SetTransform( FTransform& transform );
		void SetLocation( FVector& location );
		void SetRotation( FRotation& rotation );
		void SetScale(  FVector& scale );

		FTransform& GetTransform();
		FVector& GetLocation();
		FVector& GetRotation();
		FVector& GetScale();
	private:
		KREngine::FTransform Transform;

		uint32 Indices [3 * 4 * 3] = {
			0,1,2,
			2,3,0,

			4,5,7,
			7,6,4,

			8,9,10,
			10,11,8,

			12,13,14,
			14,15,12,

			16,17,18,
			18,19,16,

			20,21,22,
			22,23,20
		};

		float Positions [8 * 24] = {
			//Vertex Positions	    //Color				//Tex Cord   
			/** 0 */		-0.5f,-0.5f,-0.5f,		0.0f, 0.0f, 0.0f,	0.5f, 0.5f,
			/** 1 */		0.5f,-0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.5f,
			/** 2 */		0.5f,0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			/** 3 */		-0.5f,0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	0.5f, 1.0f,

			/** 4 */		-0.5f,-0.5f,0.5f,		0.0f, 0.0f, 0.0f,	0.5f, 0.5f,
			/** 5 */		0.5f,-0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.5f,
			/** 6 */		-0.5f,0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	0.5f, 1.0f,
			/** 7 */		0.5f,0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,

			/** 8 */		-0.5f,0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
			/** 9 */		0.5f,0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
			/** 10 */		0.5f,0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			/** 11 */		-0.5f,0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,

			/** 12 */		-0.5f,-0.5f,-0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
			/** 13 */		0.5f,-0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
			/** 14 */		0.5f,-0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			/** 15 */		-0.5f,-0.5f,0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,

			/** 16 */		0.5f,-0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
			/** 17 */		0.5f,-0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
			/** 18 */		0.5f,0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
			/** 19 */		0.5f,0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,

			/** 20 */		-0.5f,-0.5f,-0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
			/** 21 */		-0.5f,-0.5f,0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
			/** 22 */		-0.5f,0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			/** 23 */		-0.5f,0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f

		};
	};
}
