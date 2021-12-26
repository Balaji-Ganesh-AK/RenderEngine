#include "FLights.h"


namespace KREngine
{
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
		if(bUseAmbientColor)
		{			
			return LightColor * AmbientColor;
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
