#pragma once
#include "RenderingSystem/Shader.h"
#include "utility/Defines.h"
#include "utility/CommonInclude.h"
#include "utility/Enums.h"

namespace KREngine
{
	class FShader;

	struct FShaderData
	{
		std::string RelativeVertexShaderPath;
		std::string RelativeFragmentShaderPath;
	};

	class FShaderCompilerManager
	{
		public:

			static FShaderCompilerManager* Create();

			/*Loads in all the textures*/
			/*TODO Currently only reads form the texture folder, future la it should read from everywhere*/
			void Init();

			// ReSharper disable once CppMemberFunctionMayBeConst
			uint32 GetShaderID(const std::string& shaderName)
			{
				return ShaderPathToID[shaderName];
			}
			std::shared_ptr<FShader> GetShader(const std::string& shaderName)
			{
				return ShaderMap[ShaderPathToID[shaderName]];
			}


			std::shared_ptr<FShader> GetShader(const std::filesystem::path& shaderPath)
			{
				for (auto& shader_path : ShaderFullPathToName)
				{
					if (shader_path.first == shaderPath.generic_string())
					{
						return ShaderMap[ShaderPathToID[shader_path.first]];
					}
				}
				return nullptr;
			}
			std::shared_ptr<FShader> GetShader(uint32 shaderID)
			{
				return ShaderMap[shaderID];
			}

			void BindShader(uint32 shaderID);

			uint32 ShaderCount() const
			{
				return ShaderMap.size();
			}

			bool HasShaderName(const std::string& shaderName) const
			{
				return ShaderPathToID.contains(shaderName);
			}


			void GetShaderNames(std::vector<std::string>& outVector) const
			{
				outVector.reserve(ShaderPathToID.size());
				for (const std::pair<const std::string, unsigned>& name : ShaderPathToID)
				{
					outVector.push_back(name.first);
				}
			}

		private:
			FShaderCompilerManager();
			void LoadShader(const std::string path);
			std::unordered_map<std::string, uint32> ShaderPathToID;

			std::unordered_map<uint32, std::shared_ptr<FShader>> ShaderMap;

			std::unordered_map < std::string, std::filesystem::path> ShaderNameToFullPath;
			std::unordered_map < std::string, std::string> ShaderFullPathToName;

			/*Relative path to shader code*/
			/*TODO This part should be later replaced by reading the complied binary code from storage.*/
			std::unordered_map < std::string, std::string> ShaderFullToShaderCode;

			std::vector<std::string>AllowedExtenstion{ ".GLSL" };


			FShaderRawData ReaderShaderFile(const std::filesystem::path& shaderPath);

		};
	}

