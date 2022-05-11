#pragma once
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
		FVector Location{0.0f,-100.0f,0.0f};
		FVector Direction{0.2f,-1.0f,-0.3f};
		/*For attenuation, needs refactoring*/
		/*
		 * Formula
		 * att = 1.0/ C + L * D + Q * D * D
		 *
		 *D = Distance.
		 */
		/*Constant C*/
		float Constant = 1.0;
		/*Linear L*/
		float Linear = 0.09f;
		/*Quadratic Q*/
		float Quadratic = 0.032f;

	};
	struct FDirectionalLight
	{
		FVector Direction{0.0f,0.0f,-1.0f};
		FColor AmbientColor{ 0.1f, 0.1f, 0.1f, 0.1f};
		FColor DiffuseColor{1.0f,1.0f, 1.0f,1.0f};
		FColor SpecularColor{ 1.0f,1.0f, 1.0f,1.0f };
	};

	struct FPointLight
	{

		/*For attenuation, needs refactoring*/
		/*
		 * Formula
		 * att = 1.0/ C + L * D + Q * D * D
			 *
		 *D = Distance.
		*/
		 /*Constant C*/
		float Constant = 1.0;
		/*Linear L*/
		float Linear = 0.09f;
		/*Quadratic Q*/
		float Quadratic = 0.032f;
		vec3 Position;
		FColor AmbientColor{ 0.1f, 0.1f, 0.1f, 0.1f };
		FColor DiffuseColor{ 1.0f,1.0f, 1.0f,1.0f };
		FColor SpecularColor{ 1.0f,1.0f, 1.0f,1.0f };

		//uint16 PointLightID = -1;
		
	};

	class FLightSystem: public FSystem
	{

	public:
		void Init();
		void Update();
		void End();

#ifdef GUI
		void GUIRun();
#endif


	};
}
