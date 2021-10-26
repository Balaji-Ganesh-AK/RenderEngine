#include "OpenGLShader.h"

namespace KREngine
{
	OpenGLShader::OpenGLShader( const std::string& vertexShader, const std::string& fragShader )
	{
		RendererID = CreateShader( vertexShader, fragShader );

		glUseProgram( RendererID );
	}

	OpenGLShader::~OpenGLShader()
	{
	}

	void OpenGLShader::BindShader()
	{
		glUseProgram( RendererID );
	}

	void OpenGLShader::UnBindShader()
	{
		glUseProgram( 0 );
	}

	void OpenGLShader::SetUniform4f( const std::string& name, KREngine::vec4 vector4 )
	{
		GLint location = glGetUniformLocation( RendererID, name.c_str() );
		glUniform4f( location, vector4.x, vector4.y, vector4.w, vector4.z );
	}
	void OpenGLShader::SetUniform4f( int location, vec4 vector4 )
	{
		glUniform4f( location, vector4.x, vector4.y, vector4.w, vector4.z );
	}
	unsigned OpenGLShader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		{
			unsigned int program = glCreateProgram();

			unsigned int vertex_shader = CompileShader( GL_VERTEX_SHADER, vertexShader );
			unsigned int fragment_shader = CompileShader( GL_FRAGMENT_SHADER, fragmentShader );

			glAttachShader( program, vertex_shader );
			glAttachShader( program, fragment_shader );
			glLinkProgram( program );
			glValidateProgram( program );
			glDeleteShader( vertex_shader );
			glDeleteShader( fragment_shader );

			return program;
		}
	}

	unsigned OpenGLShader::CompileShader(unsigned type, const std::string& source)
	{
		unsigned int id = glCreateShader( type );
		//opengl wants a raw string
		const char* src = source.c_str();
		glShaderSource( id, 1, &src, nullptr );
		glCompileShader( id );

		//TODO: Error handling
		int result;
		glGetShaderiv( id, GL_COMPILE_STATUS, &result );

		if ( result == GL_FALSE )
		{
			int errorLength;
			glGetShaderiv( id, GL_COMPILE_STATUS, &errorLength );
			char* message = static_cast< char* >( _alloca( errorLength * sizeof( char ) ) );
			glGetShaderInfoLog( id, errorLength, &errorLength, message );
			assert( "Shader failed" );
			std::cout << message << std::endl;
			glDeleteShader( id );
			return -1;
		}
		return id;
	}


}
