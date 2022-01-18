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
		virtual void SetUniformMat4( const std::string& location, const glm::mat4& matrix ) override;
	private:
		unsigned CreateShader( const std::string& vertexShader, const std::string& fragmentShader );
		unsigned CompileShader( unsigned type, const std::string& source );

	public:
		virtual void SetUniform3f(const std::string& location, KREngine::vec3 vector4) override;
		virtual void SetUniformInt(const std::string& location, int value) override;
		virtual void SetUniformF(const std::string& location, float value) override;
	};

}


