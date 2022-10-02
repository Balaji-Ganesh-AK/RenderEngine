#include "Plane.h"

#include "Entity/Entity.h"


namespace KREngine
{
	/*
	 * A plane is created using a normal vector and distance
	 * the plane formula is Ax + By + Cz = d;
	 */
	struct FPlane
	{
		FVector Normal;
		float Distance;


		FPlane() = default;
		FPlane (FVector normal, float distance): Normal(normal), Distance(distance)
		{
		}

		/*Create a plane using 3 points */
		FPlane(FVector a , FVector b, FVector c)
		{
			
			FVector p1 = b - a;
			FVector p2 = c - a;
			Normal = FVector::Cross(p1,p2);
			Distance = Normal.Dot(a);

		}
	};

	class FPlaneSystem : public FSystem
	{
	public:

		
	private:

	};
}
