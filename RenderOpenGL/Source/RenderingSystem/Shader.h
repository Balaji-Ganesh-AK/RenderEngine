#pragma once
#include "utility/Pch.h"

namespace KREngine
{

	struct FShaderColorData
	{
		
	};

	class FShader
	{
	public:
		virtual ~FShader() = default;

		static FShader* CreateShader(  std::filesystem::path& vertexFilePath,  std::filesystem::path& fragFilePath );

		virtual void BindShader() =0;
		virtual void UnBindShader() =0 ;
		virtual void SetUniformInt(const std::string& location, int value) = 0;
		virtual void SetUniformF(const std::string& location, float value) = 0;
		virtual void SetUniform4f( const std::string& location, KREngine::vec4 vector4 ) = 0;
		virtual void SetUniform3f( const std::string& location, KREngine::vec3 vector4 ) = 0;
		virtual void SetUniformMat4( const std::string& location, const glm::mat4& matrix ) = 0;
		virtual void SetUniform4f( int location, vec4 vector4 ) = 0;
	protected:

		uint32 RendererID;
	};


}
