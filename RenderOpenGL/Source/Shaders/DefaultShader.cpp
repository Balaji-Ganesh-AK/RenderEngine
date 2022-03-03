#include "DefaultShader.h"

#include "GameManager.h"
#include "Entity/Components/TransformComponent.h"
#include "glm/gtx/transform.hpp"
#include "RenderingSystem/FRenderingSystem.h"
#include "RenderingSystem/WindowsWindow.h"
#include "Runtime/Camera/FCamera.h"
#include "Math/Color.h"


namespace KREngine
{
	void FDefaultUnLitShader::Init()
	{
		/*Create the shader here*/
			/*Goes into camera component*/
		for (const FEntityHandle Entity : EntityHandles)
		{
			if(EntityManager::HasComponent<FMaterialComponent>(Entity))
			{
				auto& material = EntityManager::GetComponent<FMaterialComponent>(Entity).Material;

				int slot = 0;
				material.Init(slot);
			}
		}
	}

	void FDefaultUnLitShader::Run(const FCamera& mainCamera)
	{
		/*Default shader update */
		const glm::mat4 ViewProjection = mainCamera.ViewProjection;

		const glm::mat4 WorldProjection = glm::perspective(glm::radians(45.0f), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 100.0f);
		int slot = 0;
		if (mainCamera.bMainCamera)
		{

			for (const FEntityHandle Entity : EntityHandles)
			{
				if (EntityManager::HasComponent<FDefaultUnLitShaderComponent>(Entity)&& EntityManager::HasComponent<FMaterialComponent>(Entity) && EntityManager::HasComponent<FTransformComponent>(Entity))
				{
					const auto& model_projection = EntityManager::GetComponent<FTransformComponent>(Entity).ModelProjection;
					FMaterials& material = EntityManager::GetComponent<FMaterialComponent>(Entity).Material;
					std::shared_ptr<FShader>& shader = material.Shader;
					if (shader)
					{
						int slot = 0;
						material.Bind(slot);
						slot++;
						// hader->SetUniform4f( "u_Color", vec4( clear_color.x, clear_color.y, clear_color.z, clear_color.w ) );
						//Shader->SetUniform4f( "u_ObjectColor",vec4(Color.r,Color.g,Color.b, Color.a) );
						// Shader->SetUniform4f( "u_Color",vec4( GlobalLight.GetShaderColor().r, GlobalLight.GetShaderColor().g, GlobalLight.GetShaderColor().b, GlobalLight.GetShaderColor().a) );
						shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);
						shader->SetUniformMat4("u_Model", /*ViewProjection**/ model_projection);
						/*Shader->SetUniform3f("u_LightPos", RenderingObjectList[1].Transform.GetLocation());*/
						shader->SetUniform3f("u_CameraPos", FVector::AsVec3(mainCamera.CameraPosition));
						shader->SetUniform4f("u_ObjectColor", vec4(Color.r, Color.g, Color.b, Color.a));
					}
				}
			}

		}
	}

	void FDefaultUnLitShader::End()
	{
		/*All clean ups */
	}

	void FDefaultLitShader::Init()
	{
		/*REFACTOR: This should go away asap*/

		Light.Location = EntityManager::GetComponent<FTransformComponent>(1).Transform.GetLocation();


		for (const FEntityHandle Entity : EntityHandles)
		{
			if (EntityManager::HasComponent<FMaterialComponent>(Entity))
			{
				auto& material = EntityManager::GetComponent<FMaterialComponent>(Entity).Material;

				int slot = 0;
				material.Init(slot);
			}
		}
	}

	void FDefaultLitShader::Run(const FCamera& mainCamera)
	{
		/*Default shader update */
		const glm::mat4 ViewProjection = mainCamera.ViewProjection;

		const glm::mat4 WorldProjection = glm::perspective(glm::radians(45.0f), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 100.0f);
		/*REFACTOR: This should go away asap*/
		if (EntityManager::HasComponent<FMaterialComponent>(0)&& EntityManager::HasComponent<FDefaultShaderComponent>(0) &&  (EntityManager::HasComponent<FDefaultShaderComponent>(1)))
		{
			/*if(EntityManager::GetComponent<FMaterialComponent>(0).Shader&& EntityManager::GetComponent<FMaterialComponent>(1).Shader)
			{
				
			EntityManager::GetComponent<FMaterialComponent>(0).Shader->BindShader();
		EntityManager::GetComponent<FMaterialComponent>(0).Shader->SetUniformInt("u_Light", 0);

		EntityManager::GetComponent<FMaterialComponent>(1).Shader->BindShader();
		EntityManager::GetComponent<FMaterialComponent>(1).Shader->SetUniformInt("u_Light", 1);
		EntityManager::GetComponent<FMaterialComponent>(1).Shader->SetUniform4f("u_LightColor", vec4(Light.LightColor.r, Light.LightColor.r, Light.LightColor.r, Light.LightColor.a));
			}*/
		}
		if (mainCamera.bMainCamera)
		{
			int slot = 0;
			for (const FEntityHandle Entity : EntityHandles)
			{
				
				if (EntityManager::HasComponent<FDefaultShaderComponent>(Entity) && EntityManager::HasComponent<FMaterialComponent>(Entity) && EntityManager::HasComponent<FTransformComponent>(Entity))
				{
					const auto& model_projection = EntityManager::GetComponent<FTransformComponent>(Entity).ModelProjection;
					FMaterials& material = EntityManager::GetComponent<FMaterialComponent>(Entity).Material;
					std::shared_ptr<FShader>& shader = material.Shader;
					if (shader)
					{
						
						material.Bind(slot);
						slot++;
						// hader->SetUniform4f( "u_Color", vec4( clear_color.x, clear_color.y, clear_color.z, clear_color.w ) );
						//Shader->SetUniform4f( "u_ObjectColor",vec4(Color.r,Color.g,Color.b, Color.a) );
						// Shader->SetUniform4f( "u_Color",vec4( GlobalLight.GetShaderColor().r, GlobalLight.GetShaderColor().g, GlobalLight.GetShaderColor().b, GlobalLight.GetShaderColor().a) );
					
						shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);
						shader->SetUniformMat4("u_Model", /*ViewProjection**/ model_projection);
						shader->SetUniform3f("u_LightPos", Light.Location);
						shader->SetUniformF("material.Specular", 32);
						shader->SetUniform3f("u_CameraPos", FVector::AsVec3(mainCamera.CameraPosition));
						shader->SetUniform4f("u_ObjectColor", vec4(Color.r, Color.g, Color.b, Color.a));
					}
				}
			}

		}
	}

	void FDefaultLitShader::End()
	{
	}
}
