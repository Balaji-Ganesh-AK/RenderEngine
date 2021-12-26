#include "Shader.h"

#include "RenderingAPI/OpenGL/Shader/OpenGLShader.h"


KREngine::FShader* KREngine::FShader::CreateShader(std::filesystem::path& vertexFilePath, std::filesystem::path& fragFilePath )
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
		//std::cout << "Shader error! Failed to read the file " << std::filesystem::absolute(vertexFilePath.relative_path()) <<std::endl;
		vertexShaderFile.open( ( vertexFilePath.relative_path() ) );

		fragShaderFile.open( (fragFilePath.relative_path() ));
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
