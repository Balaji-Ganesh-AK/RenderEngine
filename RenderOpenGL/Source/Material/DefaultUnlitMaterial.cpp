#include "DefaultUnlitMaterial.h"

#include "GameManager.h"
#include "Entity/Components/TransformComponent.h"
#include "RenderingSystem/Shader.h"
#include "RenderingSystem/Textures.h"
#include "RenderingSystem/WindowsWindow.h"
#include "Runtime/Camera/FCameraComponent.h"
#include "Systems/TextureSystem/TextureManager.h"
#include "glm/gtx/transform.hpp"
#include "RenderingSystem/Buffers.h"
#include "RenderingSystem/FRenderer.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"
#include "Systems/AssetSystem/AssetSystem.h"

namespace KREngine
{

	DefaultUnlitMaterial::DefaultUnlitMaterial()
	{

	}

	void DefaultUnlitMaterial::Init(int& Slot)
	{
		Shader.reset(FShader::CreateShader(DefaultVertexShaderPath, DefaultFragmentShaderPath));

		Shader->BindShader();


		/*TexturePathToTextureMap.insert({ "u_Texture" , FApplication::GetTextureManager().GetTexture(u_Texture) });
		Shader->SetUniformInt("u_Texture", Slot);
		Slot = Slot + 1;*/

		TextureRenderNameToTextureMap.insert({ "Material.BaseTexture" , FApplication::GetTextureManager().GetTexture(u_Texture) });
		TextureRenderNameToTexturePath.insert({ "Material.BaseTexture" , u_Texture});
		Shader->SetUniformInt("Material.BaseTexture", Slot);
		Slot = Slot + 1;

	

	}


	void DefaultUnlitMaterial::Bind(int& Slot)
	{
		Shader->BindShader();

		for (const auto& texture : TextureRenderNameToTextureMap)
		{
			texture.second->BindTexture(Slot);
			Slot = Slot + 1;
		}

	}

	void DefaultUnlitMaterial::UnBind()
	{
		Shader->UnBindShader();
	}


	FJson DefaultUnlitMaterial::ToJson()
	{
		FJson return_value;
		for (auto texture_map : TextureRenderNameToTexturePath)
		{
			return_value["TextureDetail"][texture_map.first] = texture_map.second;
		}

		return return_value;

	}

	DefaultUnlitMaterial::~DefaultUnlitMaterial()
	{

	}


	FJson DefaultUnLitMaterialComponent::ToJson()
	{
		FJson return_value;
		return_value["Material"] = Material.ToJson();
		return return_value;
	}

	void FDefaultUnLitMaterialSystem::Init()
	{
		FScopedTimer Timer("Default unlit system init");
		//////////////////////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < 100; i++)
		{
			float rangeX = rand() % 50 + 0;
			float rangeY = rand() % 50 + 0;
			float rangeZ = rand() % 50 + 0;

			Translations.emplace_back(rangeX, rangeY, rangeZ);
		}
		//////////////////////////////////////////////////////////////////////////////////////////
		for (const FEntityHandle Entity : EntityHandles)
		{
			if (EntityManager::HasComponent<DefaultUnLitMaterialComponent>(Entity))
			{
				auto& material = EntityManager::GetComponent<DefaultUnLitMaterialComponent>(Entity).Material;

				int slot = 0;
				material.Init(slot);
				/*TODO: extract this function to read the file and return the layout used fo this mesh*/
				VertexBufferLayout layout{
								BufferElement{"v_Pos", EShaderDataType::FVec3, true},
								BufferElement{"v_Texture", EShaderDataType::FVec2, true},
								BufferElement{"v_Normal", EShaderDataType::FVec3, true},
								BufferElement{"v_ID", EShaderDataType::Float, false},
								//BufferElement{"v_Normal", EShaderDataType::FVec3, true},
				};

				/*TODO fetch all the entities with static mesh component
				 * TODO: Should work for runtime after setting up event system.
				 */
				
					auto& static_mesh = EntityManager::GetComponent<FStaticMesh>(Entity);

					static_mesh.VertexArray = FVertexArray::Create();
					if (static_mesh.Model->VertexPositionBuffer.size() == static_mesh.Model->TextureCordBuffer.size() && static_mesh.Model->VertexPositionBuffer.size() == static_mesh.Model->NormalBuffer.size())
					{
						/*Combine all the buffer to a single buffer object*/
						for (int i = 0; i < static_mesh.Model->VertexPositionBuffer.size(); i++)
						{

							static_mesh.VertexBuffer.push_back(static_mesh.Model->VertexPositionBuffer[i].x);
							static_mesh.VertexBuffer.push_back(static_mesh.Model->VertexPositionBuffer[i].y);
							static_mesh.VertexBuffer.push_back(static_mesh.Model->VertexPositionBuffer[i].z);
							static_mesh.VertexBuffer.push_back(static_mesh.Model->TextureCordBuffer[i].x);
							static_mesh.VertexBuffer.push_back(static_mesh.Model->TextureCordBuffer[i].y);
							static_mesh.VertexBuffer.push_back(static_mesh.Model->NormalBuffer[i].x);
							static_mesh.VertexBuffer.push_back(static_mesh.Model->NormalBuffer[i].y);
							static_mesh.VertexBuffer.push_back(static_mesh.Model->NormalBuffer[i].z);
							static_mesh.VertexBuffer.push_back(Entity);
							

						}

					}
					else
					{
						Logger::Error("Mesh does not look good, please check the mesh! ");
					}
					
					static_mesh.VertexBufferData = FVertexBuffer::CreateVertexBuffer(static_mesh.VertexBuffer.data(), static_mesh.VertexBuffer.size());
					static_mesh.IndexBufferData = FIndexBuffer::CreateIndexBuffer(static_mesh.Model->IndexPositions.data(), static_mesh.Model->IndexPositions.size());

					static_mesh.VertexArray->SetLayOut(layout);
					static_mesh.VertexArray->BindBufferLayout();
					static_mesh.VertexArray->UnBindBuffer();
					material.UnBind();
				
			}
		}

		
	

	
	}

