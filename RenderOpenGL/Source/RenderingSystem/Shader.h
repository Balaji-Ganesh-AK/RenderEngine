#pragma once

#include "RenderOpenGL/Utility/Source/Math/Vec4.h"
#include "utility/Pch.h"
#include <glm/glm.hpp>
namespace KREngine
{



	/*Helper struct to store vertex and fragment shader*/
	struct FShaderRawData
	{
	public:
		std::string VertexShaderCode;
		std::string FragmentShaderCode;
	};

	struct FShaderStruct
	{
	public:
		std::string VertexShaderPath;
		std::string FragmentShaderPath;
	};

	class FShader
	{
	public:
		virtual ~FShader() = default;
		
		static FShader* CreateShader(const std::filesystem::path& VertexShaderPath , const std::filesystem::path& FragmentShaderPath);

		virtual void BindShader() =0;
		virtual void UnBindShader() =0 ;
		virtual void SetUniformInt(const std::string& location, int value) = 0;
		virtual void SetUniformF(const std::string& location, float value) = 0;
		virtual void SetUniform4f(const std::string& location, KREngine::FColor color) = 0;
		virtual void SetUniform4f( const std::string& location, KREngine::vec4 vector4 ) = 0;
		virtual void SetUniform3f( const std::string& location, KREngine::vec3 vector4 ) = 0;
		virtual void SetUniformMat4( const std::string& location, const glm::mat4& matrix ) = 0;
		virtual void SetUniform4f( int location, vec4 vector4 ) = 0;

		FORCEINLINE uint32 GetShaderRenderID() const
		{
			return RendererID;
		}


	private:
		
	protected:

		uint32 RendererID;
	};

	/*Base interface class for all shader programs*/
	class IShaderProgram
	{
	public:
		virtual ~IShaderProgram() = default;
		virtual void Init() =0;
		virtual void Update() =0;
		virtual void End() = 0;
		virtual void SetShader(FShader* shader)
		{
			Shader.reset(shader);
		}
	private:
		std::unique_ptr<FShader> Shader;
	};


}
