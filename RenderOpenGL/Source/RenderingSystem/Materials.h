#pragma once
#include "Math/Vec3.h";
namespace KREngine
{
	class FMaterials
	{
	private:
		float Shininess = {32.0f};
		
		FVector Ambient {1.0f,0.5f,0.3f};
		FVector Diffuse{ 0.1f,0.1f,0.1f };;
		FVector Specular{ 0.5f,0.5f,0.3f };;
		
	public:

		float& GetShininess();
		
		FVector& GetAmbient() ;
		FVector& GetDiffuse() ;
		FVector& GetSpecular() ;
	};
}
