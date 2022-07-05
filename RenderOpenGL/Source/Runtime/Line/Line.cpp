#include "Line.h"

#include "GameManager.h"
#include "Ray.h"
#include "Entity/Components/TransformComponent.h"
#include "RenderingSystem/Buffers.h"
#include "RenderingSystem/FRenderer.h"
#include "RenderingSystem/Shader.h"
#include "Runtime/Camera/FCameraComponent.h"
#include "glm/gtx/transform.hpp"
#include "RenderingSystem/WindowsWindow.h"

namespace KREngine
{
	FLineSystem::~FLineSystem()
	{
	}

	void FLineSystem::Init()
	{
		FSystem::Init();
		VertexBufferLayout layout{
							BufferElement{"v_Pos", EShaderDataType::FVec3, true},
		};
		for (auto entityHandle : EntityHandles)
		{
			if(EntityManager::HasComponent<FLine>(entityHandle))
			{
				auto& line = EntityManager::GetComponent<FLine>(entityHandle);
				line.Shader.reset(FShader::CreateShader(DefaultVertexShaderPath, DefaultFragmentShaderPath));

				line.Shader->BindShader();
				line.VertexArray = FVertexArray::Create();
				line.VertexBuffer.push_back(line.StartLocation.x);
				line.VertexBuffer.push_back(line.StartLocation.y);
				line.VertexBuffer.push_back(line.StartLocation.z);
				line.VertexBuffer.push_back(line.EndLocation.x);
				line.VertexBuffer.push_back(line.EndLocation.y);
				line.VertexBuffer.push_back(line.EndLocation.z);
				line.VertexBufferData = FVertexBuffer::CreateVertexBuffer(line.VertexBuffer.data(), line.VertexBuffer.size());
				line.VertexArray->SetLayOut(layout);
				line.VertexArray->BindBufferLayout();
				line.VertexArray->UnBindBuffer();
				line.Shader->UnBindShader();
			}

			if (EntityManager::HasComponent<FRay>(entityHandle))
			{
				auto& ray = EntityManager::GetComponent<FRay>(entityHandle);
				ray.Shader.reset(FShader::CreateShader(DefaultVertexShaderPath, DefaultFragmentShaderPath));

				ray.Shader->BindShader();
				ray.Shader->SetUniform4f("u_LineColor", ray.Color);
				ray.VertexArray = FVertexArray::Create();
				ray.VertexBuffer.push_back(0);
				ray.VertexBuffer.push_back(0);
				ray.VertexBuffer.push_back(0);
				ray.VertexBuffer.push_back(ray.EndLocation.x);
				ray.VertexBuffer.push_back(ray.EndLocation.y);
				ray.VertexBuffer.push_back(ray.EndLocation.z);
				ray.VertexBufferData = FVertexBuffer::CreateVertexBuffer(ray.VertexBuffer.data(), ray.VertexBuffer.size());
				ray.VertexArray->SetLayOut(layout);
				ray.VertexArray->BindBufferLayout();
				ray.VertexArray->UnBindBuffer();
				ray.Shader->UnBindShader();

			}
		}


	}

	void FLineSystem::Run(const FCameraComponent& mainCamera, const std::shared_ptr<FRenderer>& renderer)
	{
		const glm::mat4 ViewProjection = mainCamera.ViewProjection;
		const glm::mat4 WorldProjection = glm::perspective(glm::radians(45.0f), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 10000.0f);
		for(auto entityHandle: EntityHandles)
		{
			if (EntityManager::HasComponent<FLine>(entityHandle))
			{
				auto& line = EntityManager::GetComponent<FLine>(entityHandle);

				const auto& model_projection = EntityManager::GetComponent<FTransformComponent>(entityHandle).ModelProjection;
				line.Shader->BindShader();
				line.Shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);
				line.Shader->SetUniformMat4("u_Model", /*ViewProjection **/model_projection);
				line.Shader->SetUniform4f("u_LineColor", line.Color);
				line.VertexArray->BindBuffer();
				renderer->DrawLine(line.VertexBuffer.size());
				line.VertexArray->UnBindBuffer();
			}

			if (EntityManager::HasComponent<FRay>(entityHandle))
			{
				auto& ray = EntityManager::GetComponent<FRay>(entityHandle);

				const auto& model_projection = EntityManager::GetComponent<FTransformComponent>(entityHandle).ModelProjection;
				ray.Shader->BindShader();
				ray.Shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);
				ray.Shader->SetUniformMat4("u_Model", /*ViewProjection **/model_projection);
				ray.Shader->SetUniform4f("u_LineColor", ray.Color);
				ray.VertexArray->BindBuffer();
				renderer->DrawLine(ray.VertexBuffer.size());
				ray.VertexArray->UnBindBuffer();
			}
		}
		
	}

	void FLineSystem::End()
	{
		FSystem::End();
	}

	void FLineSystem::GUIInit()
	{
		FSystem::GUIInit();
	}

	void FLineSystem::GUIRun()
	{
		FSystem::GUIRun();
	}

	void FLineSystem::GUIEnd()
	{
		FSystem::GUIEnd();
	}
}
