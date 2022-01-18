#pragma once
#include "Runtime/Containers/FTransform.h"


namespace KREngine
{
	class FCamera 
	{
	public:
		FCamera();
		void SetTransform(FTransform& transform)
		{
			CameraTransform = transform;
		}
		FTransform& GetTransform()
		{
			return CameraTransform;
		}

		 FTransform GetGLMTransform() const;
	private:
		FTransform CameraTransform;
	};
}
