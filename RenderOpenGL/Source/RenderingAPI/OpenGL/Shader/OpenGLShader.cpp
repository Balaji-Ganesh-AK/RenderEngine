#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>


namespace KREngine
{
	OpenGLShader::OpenGLShader( const std::string& vertexShader, const std::string& fragShader )
	{
		RendererID = CreateShader( vertexShader, fragShader );

		glUseProgram( RendererID );
	}

	OpenGLShader::OpenGLShader(const FShader* other)
	{
		RendererID = other->GetShaderRenderID();
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
		glUniform4f( location, vector4.x, vector4.y, vector4.z, vector4.w );
	}
	void OpenGLShader::SetUniform4f( int location, vec4 vector4 )
	{
		glUniform4f( location, vector4.x, vector4.y, vector4.z, vector4.w );
	}

	void OpenGLShader::SetUniformMat4(const std::string& location, const glm::mat4& matrix)
	{
		glUniformMatrix4fv( glGetUniformLocation( RendererID, location.c_str() ), 1, GL_FALSE, &matrix[0][0] );
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

			/*Save the shader code as an asset*/
			//GLint length = 0;
			//glGetProgramiv(program, GL_PROGRAM_BINARY_LENGTH, &length);
			//std::vector<GLubyte> buffer(length);
			//GLenum format = 0;
			//glGetProgramBinary(program, length, NULL, &format, buffer.data());
			//std::string fName = "TESTSHADER.bin";
			//;
			//std::cout << "Writing to " << "Binaries/Shaders/" + fName << ", binary format = " << format << std::endl;
			//std::filesystem::create_directories("Binaries/Shaders");
			//std::ofstream out(("Binaries/Shaders/" + fName).c_str(), std::ios::binary);
			//out.write(reinterpret_cast<char*>(buffer.data()), length);
			//out.close();

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

	void OpenGLShader::SetUniform3f(const std::string& name, KREngine::vec3 vector4)
	{
		const GLint location = glGetUniformLocation( RendererID, name.c_str() );
		glUniform3f( location, vector4.x, vector4.y, vector4.z);
	}

	void OpenGLShader::SetUniformInt(const std::string& name, int value)
	{
		const GLint location = glGetUniformLocation( RendererID, name.c_str() );
		glUniform1i( location, value );
	}

	void OpenGLShader::SetUniformF(const std::string& name, float value)
	{
		const GLint location = glGetUniformLocation( RendererID, name.c_str() );
		glUniform1f( location, value );
	}
}

