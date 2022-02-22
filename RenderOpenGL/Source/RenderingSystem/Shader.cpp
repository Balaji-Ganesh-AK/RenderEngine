#include "Shader.h"

#include "RenderingAPI/OpenGL/Shader/OpenGLShader.h"
#include <sstream>





KREngine::FShader* KREngine::FShader::CreateShader(const FShaderRawData& fShaderRawData)
{
	return new OpenGLShader(fShaderRawData.VertexShader, fShaderRawData.FragmentShader);

}

KREngine::FShader* KREngine::FShader::CopyShader(const FShader* other)
{
	return new OpenGLShader(other);
}
