#include "Materials.h"

namespace KREngine
{
	float& FMaterials::GetShininess()
	{
		return Shininess;
	}

	FVector& FMaterials::GetAmbient()
	{
		return Ambient;
	}

	FVector& FMaterials::GetDiffuse() 
	{
		return Diffuse;
	}

	FVector& FMaterials::GetSpecular() 
	{
		return Specular;
	}
}
