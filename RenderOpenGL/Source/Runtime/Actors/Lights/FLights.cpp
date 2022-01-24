#include "FLights.h"


namespace KREngine
{
	FLight::FLight()
	{
		
	}

	FColor& FLight::GetLightColor()
	{
		return LightColor;
	}

	void FLight::SetLightColor(const FColor& lightColor)
	{
		LightColor = lightColor;
	}

	FColor& FLight::GetAmbientColor()
	{
		return AmbientColor;
	}

	void FLight::SetAmbientColor(const FColor& ambientColor)
	{
		AmbientColor = ambientColor;
	}

	FColor FLight::GetShaderColor() const
	{
		return LightColor;

		if(bUseAmbientColor)
		{
			return FColor( LightColor.r * AmbientStrength, LightColor.g * AmbientStrength, LightColor.b * AmbientStrength,LightColor.a );
			
		}
		else
		{
			return LightColor;
		}
	}

	void FLight::SetUseAmbientColor(bool value)
	{
		bUseAmbientColor = value;
	}
}
