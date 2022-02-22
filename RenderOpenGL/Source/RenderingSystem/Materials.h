#pragma once
#include <unordered_map>


#include "Textures.h"
#include "Math/Vec3.h"
namespace KREngine
{
	class FShader;

	class FMaterials
	{
	private:
		float Shininess = {32.0f};
		
		FVector Ambient {1.0f,0.5f,0.3f};
		FVector Diffuse{ 0.1f,0.1f,0.1f };
		FVector Specular{ 0.5f,0.5f,0.3f };

	public:
		FMaterials(  );

		std::unordered_map<std::string, std::shared_ptr<FTexture2D>> TexturePathToTextureMap;

		std::string DiffuseTexture = "DiffuseWoodCrate.png";
		std::string SpecularTexture = "SpecularCrate.png";
		std::string u_Texture = "awesomeface.png";

		std::shared_ptr<FShader> Shader;
		std::filesystem::path DefaultShaderPath = "../Content/Shaders/Default/DefaultShader.GLSL";

		void Init( int& Slot );
		void Bind(int& Slot);
		void UnBindShader( ) ;
		
		float& GetShininess();
		
		FVector& GetAmbient() ;
		FVector& GetDiffuse() ;
		FVector& GetSpecular() ;
	};
}
