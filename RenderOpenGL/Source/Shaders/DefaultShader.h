#pragma once
#include "Entity/Entity.h"
#include "RenderingSystem/Shader.h"
#include "Runtime/Actors/Lights/FLights.h"
#include "Runtime/Camera/FCamera.h"


namespace KREngine
{

	/*FIND A WAY TO AVOID DOING THIS*/
	struct FDefaultUnLitShaderComponent
	{

	};

	class FDefaultUnLitShader : public FSystem
	{
	public:
		void Init();
		void Run(const FCamera& mainCamera);
		void End();

	private:
		FColor Color{ 1.0f,1.0f,1.0f,1.0f };
	};


	/*FIND A WAY TO AVOID DOING THIS*/
	struct FDefaultShaderComponent
	{

	};


	class FDefaultLitShader : public FSystem
	{
	public:
		void Init();
		void Run(const FCamera& mainCamera);
		void End();
		void GUIRun();

	private:
		FColor Color{ 1.0f,1.0f,1.0f,1.0f };
		FLight Light;
	};
}

