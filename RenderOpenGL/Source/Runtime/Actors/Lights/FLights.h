#pragma once
#include "Math/Color.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"


namespace KREngine
{
	struct FLight
	{
		FColor LightColor{ 0.5f,0.5f,0.5f,1.0f };
		FColor AmbientColor;
		float AmbientStrength = 0.1f;
		float Shininess = 1.0f;
		bool bUseAmbientColor{ false };
		/*Can be moved out of this*/
		FVector Location{0.0f,0.0f,0.0f};
	};

	class FLightSystem: public FSystem
	{

	public:
		//void Init();
		//void Update();
		//void End();

	//private:
	//	FColor LightColor{ 1.0f,1.0f,1.0f,1.0f };
	//	FColor AmbientColor;
	//	float AmbientStrength =0.1f;
	//	bool bUseAmbientColor{ false };

	//public:
	//	FLight();
	//	FColor& GetLightColor();
	//	void SetLightColor( const FColor& lightColor );


	//	FColor& GetAmbientColor();
	//	void SetAmbientColor( const FColor& ambientColor );

	//	/*Gets the value for the shader, total color value*/
	//	FColor GetShaderColor() const;

	//	/*Whether to use ambient color for this light source*/
	//	void SetUseAmbientColor( bool value );
	//	bool GetUseAmbientColor() { return bUseAmbientColor; }
	//	
	};
}
