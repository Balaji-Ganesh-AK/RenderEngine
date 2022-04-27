#include "Line.h"

#include "GameManager.h"
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
			
				auto& line = EntityManager::GetComponent<FLine>(entityHandle);
				line.Shader.reset(FShader::CreateShader(DefaultVertexShaderPath, DefaultFragmentShaderPath));

				line.Shader->BindShader();
				line.VertexArray = FVertexArray::Create();
				VertexBuffer.push_back(line.StartLocation.x);
				VertexBuffer.push_back(line.StartLocation.y);
				VertexBuffer.push_back(line.StartLocation.z);
				VertexBuffer.push_back(line.EndLocation.x);
				VertexBuffer.push_back(line.EndLocation.y);
				VertexBuffer.push_back(line.EndLocation.z);
			/*	vertexpos[0] = &line.StartLocation.x;
				vertexpos[1] = &line.StartLocation.y;
				vertexpos[2] = &line.StartLocation.z;
				vertexpos[3] = &line.EndLocation.x;
				vertexpos[4] = &line.EndLocation.y;
				vertexpos[5] = &line.EndLocation.z;*/
				line.VertexBufferData = FVertexBuffer::CreateVertexBuffer(VertexBuffer.data(), VertexBuffer.size());
				line.VertexArray->SetLayOut(layout);
				line.VertexArray->BindBufferLayout();
				line.VertexArray->UnBindBuffer();
				line.Shader->UnBindShader();
		}
	}

	void FLineSystem::Run(const FCameraComponent& mainCamera, const std::shared_ptr<FRenderer>& renderer)
	{
		const glm::mat4 ViewProjection = mainCamera.ViewProjection;
		const glm::mat4 WorldProjection = glm::perspective(glm::radians(45.0f), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 10000.0f);
		for(auto entityHandle: EntityHandles)
		{
			auto& line = EntityManager::GetComponent<FLine>(entityHandle);
			
			const auto& model_projection = EntityManager::GetComponent<FTransformComponent>(entityHandle).ModelProjection;
			line.Shader->BindShader();
			line.Shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);
			line.Shader->SetUniformMat4("u_Model", /*ViewProjection **/model_projection);
			line.VertexArray->BindBuffer();
			renderer->DrawLine(line.StartLocation, line.EndLocation);
			line.VertexArray->UnBindBuffer();
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
