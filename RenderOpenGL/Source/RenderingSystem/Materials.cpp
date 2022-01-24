#include "Materials.h"
#include "Shader.h"
#include "utility/CommonInclude.h"
namespace KREngine
{
	FMaterials::FMaterials(  )
	{
		
	}

	void FMaterials::Init( std::shared_ptr<FShader> shader, int& Slot)
	{
		Shader = shader;
		Shader->BindShader();
		TextureMap.insert( { "material.Diffuse" , FTexture2D::Create( DiffuseTexture ) } );
		Shader->SetUniformInt( "material.Diffuse", Slot );	
		Slot = Slot+ 1;
		TextureMap.insert( { "u_Texture" , FTexture2D::Create( u_Texture ) } );
		Shader->SetUniformInt( "u_Texture", Slot );
		Slot = Slot + 1;

		TextureMap.insert( { "material.Specular" , FTexture2D::Create( SpecularTexture ) } );
		Shader->SetUniformInt( "material.Specular", Slot );
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
