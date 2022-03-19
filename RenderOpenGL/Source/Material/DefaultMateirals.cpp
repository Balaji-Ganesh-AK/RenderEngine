#include "DefaultMateirals.h"

#include "GameManager.h"
#include "Entity/Components/TransformComponent.h"
#include "glm/gtx/transform.hpp"
#include "RenderingSystem/FRenderingSystem.h"
#include "RenderingSystem/WindowsWindow.h"
#include "Runtime/Camera/FCamera.h"
#include "Math/Color.h"
#include "RenderingSystem/Buffers.h"
#include "RenderingSystem/FRenderer.h"
#include "RenderingSystem/Textures.h"
#include "Systems/TextureSystem/TextureManager.h"


namespace KREngine
{

	FDefaultLitMaterial::FDefaultLitMaterial()
	{

	}

	void FDefaultLitMaterial::Init(int& Slot)
	{
		Shader.reset(FShader::CreateShader(DefaultVertexShaderPath, DefaultFragmentShaderPath));

		Shader->BindShader();
		TexturePathToTextureMap.insert({ "material.Diffuse" , FApplication::GetTextureManager().GetTexture(DiffuseTexture) });
		Shader->SetUniformInt("material.Diffuse", Slot);
		Slot = Slot + 1;
		TexturePathToTextureMap.insert({ "material.Specular" , FApplication::GetTextureManager().GetTexture(SpecularTexture) });
		Shader->SetUniformInt("material.Specular", Slot);
		Slot = Slot + 1;
	
		TexturePathToTextureMap.insert({ "u_Texture" , FApplication::GetTextureManager().GetTexture(u_Texture) });
		Shader->SetUniformInt("u_Texture", Slot);
		Slot = Slot + 1;

		Shader->UnBindShader();

	}


	void FDefaultLitMaterial::Bind(int& Slot)
	{

		Shader->BindShader();

		for (const auto& texture : TexturePathToTextureMap)
		{
			texture.second->BindTexture(Slot);
			Slot = Slot + 1;
		}


	}

	void FDefaultLitMaterial::UnBind()
	{
		Shader->UnBindShader();
	}

	float& FDefaultLitMaterial::GetShininess()
	{
		return Shininess;
	}

	FVector& FDefaultLitMaterial::GetAmbient()
	{
		return Ambient;
	}

	FVector& FDefaultLitMaterial::GetDiffuse()
	{
		return Diffuse;
	}

	FVector& FDefaultLitMaterial::GetSpecular()
	{
		return Specular;
	}

	FDefaultLitMaterial::~FDefaultLitMaterial()
	{

	}




	void FDefaultLitMaterialSystem::Init()
	{
		/*REFACTOR: This should go away asap*/

		Light.Location = EntityManager::GetComponent<FTransformComponent>(1).Transform.GetLocation();


		for (const FEntityHandle Entity : EntityHandles)
		{
			if (EntityManager::HasComponent<DefaultLitMaterialComponent>(Entity))
			{
				auto& material = EntityManager::GetComponent<DefaultLitMaterialComponent>(Entity).Material;

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

	void FDefaultLitMaterialSystem::Run(const FCamera& mainCamera, const std::shared_ptr<FRenderer>& renderer)
	{


		/*Default shader update */
		const glm::mat4 ViewProjection = mainCamera.ViewProjection;


		const glm::mat4 WorldProjection = glm::perspective(glm::radians(45.0f), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 10000.0f);

			for (const FEntityHandle Entity : EntityHandles)
			{
				if (EntityManager::HasComponent<DefaultLitMaterialComponent>(Entity) && EntityManager::HasComponent<FTransformComponent>(Entity) && EntityManager::HasComponent<FStaticMesh>(Entity))
				{
					auto& static_mesh = EntityManager::GetComponent<FStaticMesh>(Entity);
					const auto& model_projection = EntityManager::GetComponent<FTransformComponent>(Entity).ModelProjection;
					FDefaultLitMaterial& material = EntityManager::GetComponent<DefaultLitMaterialComponent>(Entity).Material;
					std::shared_ptr<FShader>& shader = material.Shader;
					if (shader)
					{
						
						int slot = 0;
						material.Bind(slot);

						shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);
						shader->SetUniformMat4("u_Model", /*ViewProjection **/model_projection);
						shader->SetUniform3f("u_LightPos", Light.Location);
						shader->SetUniform3f("Light.u_LightDirection", Light.Direction);
						material.SetShininess(Light.Shininess);
						
						shader->SetUniform3f("u_CameraPos", FVector::AsVec3(mainCamera.CameraPosition));
						shader->SetUniform4f("u_ObjectColor", vec4(Color.r, Color.g, Color.b, Color.a));
						shader->SetUniform4f("u_LightColor", vec4(Light.LightColor.r, Light.LightColor.g, Light.LightColor.b, Light.LightColor.a));
						shader->SetUniformF("material.Shininess", 32);
						
						static_mesh.VertexArray->BindBuffer();
						
						// 3 vertex two triangles.
						renderer->Draw(static_cast<int>(static_mesh.IndexBufferData->GetIndexBufferCount()));
					//	(glDrawElements(GL_TRIANGLES, , GL_UNSIGNED_INT, nullptr));
						static_mesh.VertexArray->UnBindBuffer();
						material.UnBind();
					}
				}
			}
		
	}


	void FDefaultLitMaterialSystem::End()
	{
	}

	void FDefaultLitMaterialSystem::GUIRun()
	{
		ImGui::Begin("TESTING MENU");
		IMGUI_LEFT_LABEL(ImGui::DragFloat4("##LightColor", &Light.LightColor.r, 0.01, -1, 1), "LightColor", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat4("##ObjectColor", &Color.r, 0.01, -1, 1), "ObjectColor", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat("##Shininess", &Light.Shininess, 2, 2, 1024), "Shininess", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Direction", &Light.Direction.x), "Direction", );
		ImGui::End();
		
	}
}
