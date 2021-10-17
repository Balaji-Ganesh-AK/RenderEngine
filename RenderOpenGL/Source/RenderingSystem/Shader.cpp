#include "Shader.h"

#include "RenderingAPI/OpenGL/Shader/OpenGLShader.h"


KREngine::FShader* KREngine::FShader::CreateShader(const std::string& vertexFilePath, const std::string& fragFilePath )
{
	std::string vertexCode;
	std::string fragCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragShaderFile;

	vertexShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
	fragShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );

	try
	{
		/** Open and read the files*/
		vertexShaderFile.open( vertexFilePath );
		fragShaderFile.open( fragFilePath );
		std::stringstream vertexShaderStream;
		std::stringstream fragShaderStream;

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragShaderStream << fragShaderFile.rdbuf();

		vertexShaderFile.close();
		fragShaderFile.close();
		vertexCode = vertexShaderStream.str();
		fragCode = fragShaderStream.str();
		return new OpenGLShader( vertexCode, fragCode );
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Shader error! Failed to read the file" << std::endl;
		return nullptr;
	}

	return nullptr;
}
