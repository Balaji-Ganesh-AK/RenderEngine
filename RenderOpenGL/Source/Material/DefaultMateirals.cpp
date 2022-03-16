#include "DefaultMateirals.h"

#include "GameManager.h"
#include "Entity/Components/TransformComponent.h"
#include "glm/gtx/transform.hpp"
#include "RenderingSystem/FRenderingSystem.h"
#include "RenderingSystem/WindowsWindow.h"
#include "Runtime/Camera/FCamera.h"
#include "Math/Color.h"
#include "RenderingSystem/Buffers.h"
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



	}


	void FDefaultLitMaterial::Bind(int& Slot)
	{

		//Shader->BindShader();

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
			}
		}
		Framebuffer.reset(FFrameBuffer::CreateFrameBuffer(FApplication::Get().GetWindowsWindow()->Properties->GetWidth(),
			FApplication::Get().GetWindowsWindow()->Properties->GetHeight()));
	}

	void FDefaultLitMaterialSystem::Run(const FCamera& mainCamera)
	{
		Framebuffer->BindBuffer();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);


		/*Default shader update */
		const glm::mat4 ViewProjection = mainCamera.ViewProjection;


		const glm::mat4 WorldProjection = glm::perspective(glm::radians(45.0f), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 10000.0f);

		if (mainCamera.bMainCamera)
		{

			for (const FEntityHandle Entity : EntityHandles)
			{
				if (EntityManager::HasComponent<DefaultLitMaterialComponent>(Entity) && EntityManager::HasComponent<FTransformComponent>(Entity) && EntityManager::HasComponent<FStaticMesh>(Entity))
				{
					const FStaticMesh& static_mesh = EntityManager::GetComponent<FStaticMesh>(Entity);
					const auto& model_projection = EntityManager::GetComponent<FTransformComponent>(Entity).ModelProjection;
					FDefaultLitMaterial& material = EntityManager::GetComponent<DefaultLitMaterialComponent>(Entity).Material;
					std::shared_ptr<FShader>& shader = material.Shader;
					if (shader)
					{
						
						shader->BindShader();
						// hader->SetUniform4f( "u_Color", vec4( clear_color.x, clear_color.y, clear_color.z, clear_color.w ) );
						//Shader->SetUniform4f( "u_ObjectColor",vec4(Color.r,Color.g,Color.b, Color.a) );
						// Shader->SetUniform4f( "u_Color",vec4( GlobalLight.GetShaderColor().r, GlobalLight.GetShaderColor().g, GlobalLight.GetShaderColor().b, GlobalLight.GetShaderColor().a) );

						shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);
						shader->SetUniformMat4("u_Model", /*ViewProjection **/model_projection);
						shader->SetUniform3f("u_LightPos", Light.Location);
						shader->SetUniform3f("Light.u_LightDirection", Light.Direction);
						material.SetShininess(Light.Shininess);
						shader->SetUniformF("material.Specular", material.GetShininess());
						shader->SetUniform3f("u_CameraPos", FVector::AsVec3(mainCamera.CameraPosition));
						shader->SetUniform4f("u_ObjectColor", vec4(Color.r, Color.g, Color.b, Color.a));
						shader->SetUniform4f("u_LightColor", vec4(Light.LightColor.r, Light.LightColor.g, Light.LightColor.b, Light.LightColor.a));
						shader->SetUniformF("material.Shininess", 32);

						int slot = 0;
						material.Bind(slot);
				
						//glfwPollEvents();
						int32 DrawCallCount{ 0 };

						const glm::mat4 ViewProjection = mainCamera.ViewProjection;
						static_mesh.VertexArray->BindBuffer();
						DrawCallCount++;
						// 3 vertex two triangles.
						(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr));
						

					}
				}
			}
		}
		else
		{
			Logger::Error("No main camera found! ");
		}
		Framebuffer->UnBindBuffer();
	}


	void FDefaultLitMaterialSystem::End()
	{
	}

	void FDefaultLitMaterialSystem::GUIRun()
	{
/*		ImGui::Begin("TESTING MENU");
		IMGUI_LEFT_LABEL(ImGui::DragFloat4("##LightColor", &Light.LightColor.r, 0.01, -1, 1), "LightColor", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat4("##ObjectColor", &Color.r, 0.01, -1, 1), "ObjectColor", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat("##Shininess", &Light.Shininess, 2, 2, 1024), "Shininess", );
		IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Direction", &Light.Direction.x), "Direction", );
		ImGui::End()*/;
		{
			SCOPED_TIMER("Screen frame buffer");
			ImGui::Begin("ScreenPort");
			if (test != FApplication::Get().GetWindowsWindow()->Properties->GetWidth())
			{
				test = FApplication::Get().GetWindowsWindow()->Properties->GetWidth();
				Framebuffer->OnWindowResize(static_cast<float>(FApplication::Get().GetWindowsWindow()->Properties->GetWidth()), static_cast<float>(FApplication::Get().GetWindowsWindow()->Properties->GetHeight()));
			}

			const uint32 textureID = Framebuffer->GetTextureRendererID();
			auto WindowSize = ImGui::GetWindowSize();
			ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ static_cast<float>(FApplication::Get().GetWindowsWindow()->Properties->GetWidth()),static_cast<float>(FApplication::Get().GetWindowsWindow()->Properties->GetHeight()) }/*, ImVec2( 0, 1 ), ImVec2( 0, 1 )*/);
			ImGui::End();

		}
	}
}
