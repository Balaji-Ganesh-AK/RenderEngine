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
		FVector Diffuse{ 0.1f,0.1f,0.1f };;
		FVector Specular{ 0.5f,0.5f,0.3f };;

	public:
		FMaterials(  );

		std::unordered_map<std::string, FTexture2D*> TextureMap;
		std::string DiffuseTexture = "../Content/Textures/DiffuseWoodCrate.png";
		std::string SpecularTexture = "../Content/Textures/SpecularCrate.png";
		std::string u_Texture = "../Content/Textures/awesomeface.png";
		std::vector<FTexture2D*> TextureList;
		std::shared_ptr<FShader> Shader;
		void Init( std::shared_ptr<FShader> shader, int& Slot );
		void Bind( int& Slot) const;
		
		float& GetShininess();
		
		FVector& GetAmbient() ;
		FVector& GetDiffuse() ;
		FVector& GetSpecular() ;
	};
}
