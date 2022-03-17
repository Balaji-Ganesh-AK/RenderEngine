#pragma once
#include "Entity/Entity.h"
#include "RenderingSystem/Material.h"
#include "RenderingSystem/Shader.h"
#include "Runtime/Actors/Lights/FLights.h"
#include "Runtime/Camera/FCamera.h"


namespace KREngine
{
	class FFrameBuffer;
	class FTexture2D;

	class FDefaultLitMaterial : public IMaterial
	{
	private:
		float Shininess = { 32.0f };

		FVector Ambient{ 1.0f,0.5f,0.3f };
		FVector Diffuse{ 0.1f,0.1f,0.1f };
		FVector Specular{ 0.5f,0.5f,0.3f };

	public:
		FDefaultLitMaterial();

		std::unordered_map<std::string, std::shared_ptr<FTexture2D>> TexturePathToTextureMap;
		std::string u_Texture = "DefaultTexture.png";
		/*Used for calling binding functions*/
		uint32 ShaderID;
		std::shared_ptr<FShader> Shader;


		std::string DiffuseTexture = "DiffuseWoodCrate.png";
		std::string SpecularTexture = "SpecularCrate.png";
	
		std::filesystem::path DefaultVertexShaderPath = "../Content/Shaders/Source/DefaultLitVertexShader.GLSL";
		std::filesystem::path DefaultFragmentShaderPath = "../Content/Shaders/Source/DefaultLitFragmentShader.GLSL";

		/*	std::filesystem::path DefaultVertexShaderPath = "../Content/Shaders/Source/DefaultVertexShader.GLSL";
			std::filesystem::path DefaultFragmentShaderPath = "../Content/Shaders/Source/DefaultFragmentShader.GLSL";*/

		void Init(int& Slot) override;

		void Bind(int& Slot) override;

		void UnBind() override;

		float& GetShininess();

		FVector& GetAmbient();

		FVector& GetDiffuse();

		FVector& GetSpecular();

		void SetShininess(float shininess)
		{
			Shininess = shininess;
		}

		~FDefaultLitMaterial() override;
	};

	

	struct DefaultLitMaterialComponent
	{
		FDefaultLitMaterial Material;
	};

	class FDefaultLitMaterialSystem : public FSystem
	{
	public:
		void Init();
		void Run(const FCamera& mainCamera);
		void End();
		void GUIRun();

	private:
		FColor Color{ 1.0f,1.0f,1.0f,1.0f };
		FLight Light;
		float test = 0.0;
		std::shared_ptr<FFrameBuffer> Framebuffer;
	};

}
