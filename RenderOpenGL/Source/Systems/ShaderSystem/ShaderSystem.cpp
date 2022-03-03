#include "ShaderSystem.h"

#include "RenderingSystem/Shader.h"
#include "utility/LogTimer.h"

namespace KREngine
{
		FShaderManager* FShaderManager::Create()
		{
			return new FShaderManager();
		}

		void FShaderManager::Init()
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
							/*Read the complied shader data here, if any exist*/
							ReaderShaderFile(shader_path);
						}

					}
				}

			}
		}

		FShaderRawData FShaderManager::GetShaderRawDataFromFile(const std::filesystem::path& VertexShaderPath, const std::filesystem::path& FragmentShaderPath)
		{
			FShaderRawData return_data;

			return_data.VertexShaderCode = ReaderShaderFile(VertexShaderPath);
			return_data.FragmentShaderCode = ReaderShaderFile(FragmentShaderPath);

			return return_data;
		}

		void FShaderManager::BindShader(uint32 shaderID)
		{
			if (ShaderMap.contains(shaderID))
			{
				ShaderMap[shaderID]->BindShader();
			}

		}

		FShaderManager::FShaderManager()
		{
		}

		void FShaderManager::LoadShader(const std::string path)
		{
		}

		std::string FShaderManager::ReaderShaderFile(const std::filesystem::path& shaderPath)
		{
			if (!ShaderFullPathToShaderCode.contains(shaderPath.generic_string()))
			{
				std::ifstream shaderFile;
				shaderFile.open((shaderPath.relative_path()));
				std::stringstream shader_stream;
				{
					std::string line;
					EShaderType type = EShaderType::None;
					while (std::getline(shaderFile, line))
					{
						if (line.find("##Shader End") == std::string::npos)
						{

							shader_stream << line << '\n';

						}
						else
						{
							/*TODO CHECK THIS SHIT*/
							shaderFile.clear();
							shaderFile.close();
						}

					}
				}

				ShaderFullPathToShaderCode[shaderPath.generic_string()] = shader_stream.str();

			}
			return ShaderFullPathToShaderCode[shaderPath.generic_string()];
		}
}
