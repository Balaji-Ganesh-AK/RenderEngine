#include "Materials.h"

#include "GameManager.h"
#include "Shader.h"
#include "Systems/ShaderSystem/ShaderSystem.h"
#include "Systems/TextureSystem/TextureManager.h"
#include "utility/CommonInclude.h"
namespace KREngine
{
	FMaterials::FMaterials(  )
	{
		
	}

	void FMaterials::Init(int& Slot)
	{
		Shader.reset(FShader::CopyShader(FApplication::GetShaderCompilerManager().GetShader(DefaultShaderPath).get()));
		Shader->BindShader();
		TexturePathToTextureMap.insert({ "material.Diffuse" , FApplication::GetTextureManager().GetTexture(DiffuseTexture) });
		Shader->SetUniformInt( "material.Diffuse", Slot );
		Slot = Slot+ 1;
		TexturePathToTextureMap.insert( { "u_Texture" , FApplication::GetTextureManager().GetTexture(u_Texture)} );
		Shader->SetUniformInt( "u_Texture", Slot );
		Slot = Slot + 1;

		TexturePathToTextureMap.insert( { "material.Specular" , FApplication::GetTextureManager().GetTexture(SpecularTexture) } );
		Shader->SetUniformInt( "material.Specular", Slot );
		Slot = Slot + 1;
		
	}

	void FMaterials::Bind( int& Slot )
	{
		Shader->BindShader();
		

		for( const auto& texture: TexturePathToTextureMap )
		{
			texture.second->BindTexture( Slot );
			Slot = Slot+ 1;
		}

	}

	void FMaterials::UnBindShader() 
	{
		Shader->UnBindShader();
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
