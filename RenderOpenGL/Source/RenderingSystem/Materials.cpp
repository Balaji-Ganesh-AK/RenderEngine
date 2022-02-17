#include "Materials.h"

#include "GameManager.h"
#include "Shader.h"
#include "Systems/TextureSystem/TextureManager.h"
#include "utility/CommonInclude.h"
namespace KREngine
{
	FMaterials::FMaterials(  )
	{
		
	}

	void FMaterials::Init( std::shared_ptr<FShader> shader, int& Slot)
	{
		shader->BindShader();
		TextureMap.insert({ "material.Diffuse" , FApplication::GetTextureManager().GetTexture(DiffuseTexture) });
		shader->SetUniformInt( "material.Diffuse", Slot );
		Slot = Slot+ 1;
		TextureMap.insert( { "u_Texture" , FApplication::GetTextureManager().GetTexture(u_Texture)} );
		shader->SetUniformInt( "u_Texture", Slot );
		Slot = Slot + 1;

		TextureMap.insert( { "material.Specular" , FApplication::GetTextureManager().GetTexture(SpecularTexture) } );
		shader->SetUniformInt( "material.Specular", Slot );
		Slot = Slot + 1;
		
	}

	void FMaterials::Bind( int& Slot ) const
	{

		for( const auto& texture: TextureMap )
		{
			texture.second->BindTexture( Slot );
			Slot = Slot+ 1;
		}

	}

	float& FMaterials::GetShininess()
	{
		return Shininess;
	}

	FVector& FMaterials::GetAmbient()
	{
		return Ambient;
	}

	FVector& FMaterials::GetDiffuse() 
	{
		return Diffuse;
	}

	FVector& FMaterials::GetSpecular() 
	{
		return Specular;
	}
}
