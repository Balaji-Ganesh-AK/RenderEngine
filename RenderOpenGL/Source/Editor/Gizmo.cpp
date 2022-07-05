#include "Gizmo.h"

#include "GameManager.h"
#include "Entity/Components/TransformComponent.h"
#include "RenderingSystem/Buffers.h"
#include "RenderingSystem/FRenderer.h"
#include "RenderingSystem/Shader.h"
#include "RenderingSystem/WindowsWindow.h"
#include "glm/gtx/transform.hpp"
#include "Runtime/Camera/FCameraComponent.h"

namespace KREngine
{
	void FGizmo::SetLocation(FVector location)
	{
		Axes[0].SetStartLocation(location);
		Axes[1].SetStartLocation(location);
		Axes[2].SetStartLocation(location);
	}

	FGizmoSystem::~FGizmoSystem()
	{
	}

	void FGizmoSystem::Init()
	{
		
		VertexBufferLayout layout{
							BufferElement{"v_Pos", EShaderDataType::FVec3, true},
							BufferElement{"v_Color", EShaderDataType::FVec4, true},
		};
		for (auto entityHandle : EntityHandles)
		{

			auto& gizmo = EntityManager::GetComponent<FGizmo>(entityHandle);
			gizmo.Shader.reset(FShader::CreateShader(DefaultVertexShaderPath, DefaultFragmentShaderPath));

			gizmo.Shader->BindShader();
			gizmo.VertexArray = FVertexArray::Create();

			for(const FLine& axis: gizmo.Axes)
			{
				gizmo.VertexBuffer.push_back(axis.GetStartLocation().x);
				gizmo.VertexBuffer.push_back(axis.GetStartLocation().y);
				gizmo.VertexBuffer.push_back(axis.GetStartLocation().z);
				
				gizmo.VertexBuffer.push_back(axis.GetColor().r);
				gizmo.VertexBuffer.push_back(axis.GetColor().g);
				gizmo.VertexBuffer.push_back(axis.GetColor().b);
				gizmo.VertexBuffer.push_back(axis.GetColor().a);

				gizmo.VertexBuffer.push_back(axis.GetEndLocation().x);
				gizmo.VertexBuffer.push_back(axis.GetEndLocation().y);
				gizmo.VertexBuffer.push_back(axis.GetEndLocation().z);

				gizmo.VertexBuffer.push_back(axis.GetColor().r);
				gizmo.VertexBuffer.push_back(axis.GetColor().g);
				gizmo.VertexBuffer.push_back(axis.GetColor().b);
				gizmo.VertexBuffer.push_back(axis.GetColor().a);
			}
		




			gizmo.VertexBufferData = FVertexBuffer::CreateVertexBuffer(gizmo.VertexBuffer.data(), gizmo.VertexBuffer.size());
			gizmo.VertexArray->SetLayOut(layout);
			gizmo.VertexArray->BindBufferLayout();
			gizmo.VertexArray->UnBindBuffer();
			gizmo.Shader->UnBindShader();
		}
	}

	void FGizmoSystem::Run(const FCameraComponent& mainCamera, const std::shared_ptr<FRenderer>& renderer)
	{
		const glm::mat4 ViewProjection = mainCamera.ViewProjection;
		const glm::mat4 WorldProjection = glm::perspective(glm::radians(45.0f), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 10000.0f);
		for (const auto entityHandle : EntityHandles)
		{
			auto& gizmo = EntityManager::GetComponent<FGizmo>(entityHandle);

			const auto& model_projection = EntityManager::GetComponent<FTransformComponent>(entityHandle).ModelProjection;
			if(gizmo.Shader && gizmo.bNeedsToRender)
			{
				
			gizmo.Shader->BindShader();
			gizmo.Shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);
			gizmo.Shader->SetUniformMat4("u_Model", /*ViewProjection **/model_projection);

			gizmo.VertexArray->BindBuffer();
			renderer->DrawLine(gizmo.VertexBuffer.size());
			gizmo.VertexArray->UnBindBuffer();
			}
			
			
		
		}
	}

	void FGizmoSystem::End()
	{
		FSystem::End();
	}

	void FGizmoSystem::GUIInit()
	{
		FSystem::GUIInit();
	}

	void FGizmoSystem::GUIRun()
	{
		FSystem::GUIRun();
	}

	void FGizmoSystem::GUIEnd()
	{
		FSystem::GUIEnd();
	}
}
