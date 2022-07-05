#include "Shader.h"

#include "RenderingAPI/OpenGL/Shader/OpenGLShader.h"
#include <sstream>

#include "GameManager.h"
#include "Systems/ShaderSystem/ShaderSystem.h"


/*TODO Send in the complied code here*/
KREngine::FShader* KREngine::FShader::CreateShader(const std::filesystem::path& VertexShaderPath, const std::filesystem::path& FragmentShaderPath)
{

	FShaderRawData shader_raw_data = FApplication::GetShaderManager().GetShaderRawDataFromFile( VertexShaderPath, FragmentShaderPath) ;

	return new OpenGLShader(shader_raw_data.VertexShaderCode, shader_raw_data.FragmentShaderCode);

}

