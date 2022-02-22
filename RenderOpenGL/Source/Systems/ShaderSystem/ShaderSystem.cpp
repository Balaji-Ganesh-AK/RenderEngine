#include "ShaderSystem.h"

#include "RenderingSystem/Shader.h"
#include "utility/LogTimer.h"

namespace KREngine
{
		FShaderCompilerManager* FShaderCompilerManager::Create()
		{
			return new FShaderCompilerManager();
		}

		void FShaderCompilerManager::Init()
		{

			{
				FScopedTimer Shader{ "Loading Shaders" };
				for (const std::filesystem::directory_entry& shader_path : std::filesystem::recursive_directory_iterator(DefaultShaderFolderPath))
				{
					for (const std::string& it : AllowedExtenstion)
					{
						if (shader_path.path().extension().generic_string() == it)
						{
							Logger::Verbose("..... Loading Shader from file ....%s", shader_path.path().generic_string().c_str());
							FShaderRawData shaderRawData = ReaderShaderFile(shader_path.path());
							FShader* shader = FShader::CreateShader(shaderRawData);
							
							ShaderPathToID[shader_path.path().generic_string()] = shader->GetShaderRenderID();
							ShaderMap[shader->GetShaderRenderID()].reset(shader);
							ShaderNameToFullPath[shader_path.path().filename().string()] = shader_path.path();
							ShaderFullPathToName[shader_path.path().generic_string()] = shader_path.path().filename().string();
						}

					}
				}

			}
		}

		void FShaderCompilerManager::BindShader(uint32 shaderID)
		{
			if (ShaderMap.contains(shaderID))
			{
				ShaderMap[shaderID]->BindShader();
			}

		}

		FShaderCompilerManager::FShaderCompilerManager()
		{
		}

		void FShaderCompilerManager::LoadShader(const std::string path)
		{
		}

		FShaderRawData FShaderCompilerManager::ReaderShaderFile(const std::filesystem::path& shaderPath)
		{
			std::ifstream shaderFile;

			//shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			FShaderRawData raw_data;
			//try
			{
				/** Open and read the files*/
				//std::cout << "Shader error! Failed to read the file " << std::filesystem::absolute(vertexFilePath.relative_path()) <<std::endl;
				shaderFile.open((shaderPath.relative_path()));


				std::string line;
				EShaderType type = EShaderType::None;
				std::stringstream shader_stream[2];

				while (std::getline(shaderFile, line))
				{
					if (line.find("#Shader End") == std::string::npos)
					{


						if (line.find("#Shader") != std::string::npos)
						{
							if (line.find("Vertex") != std::string::npos)
							{
								type = EShaderType::VertexShader;
							}
							else if (line.find("Fragment") != std::string::npos)
							{
								type = EShaderType::FragmentShader;
							}
						}
						else
						{
							shader_stream[static_cast<uint8>(type)] << line << '\n';
						}
					}
					else
					{
						/*TODO CHECK THIS SHIT*/
						shaderFile.clear();
						shaderFile.close();
					}

				}

				raw_data.FragmentShader = shader_stream[static_cast<uint8>(EShaderType::FragmentShader)].str();
				raw_data.VertexShader = shader_stream[static_cast<uint8>(EShaderType::VertexShader)].str();


				return raw_data;
			}
		}
}
