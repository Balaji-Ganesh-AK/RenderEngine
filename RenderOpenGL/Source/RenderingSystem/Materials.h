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

		std::unordered_map<std::string, std::shared_ptr<FTexture2D>> TextureMap;
		std::string DiffuseTexture = "DiffuseWoodCrate.png";
		std::string SpecularTexture = "SpecularCrate.png";
		std::string u_Texture = "awesomeface.png";
		void Init( std::shared_ptr<FShader> shader, int& Slot );
		void Bind( int& Slot) const;
		
		float& GetShininess();
		
		FVector& GetAmbient() ;
		FVector& GetDiffuse() ;
		FVector& GetSpecular() ;
	};
}
