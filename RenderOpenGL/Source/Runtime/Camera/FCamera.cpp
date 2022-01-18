#include "FCamera.h"


namespace KREngine
{
	FCamera::FCamera()
	{
	//	CameraTransform.SetRotation( FVector( CameraTransform.GetRotation().x, 180, CameraTransform.GetRotation().z ) );
	}

	 FTransform FCamera::GetGLMTransform() const
	{
		FTransform temp = CameraTransform;
		temp.SetLocation( FVector( temp.GetLocation().x, temp.GetLocation().y, temp.GetLocation().z ) );
		return temp;
	}
}
