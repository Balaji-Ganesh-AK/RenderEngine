#pragma once
#include "Math/Vec3.h"

namespace KREngine
{
	class FTransform 
	{
	public:

		FTransform(FVector& location, FVector& rotation, FVector& scale ): Location(location), Rotation(rotation), Scale(scale)
		{
		}

		FTransform()
		{
			
		}

		FVector& GetLocation() { return Location; }
		FVector& GetRotation();
		FVector& GetScale() { return Scale; }


		void SetLocation(FVector& location) { Location = location; }
		void SetRotation(FVector& rotation);
		void SetScale( FVector& scale ) { Scale = scale; }



		void SetLocation(const FVector& location ) { Location = location; }
		void SetRotation( const FVector& rotation );
		void SetScale( const FVector& scale ) { Scale = scale; }
		
	private:

		FVector Location{ 0.0f,0.0f,0.0f };
		FVector Rotation{ 0.0f,0.0f,0.0f };
		FVector Scale{ 1.0f,1.0f,1.0f };
	};

	inline FVector& FTransform::GetRotation()
	{

		if ( Rotation.x < -360 )
		{
			Rotation.x = Rotation.x / -360;
		}
		if ( Rotation.y < -360 )
		{
			Rotation.y = Rotation.y / -360;
		}
		if ( Rotation.z < -360 )
		{
			Rotation.z = Rotation.z / -360;
		}
		
		if ( Rotation.x > 360 )
		{
			Rotation.x = Rotation.x/360;
		}
		if ( Rotation.y > 360 )
		{
			Rotation.y = Rotation.y / 360;
		}
		if ( Rotation.z > 360 )
		{
			Rotation.z = Rotation.z / 360;
		}


	

		return Rotation;
	}

	inline void FTransform::SetRotation(FVector& rotation)
	{
		if ( rotation.x < -360 )
		{
			rotation.x = rotation.x / -360;
		}
		if ( rotation.y < 0 )
		{
			rotation.y = rotation.y / -360;
		}
		if ( rotation.z < 0 )
		{
			rotation.z = rotation.z / -360;
		}

		if ( rotation.x > 360 )
		{
			rotation.x = rotation.x / 360;
		}
		if ( rotation.y > 360 )
		{
			rotation.y = rotation.y / 360;
		}
		if ( rotation.z > 360 )
		{
			rotation.z = rotation.z / 360;
		}
		Rotation = rotation;
	}
}


