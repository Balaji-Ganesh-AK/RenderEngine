#pragma once
#include "Math/Color.h"


namespace KREngine
{
	class FLight
	{
	private:
		FColor LightColor{ 1.0f,1.0f,1.0f,1.0f };
		FColor AmbientColor;

		bool bUseAmbientColor{ false };

	public:
		FColor& GetLightColor();
		void SetLightColor( const FColor& lightColor );


		FColor& GetAmbientColor();
		void SetAmbientColor( const FColor& ambientColor );

		/*Gets the value for the shader, total color value*/
		FColor GetShaderColor() const;

		/*Whether to use ambient color for this light source*/
		void SetUseAmbientColor( bool value );
	};
}
