#pragma once
#include "RenderingSystem/Shader.h"
#include "utility/Defines.h"
#include "utility/CommonInclude.h"
#include "utility/Enums.h"

namespace KREngine
{
	class FShader;

	/*This will be stored in the shader manager class */
	struct FShaderData
	{
	public:
		/*The display name of the shader*/
		std::string ShaderName;
		/*The relative path to the vertex shader*/
		std::string RelativeVertexShaderPath;
		/*The relative path to the fragment shader*/
		std::string RelativeFragmentShaderPath;

		/*OPENGL: Renderer ID*/
		uint32 ShaderID;
	};

	/*RUN ONCE */
	class FShaderManager
	{
		public:

			static FShaderManager* Create();

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

			FShaderRawData GetShaderRawDataFromFile(const std::filesystem::path& VertexShaderPath, const std::filesystem::path& FragmentShaderPath);

			//std::shared_ptr<FShader> GetShader(const std::filesystem::path& shaderPath)
			//{
			//	for (auto& shader_path : ShaderFullPathToName)
			//	{
			//		if (shader_path.first == shaderPath.generic_string())
			//		{
			//			return ShaderNameToFullPath[ShaderFullPathToName[shader_path.first]];
			//		}
			//	}
			//	return nullptr;
			//}

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
			FShaderManager();
			void LoadShader(const std::string path);
			std::unordered_map<std::string, uint32> ShaderPathToID;

			std::unordered_map<uint32, std::shared_ptr<FShader>> ShaderMap;

		

			/*Relative path to shader code*/
			/*TODO This part should be later replaced by reading the complied binary code from storage.*/
			std::unordered_map < std::string, std::string> ShaderRelativePathToShaderCode;

			std::vector<std::string>AllowedExtenstion{ ".GLSL" };

			/*Reads in the given file and returns the code in string, which will be
			 * used as input for compiling the shader.
			 */
			std::string ReaderShaderFile(const std::filesystem::path& shaderPath);

			/*Look up cache table for already read files*/

			/*Have to fucking use string when using map and cant use std::filepath for some stupid reason i don't know ~bg*/
			std::unordered_map < std::string, std::string> ShaderFullPathToShaderCode;
		};
	}

