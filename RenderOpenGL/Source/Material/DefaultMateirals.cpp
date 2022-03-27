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
#include "Systems/AssetSystem/AssetSystem.h"
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


	FDefaultLitMaterial::~FDefaultLitMaterial()
	{

	}




	void FDefaultLitMaterialSystem::Init()
	{
		/*REFACTOR: This should go away asap*/
		FScopedTimer Timer("Default lit system init");
		//DirectionalLight.Location = EntityManager::GetComponent<FTransformComponent>(0).Transform.GetLocation();

		/*TODO: extract this function to read the file and return the layout used fo this mesh*/
		VertexBufferLayout layout{
						BufferElement{"v_Pos", EShaderDataType::FVec3, true},
						BufferElement{"v_Texture", EShaderDataType::FVec2, true},
						BufferElement{"v_Normal", EShaderDataType::FVec3, true},
						//BufferElement{"v_Normal", EShaderDataType::FVec3, true},
		};

		for (const FEntityHandle Entity : EntityHandles)
		{
			if (EntityManager::HasComponent<DefaultLitMaterialComponent>(Entity))
			{
				auto& material = EntityManager::GetComponent<DefaultLitMaterialComponent>(Entity).Material;

				int slot = 0;
				material.Init(slot);
			
				/*TODO fetch all the entities with static mesh component
				 * TODO: Should work for runtime after setting up event system.
				 */
				auto& static_mesh = EntityManager::GetComponent<FStaticMesh>(Entity);

					static_mesh.VertexArray = FVertexArray::Create();

				/*Check if we vertex pos count tex cord count and normal count matches, if not mark the component and don't draw it */
				if(static_mesh.Model->VertexPosition.size() == static_mesh.Model->TexCord.size() && static_mesh.Model->VertexPosition.size() == static_mesh.Model->Normal.size())
				{
					for (int i = 0; i < static_mesh.Model->VertexPosition.size(); i++)
					{

						static_mesh.VertexBuffer.push_back(static_mesh.Model->VertexPosition[i].x);
						static_mesh.VertexBuffer.push_back(static_mesh.Model->VertexPosition[i].y);
						static_mesh.VertexBuffer.push_back(static_mesh.Model->VertexPosition[i].z);
						static_mesh.VertexBuffer.push_back(static_mesh.Model->TexCord[i].x);
						static_mesh.VertexBuffer.push_back(static_mesh.Model->TexCord[i].y);
						static_mesh.VertexBuffer.push_back(static_mesh.Model->Normal[i].x);
						static_mesh.VertexBuffer.push_back(static_mesh.Model->Normal[i].y);
						static_mesh.VertexBuffer.push_back(static_mesh.Model->Normal[i].z);

					}

				}
				else
				{
					Logger::Error("Mesh does not look good, please check the mesh! ");
					for (int i = 0; i < static_mesh.Model->VertexPosition.size(); i++)
					{

						static_mesh.VertexBuffer.push_back(0);
						static_mesh.VertexBuffer.push_back(0);
						static_mesh.VertexBuffer.push_back(0);
						static_mesh.VertexBuffer.push_back(0);
						static_mesh.VertexBuffer.push_back(0);
						static_mesh.VertexBuffer.push_back(0);
						static_mesh.VertexBuffer.push_back(0);
						static_mesh.VertexBuffer.push_back(0);

					}
				}
					
			

					//static_mesh.VertexBufferData.reset(FVertexBuffer::CreateVertexBuffer(static_mesh.Positions, sizeof(static_mesh.Positions) / sizeof(float)));
					//static_mesh.IndexBufferData.reset(FIndexBuffer::CreateIndexBuffer(static_mesh.Indices, sizeof(static_mesh.Indices) / sizeof(unsigned int)));
				static_mesh.VertexBufferData = FVertexBuffer::CreateVertexBuffer(static_mesh.VertexBuffer.data(), static_mesh.VertexBuffer.size());
				static_mesh.IndexBufferData = FIndexBuffer::CreateIndexBuffer(static_mesh.Model->Indices, sizeof(static_mesh.Model->Indices) / sizeof(unsigned int));

					static_mesh.VertexArray->SetLayOut(layout);
					static_mesh.VertexArray->BindBufferLayout();
				
					static_mesh.VertexArray->UnBindBuffer();
					material.UnBind();
				
			}
		}

	}

	void FDefaultLitMaterialSystem::Run(const FCamera& mainCamera, const std::shared_ptr<FRenderer>& renderer)
	{


		/*Default shader update */
		const glm::mat4 ViewProjection = mainCamera.ViewProjection;

		std::vector< glm::mat4> Translations;
		const glm::mat4 WorldProjection = glm::perspective(glm::radians(45.0f), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 10000.0f);

			for (const FEntityHandle Entity : EntityHandles)
			{
				if (EntityManager::HasComponent<DefaultLitMaterialComponent>(Entity) && EntityManager::HasComponent<FTransformComponent>(Entity) && EntityManager::HasComponent<FStaticMesh>(Entity))
				{
					auto& static_mesh = EntityManager::GetComponent<FStaticMesh>(Entity);
					const glm::mat4& model_projection = EntityManager::GetComponent<FTransformComponent>(Entity).
						ModelProjection;
					FDefaultLitMaterial& material = EntityManager::GetComponent<DefaultLitMaterialComponent>(Entity).Material;
					std::shared_ptr<FShader>& shader = material.Shader;
					if (shader)
					{
						
						int slot = 0;
						material.Bind(slot);

						shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);
						shader->SetUniformMat4("u_Model", /*ViewProjection **/model_projection);
						if(PointLight)
						{
							
							shader->SetUniformInt("CurrentPointLightCount", 1);
						}
						else
						{
							shader->SetUniformInt("CurrentPointLightCount", 0);
						}
						shader->SetUniform3f("DirectionalLight.Diffuse", vec3(DirectionalLight.DiffuseColor.r, DirectionalLight.DiffuseColor.g, DirectionalLight.DiffuseColor.b));
						shader->SetUniform3f("DirectionalLight.Ambient", vec3(DirectionalLight.AmbientColor.r, DirectionalLight.AmbientColor.g, DirectionalLight.AmbientColor.b));
						shader->SetUniform3f("DirectionalLight.Specular", vec3(DirectionalLight.SpecularColor.r, DirectionalLight.SpecularColor.g, DirectionalLight.SpecularColor.b));
						shader->SetUniform3f("DirectionalLight.Direction", DirectionalLight.Direction);

						
						
						shader->SetUniformF("material.Shininess", material.GetShininess());
						shader->SetUniform3f("CameraPosition", FVector::AsVec3(mainCamera.CameraPosition));
						shader->SetUniform3f("CameraFront",vec3(-mainCamera.CameraFront.x, -mainCamera.CameraFront.y, -mainCamera.CameraFront.z));
						shader->SetUniform3f("u_CameraPos", FVector::AsVec3(mainCamera.CameraPosition));
						shader->SetUniform4f("u_ObjectColor", vec4(Color.r, Color.g, Color.b, Color.a));


						//if(EntityManager::HasComponent<FPointLight>(Entity))
						
							
							
							/*REFACTOR Should have a function that finds all relative point lights*/
							
							//"PointLights[" + id.to_string() + "]//
						shader->SetUniform3f("PointLights[0].Diffuse", vec3(Light.DiffuseColor.r, Light.DiffuseColor.g, Light.DiffuseColor.b));
						shader->SetUniform3f("PointLights[0].Ambient", vec3(Light.AmbientColor.r, Light.AmbientColor.g, Light.AmbientColor.b));
						shader->SetUniform3f("PointLights[0].Specular", vec3(Light.SpecularColor.r, Light.SpecularColor.g, Light.SpecularColor.b));
							shader->SetUniform3f("PointLights[0].Position", EntityManager::GetComponent<FTransformComponent>(0).Transform.GetLocation());
							shader->SetUniformF("PointLights[0].Constant", Light.Constant);
							shader->SetUniformF("PointLights[0].Linear", Light.Linear);
							shader->SetUniformF("PointLights[0].Quadratic", Light.Quadratic/10000);
						
							////shader->SetUniform3f("Light.Direction", Light.Direction);
							//shader->SetUniformF("Light.OuterCutOff", glm::cos(glm::radians(12.5f)));
							//shader->SetUniformF("Light.CutOff", glm::cos(glm::radians(8.5f)));
							//material.SetShininess(Light.Shininess);
						
						
						
						Translations.push_back(model_projection);
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


	void FDefaultLitMaterialSystem::End()
	{
	}

	void FDefaultLitMaterialSystem::GUIRun()
	{
		ImGui::Begin("Light MENU");
		IMGUI_LEFT_LABEL(ImGui::DragFloat4("##Ambient Color", &DirectionalLight.AmbientColor.r, 0.1, -1, 1), "Ambient Color", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat4("##Diffuse Color", &DirectionalLight.DiffuseColor.r, 0.1, -1, 1), "Diffuse Color", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat4("##Specular Color", &DirectionalLight.SpecularColor.r, 0.1, -1, 1), "Specular Color", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Direction", &DirectionalLight.Direction.x, 0.1, -1, 1), "Direction", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat4("##ObjectColor", &Color.r, 0.1, -1, 1), "ObjectColor", );
		//IMGUI_LEFT_LABEL(ImGui::DragFloat("##Shininess", &Light.Shininess, 2, 2, 1024), "Shininess", );
		//IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Point light Position", &Light.Position.x), "Position", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat("##AttenutaionLinear", &Light.Linear, 0.001, 0, 1), "Linear", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat("##AttenutaionQuad", &Light.Quadratic, 1, 0, 10000), "Quad", );
		IMGUI_LEFT_LABEL(ImGui::Checkbox("##Point Light?", &PointLight), "Point light", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat4("##Point light Ambient Color", &Light.AmbientColor.r, 0.1, -1, 1), "Point light Ambient Color", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat4("##Point light Diffuse Color", &Light.DiffuseColor.r, 0.1, -1, 1), "Point light Diffuse Color", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat4("##Point light Specular Color", &Light.SpecularColor.r, 0.1, -1, 1), "Point light Specular Color", );
		ImGui::End();
		
	}
}
