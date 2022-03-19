#include "DefaultUnlitMaterial.h"

#include "GameManager.h"
#include "Entity/Components/TransformComponent.h"
#include "RenderingSystem/Shader.h"
#include "RenderingSystem/Textures.h"
#include "RenderingSystem/WindowsWindow.h"
#include "Runtime/Camera/FCamera.h"
#include "Systems/TextureSystem/TextureManager.h"
#include "glm/gtx/transform.hpp"
#include "RenderingSystem/Buffers.h"
#include "RenderingSystem/FRenderer.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"

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

		TexturePathToTextureMap.insert({ "Material.BaseTexture" , FApplication::GetTextureManager().GetTexture(u_Texture) });
		Shader->SetUniformInt("Material.BaseTexture", Slot);
		Slot = Slot + 1;

	

	}


	void DefaultUnlitMaterial::Bind(int& Slot)
	{
		Shader->BindShader();

		for (const auto& texture : TexturePathToTextureMap)
		{
			texture.second->BindTexture(Slot);
			Slot = Slot + 1;
		}

	}

	void DefaultUnlitMaterial::UnBind()
	{
		Shader->UnBindShader();
	}

	

	DefaultUnlitMaterial::~DefaultUnlitMaterial()
	{

	}




	void FDefaultUnLitMaterialSystem::Init()
	{
		FScopedTimer Timer("Default unlit system init");

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
								//BufferElement{"v_Normal", EShaderDataType::FVec3, true},
				};

				/*TODO fetch all the entities with static mesh component
				 * TODO: Should work for runtime after setting up event system.
				 */
				for (const FEntityHandle& entity : EntityHandles)
				{
					auto& static_mesh = EntityManager::GetComponent<FStaticMesh>(entity);

					static_mesh.VertexArray = FVertexArray::Create();
					//static_mesh.VertexBufferData.reset(FVertexBuffer::CreateVertexBuffer(static_mesh.Positions, sizeof(static_mesh.Positions) / sizeof(float)));
					//static_mesh.IndexBufferData.reset(FIndexBuffer::CreateIndexBuffer(static_mesh.Indices, sizeof(static_mesh.Indices) / sizeof(unsigned int)));
					static_mesh.VertexBufferData = FVertexBuffer::CreateVertexBuffer(static_mesh.Positions, sizeof(static_mesh.Positions) / sizeof(float));
					static_mesh.IndexBufferData = FIndexBuffer::CreateIndexBuffer(static_mesh.Indices, sizeof(static_mesh.Indices) / sizeof(unsigned int));

					static_mesh.VertexArray->SetLayOut(layout);
					static_mesh.VertexArray->BindBufferLayout();
					static_mesh.VertexArray->UnBindBuffer();
					material.UnBind();
				}
			}
		}
	
	}

	void FDefaultUnLitMaterialSystem::Run(const FCamera& mainCamera, const std::shared_ptr<FRenderer>& renderer)
	{
		/*Default shader update */
		const glm::mat4 ViewProjection = mainCamera.ViewProjection;


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
						shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);
						shader->SetUniformMat4("u_Model", /*ViewProjection **/model_projection);
						shader->SetUniform4f("Material.ObjectColor", vec4(Color.r, Color.g, Color.b, Color.a));
						static_mesh.VertexArray->BindBuffer();
						// 3 vertex two triangles.
						renderer->Draw(static_cast<int>(static_mesh.IndexBufferData->GetIndexBufferCount()));
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
