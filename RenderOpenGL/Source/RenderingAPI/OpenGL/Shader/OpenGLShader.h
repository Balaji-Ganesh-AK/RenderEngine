#pragma once
#include "RenderingSystem/Shader.h"

namespace KREngine
{
	class OpenGLShader : public FShader
	{
	public:
		OpenGLShader( const std::string& vertexShader, const std::string& fragShader );
		~OpenGLShader() override;
		void BindShader() override;
		void UnBindShader() override;
		virtual void SetUniform4f( const std::string& location, KREngine::vec4 vector4 ) override;
		virtual void SetUniform4f( int location, vec4 vector4 ) override;
	private:
		unsigned CreateShader( const std::string& vertexShader, const std::string& fragmentShader );
		unsigned CompileShader( unsigned type, const std::string& source );
		
	};

}

