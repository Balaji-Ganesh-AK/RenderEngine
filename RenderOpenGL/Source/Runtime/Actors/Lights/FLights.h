#pragma once
#include "Math/Color.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"


namespace KREngine
{
	class FLight
	{
	private:
		FColor LightColor{ 1.0f,1.0f,1.0f,1.0f };
		FColor AmbientColor;
		float AmbientStrength =0.1f;
		FStaticMesh Mesh;
		bool bUseAmbientColor{ false };

	public:
		FLight();
		FColor& GetLightColor();
		void SetLightColor( const FColor& lightColor );


		FColor& GetAmbientColor();
		void SetAmbientColor( const FColor& ambientColor );

		/*Gets the value for the shader, total color value*/
		FColor GetShaderColor() const;

		/*Whether to use ambient color for this light source*/
		void SetUseAmbientColor( bool value );
		bool GetUseAmbientColor() { return bUseAmbientColor; }
		FORCEINLINE FStaticMesh& GetMesh()
		{
			return Mesh;
		}
	};
}
