#include "FRenderingSystem.h"

#include "Buffers.h"
#include "FRenderer.h"
#include "GameManager.h"
#include "Shader.h"
#include "WindowsWindow.h"
#include "Entity/Components/TransformComponent.h"
#include "glm/gtx/transform.hpp"
#include "ImGUI/imgui.h"
#include "Material/DefaultMateirals.h"
#include "Material/DefaultUnlitMaterial.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"
#include "Runtime/Camera/FCameraComponent.h"
#include "RenderingSystem/FRenderer.h"
#include "Runtime/Foliage/Foliage.h"
#include "Runtime/Line/Line.h"
#include "Systems/ShaderSystem/ShaderSystem.h"
 

using namespace KREngine;

FRenderingSystem::FRenderingSystem()
{

	StaticMeshSystem = EntityManager::RegisterSystem<FStaticMeshSystem>();
	TransformSystem = EntityManager::RegisterSystem<FTransformSystem>();
	DefaultShaderSystem = EntityManager::RegisterSystem<FDefaultUnLitMaterialSystem>();
	DefaultLitShaderSystem = EntityManager::RegisterSystem<FDefaultLitMaterialSystem>();
	FoliageSystem = EntityManager::RegisterSystem<FFoliageSystem>();
	LineSystem = EntityManager::RegisterSystem<FLineSystem>();

	EntityManager::RegisterComponent<FLine>();
	{
		ComponentUID UID;
		UID.set(EntityManager::GetComponentType<FTransformComponent>());
		UID.set(EntityManager::GetComponentType<FLine>());
		EntityManager::SetSystemComponents<FLineSystem>(UID);
	}
	Renderer.reset(FRenderer::CreateRenderer());
}

void FRenderingSystem::Init()
{
	Renderer->Init();
	FoliageSystem->Init();
	DefaultShaderSystem->Init();
	DefaultLitShaderSystem->Init();
	LineSystem->Init();

	Framebuffer.reset(FFrameBuffer::CreateFrameBuffer(FApplication::Get().GetWindowsWindow()->Properties->GetWidth(),
		FApplication::Get().GetWindowsWindow()->Properties->GetHeight()));


	/*shader init*/
	StaticMeshSystem->Init();
	Shader.reset(FShader::CreateShader(DefaultVertexShaderPath, DefaultFragmentShaderPath));

}

void FRenderingSystem::Run(const FCameraComponent& mainCamera, uint32 currentSelectedEntity)
{
	TransformSystem->Run();

	{
		SCOPED_TIMER("Rendering loop");

#if GUI
		Framebuffer->BindBuffer();
#endif
		Renderer->ClearColor();



		const glm::mat4 ViewProjection = mainCamera.ViewProjection;


		if (mainCamera.bMainCamera)
		{
			FoliageSystem->Run(mainCamera, Renderer);
			DefaultShaderSystem->Run(mainCamera, Renderer);
			DefaultLitShaderSystem->Run(mainCamera, Renderer);
			LineSystem->Run(mainCamera, Renderer);
			OutLine(mainCamera, Renderer, currentSelectedEntity);
		}
		else
		{
			Logger::Error("No main camera found! ");
		}
		Framebuffer->UnBindBuffer();


	}
	{
		//SCOPED_TIMER("Buffer Swap");
				/* Poll for and process events */
		
		glfwSwapBuffers(FApplication::Get().GetWindowsWindow()->GetCurrentWindow());
		glfwPollEvents();

	}

}

void FRenderingSystem::Stop()
{
}
#ifdef GUI
void FRenderingSystem::GUIInit()
{
	TransformSystem->GUIInit();
	StaticMeshSystem->GUIInit();
	
}

void FRenderingSystem::GUIStop()
{
}

void FRenderingSystem::GUIRun()
{
	TransformSystem->GUIRun();
	DefaultLitShaderSystem->GUIRun();
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



void FRenderingSystem::OutLine(const FCameraComponent& mainCamera, const std::shared_ptr<FRenderer>& renderer, uint32 currentSelectedEntity) const
{
	const glm::mat4 ViewProjection = mainCamera.ViewProjection;

	std::vector< glm::mat4> Translations;
	const glm::mat4 WorldProjection = glm::perspective(glm::radians(45.0f), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 10000.0f);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);
	if (EntityManager::HasComponent<FTransformComponent>(currentSelectedEntity) && EntityManager::HasComponent<FStaticMesh>(currentSelectedEntity) &&
		(EntityManager::HasComponent<DefaultLitMaterialComponent>(currentSelectedEntity) || EntityManager::HasComponent<DefaultUnLitMaterialComponent>(currentSelectedEntity)))

	{


		FTransform& transform = EntityManager::GetComponent<FTransformComponent>(currentSelectedEntity).Transform;
		auto& model_projection = EntityManager::GetComponent<FTransformComponent>(currentSelectedEntity).ModelProjection;
		model_projection = glm::mat4(1.0f);
		model_projection = glm::translate(model_projection, VectorHelper::AsGLMVec3(transform.GetLocation()));
		model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
		model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
		model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
		model_projection = glm::scale(model_projection, VectorHelper::AsGLMVec3(transform.GetScale() * 1.05f));


		auto& static_mesh = EntityManager::GetComponent<FStaticMesh>(currentSelectedEntity);
		{
			int slot = 0;

			Shader->BindShader();
			Shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);
			Shader->SetUniformMat4("u_Model", /*ViewProjection **/model_projection);
			static_mesh.VertexArray->BindBuffer();
			// 3 vertex two triangles.
			renderer->Draw(static_cast<int>(static_mesh.IndexBufferData->GetIndexBufferCount()));
			//(glDrawElements(GL_TRIANGLES, static_cast<int>(static_mesh.IndexBufferData->GetIndexBufferCount()), GL_UNSIGNED_INT, nullptr));
			static_mesh.VertexArray->UnBindBuffer();
			Shader->UnBindShader();
		}
	}
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glEnable(GL_DEPTH_TEST);
}
#endif
