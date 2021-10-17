#pragma once
#include "../utility/Pch.h"

namespace KREngine
{

	struct FShaderColorData
	{
		
	};

	class FShader
	{
	public:
		virtual ~FShader() = default;

		static FShader* CreateShader( const std::string& vertexFilePath , const std::string& fragFilePath);

		virtual void BindShader() =0;
		virtual void UnBindShader() =0 ;
		virtual void SetUniform4f( const std::string& location, KREngine::vec4 vector4 ) = 0;
		virtual void SetUniform4f( int location, vec4 vector4 ) = 0;
	protected:

		uint32 RendererID;
	};


}