	void FDefaultUnLitMaterialSystem::Run(const FCameraComponent& mainCamera, const std::shared_ptr<FRenderer>& renderer)
	{
		/*Default shader update */
		const glm::mat4 ViewProjection = mainCamera.ViewProjection;
		
		glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments should pass the stencil test
		glStencilMask(0xFF);

		const glm::mat4 WorldProjection = glm::perspective(glm::radians(45.0f), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 10000.0f);

			for (const FEntityHandle Entity : EntityHandles)
			{
				if (EntityManager::HasComponent<DefaultUnLitMaterialComponent>(Entity) && EntityManager::HasComponent<FTransformComponent>(Entity) && EntityManager::HasComponent<FStaticMesh>(Entity))
				{
					auto& static_mesh = EntityManager::GetComponent<FStaticMesh>(Entity);
					const auto& model_projection = EntityManager::GetComponent<FTransformComponent>(Entity).ModelProjection;
					auto& material = EntityManager::GetComponent<DefaultUnLitMaterialComponent>(Entity).Material;
					std::shared_ptr<FShader>& shader = material.Shader;
					if (shader)
					{
						int slot = 0;
						material.Bind(slot);
						
						//shader->SetUniform3f("Positions[1]", Translations[Entity]);
						shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);
						shader->SetUniformMat4("u_Model", /*ViewProjection **/model_projection);
						shader->SetUniform4f("Material.ObjectColor", vec4(Color.r, Color.g, Color.b, Color.a));
						static_mesh.VertexArray->BindBuffer();
						// 3 vertex two triangles.
						renderer->Draw(static_cast<int>(static_mesh.IndexBufferData->GetIndexBufferCount()));
					//	renderer->DrawIndexed(static_cast<int>(static_mesh.IndexBufferData->GetIndexBufferCount()), Translations.size());
						//(glDrawElements(GL_TRIANGLES, static_cast<int>(static_mesh.IndexBufferData->GetIndexBufferCount()), GL_UNSIGNED_INT, nullptr));
						static_mesh.VertexArray->UnBindBuffer();
						material.UnBind();
					}
				}
			}


		
	}

	void FDefaultUnLitMaterialSystem::End()
	{
	}

	void FDefaultUnLitMaterialSystem::GUIRun()
	{
		ImGui::Begin("TESTING MENU");
		IMGUI_LEFT_LABEL(ImGui::DragFloat4("##LightColor", &Light.LightColor.r, 0.01, -1, 1), "LightColor", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat4("##ObjectColor", &Color.r, 0.01, -1, 1), "ObjectColor", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat("##Shininess", &Light.Shininess, 2, 2, 1024), "Shininess", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Direction", &Light.Direction.x), "Direction", );
		ImGui::End();
	}


}
