#include "FRenderingSystem.h"

#include "Buffers.h"
#include "FRenderer.h"
#include "GameManager.h"
#include "Shader.h"
#include "WindowsWindow.h"
#include "Editor/Gizmo.h"
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
#include "Runtime/Sphere/Collider.h"
#include "Systems/Input/Input.h"
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
	GizmoSystem = EntityManager::RegisterSystem<FGizmoSystem>();

	SphereSystem = EntityManager::RegisterSystem< FColliderRenderer>();
	{
		ComponentUID UID;
		UID.set(EntityManager::GetComponentType<FSphereCollider>());
		UID.set(EntityManager::GetComponentType<FTransformComponent>());
		EntityManager::SetSystemComponents<FColliderRenderer>(UID);
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
	SphereSystem->Init();

	Gizmo = KREngine::EntityManager::CreateEntity();
	EntityManager::AddComponent(Gizmo, KREngine::FTransformComponent{});
	EntityManager::AddComponent(Gizmo, KREngine::FGizmo{});

	GizmoSystem->Init();
	FFrameBufferSettings settings(FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), FApplication::Get().GetWindowsWindow()->Properties->GetHeight());
	Framebuffer.reset(FFrameBuffer::CreateFrameBuffer(settings));


	/*shader init*/
	StaticMeshSystem->Init();
	Shader.reset(FShader::CreateShader(DefaultVertexShaderPath, DefaultFragmentShaderPath));

	

}

void FRenderingSystem::Run(const FCameraComponent& mainCamera, FEntityHandle& currentSelectedEntity)
{
	TransformSystem->Run();

	{
		SCOPED_TIMER("Rendering loop");

#if GUI
		Framebuffer->BindBuffer();
#endif
		Renderer->ClearColor();
#if GUI
		/*Renderer->ClearColor()'s glClear wipes the integer id attachment to 0; re-clear it to -1
		 *("no entity") AFTER that, so clicking empty space reads -1 and clears the selection instead
		 *of selecting entity 0.*/
		{
			const int clearEntityId[4] = { -1, 0, 0, 0 };
			glClearBufferiv(GL_COLOR, 1, clearEntityId);
		}
#endif



		const glm::mat4 ViewProjection = mainCamera.ViewProjection;

		
		if (mainCamera.bMainCamera)
		{
			FoliageSystem->Run(mainCamera, Renderer);
			DefaultShaderSystem->Run(mainCamera, Renderer);
			DefaultLitShaderSystem->Run(mainCamera, Renderer);

			// --- Mouse picking ---
			// Read the entity id under the cursor from the id attachment HERE: right after the
			// pickable mesh passes and BEFORE the sphere/line/outline overlays. Those overlay
			// shaders don't write the id output, so drawing them first would scribble garbage
			// over the id buffer and break picking wherever they overlap a mesh.
			// Fire only on a fresh left-click (rising edge) so one click selects exactly one entity.
#if GUI
			/*Gizmo drag takes priority: if it grabs/uses a handle this frame, skip click-to-select.*/
			const bool gizmoUsingMouse = GizmoSystem->UpdateInteraction(mainCamera, currentSelectedEntity);
			const bool bLeftDownInViewport = FApplication::Get().GetInputSystem().IsMouseKeyPressedInViewPort(Input::MouseCode::ButtonLeft);
			if (!gizmoUsingMouse && bLeftDownInViewport && !PreviousLeftMouseDown)
			{
				const Vec2 mousePos = FApplication::Get().GetInputSystem().GetMousePosition();
				const int pickX = static_cast<int>(mousePos.x);
				const int pickY = static_cast<int>(mousePos.y);
				const int fbWidth = static_cast<int>(FApplication::Get().GetWindowsWindow()->Properties->GetWidth());
				const int fbHeight = static_cast<int>(FApplication::Get().GetWindowsWindow()->Properties->GetHeight());
				if (pickX >= 0 && pickY >= 0 && pickX < fbWidth && pickY < fbHeight)
				{
					const int picked = Framebuffer->ReadPixel(1, pickX, pickY);
					if (picked >= 0)
					{
						currentSelectedEntity = static_cast<FEntityHandle>(picked);
					}
					else
					{
						/*Clicked empty space (the id attachment reads -1 there): clear the selection.*/
						currentSelectedEntity = INVALID_ENTITY;
					}
				}
			}
			PreviousLeftMouseDown = bLeftDownInViewport;
#endif

			SphereSystem->RenderRun(mainCamera, Renderer);
			
			LineSystem->Run(mainCamera, Renderer);
			//GizmoSystem->RenderRun(mainCamera, Renderer);
#if GUI
			OutLine(mainCamera, Renderer, static_cast<uint32>(currentSelectedEntity));
			glDisable(GL_DEPTH_TEST);
			GizmoSystem->Run(mainCamera, Renderer);
			glEnable(GL_DEPTH_TEST);
#endif
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

void FRenderingSystem::Run()
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
			//Framebuffer->OnWindowResize(ImGui::GetContentRegionAvail().x, (ImGui::GetContentRegionAvail().y));
			//ImGui::Image(reinterpret_cast<void*>(textureID), ImGui::GetContentRegionAvail()/*, ImVec2( 0, 1 ), ImVec2( 0, 1 )*/);
		}
		
		const uint32 textureID = Framebuffer->GetTextureRendererID();

		const auto imgui_cursor_pos = ImGui::GetCursorPos();
		Vec2 viewport_offset{ imgui_cursor_pos.x, imgui_cursor_pos.y };

		const auto window_size = ImGui::GetWindowSize();
		auto bounds = ImGui::GetWindowPos();
		bounds.x += viewport_offset.x;
		bounds.y += viewport_offset.y;
		Vec2 min_bounds = { bounds.x,bounds.y };
		Vec2 max_bounds = { bounds.x + window_size.x,bounds.y + window_size.y };

		FApplication::Get().GetInputSystem().SetCurrentViewportBounds(min_bounds, max_bounds);

		
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2(static_cast<float>(FApplication::Get().GetWindowsWindow()->Properties->GetWidth()), static_cast<float>(FApplication::Get().GetWindowsWindow()->Properties->GetHeight()))/*, ImVec2( 0, 1 ), ImVec2( 0, 1 )*/);
		//ImGui::Image(reinterpret_cast<void*>(textureID), ImGui::GetContentRegionAvail()/*, ImVec2( 0, 1 ), ImVec2( 0, 1 )*/);
		ImGui::End();

	}

}



void FRenderingSystem::OutLine(const FCameraComponent& mainCamera, const std::shared_ptr<FRenderer>& renderer, uint32 currentSelectedEntity) const
{
	const glm::mat4 ViewProjection = mainCamera.ViewProjection;

	std::vector< glm::mat4> Translations;
	const glm::mat4 WorldProjection = glm::perspective(glm::radians(45.0f), FApplication::Get().GetWindowsWindow()->Properties->GetWidth() / FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.1f, 10000.0f);

	
	/*Selection outline. Depth test off so the highlight is always visible; the stencil funcs are
	 *configured per-pass in the draw below.*/
	glDisable(GL_DEPTH_TEST);
	if (EntityManager::HasComponent<FTransformComponent>(currentSelectedEntity) && EntityManager::HasComponent<FStaticMesh>(currentSelectedEntity) &&
		(EntityManager::HasComponent<DefaultLitMaterialComponent>(currentSelectedEntity) || EntityManager::HasComponent<DefaultUnLitMaterialComponent>(currentSelectedEntity)))

	{


		FTransform& transform = EntityManager::GetComponent<FTransformComponent>(currentSelectedEntity).Transform;
		/*Build the model matrix from the actual transform. No fixed 1.005 scale-up: the outline
		 *thickness is produced in screen space by the outline vertex shader, so it stays the same
		 *size on screen for every object regardless of the object's size or distance.*/
		glm::mat4 model_projection = glm::mat4(1.0f);
		model_projection = glm::translate(model_projection, FVectorHelper::AsGLMVec3(transform.GetLocation()));
		model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
		model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
		model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
		model_projection = glm::scale(model_projection, FVectorHelper::AsGLMVec3(transform.GetScale()));

		

		auto& static_mesh = EntityManager::GetComponent<FStaticMesh>(currentSelectedEntity);
			const glm::mat4 mvp = WorldProjection * ViewProjection * model_projection;
			const KREngine::vec3 viewportSize(FApplication::Get().GetWindowsWindow()->Properties->GetWidth(), FApplication::Get().GetWindowsWindow()->Properties->GetHeight(), 0.0f);
			const int indexCount = static_cast<int>(static_mesh.IndexBufferData->GetIndexBufferCount());

			Shader->BindShader();
			Shader->SetUniformMat4("u_MVP", mvp);
			Shader->SetUniform3f("u_ViewportSize", viewportSize);
			static_mesh.VertexArray->BindBuffer();

			/*Pass 1: stamp ONLY this object's silhouette into the stencil buffer with a unique value
			 *(2), writing no colour and no extrusion. Every object in the main pass shares stencil=1,
			 *so without this the outline gets clipped wherever the object meets the floor/another mesh.*/
			Shader->SetUniformF("u_OutlinePixels", 0.0f);
			glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
			glStencilFunc(GL_ALWAYS, 2, 0xFF);
			glStencilMask(0xFF);
			renderer->Draw(indexCount);

			/*Pass 2: draw the screen-space-expanded mesh in yellow everywhere the stencil is NOT this
			 *object (the silhouette border), giving a complete, uniform outline all the way around.*/
			Shader->SetUniformF("u_OutlinePixels", 4.0f);
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			glStencilFunc(GL_NOTEQUAL, 2, 0xFF);
			glStencilMask(0x00);
			renderer->Draw(indexCount);

			static_mesh.VertexArray->UnBindBuffer();
			Shader->UnBindShader();


			if (EntityManager::HasComponent<FGizmo>(Gizmo) && EntityManager::HasComponent<FTransformComponent>(Gizmo))
			{
				FGizmo& gizmo = EntityManager::GetComponent<FGizmo>(Gizmo);
				FTransformComponent& transform_gizmo = EntityManager::GetComponent<FTransformComponent>(Gizmo);
				gizmo.bNeedsToRender = true;
				transform_gizmo.Transform.SetLocation(transform.GetLocation());
				/*Gizmo orientation follows the object in Local space; stays world-aligned in Global space.*/
				if (FApplication::Get().IsGizmoLocalSpace())
					transform_gizmo.Transform.SetRotation(transform.GetRotation());
				else
					transform_gizmo.Transform.SetRotation(FVector(0.0f, 0.0f, 0.0f));

				/*Constant screen size: scale proportional to camera distance, set fresh each frame (not accumulated).*/
				const float gizmoDistance = glm::length(FVectorHelper::AsGLMVec3(transform.GetLocation()) - mainCamera.CameraPosition);
				const float gizmoScale = gizmoDistance * GizmoScreenSize;
				transform_gizmo.Transform.SetScale(FVector(gizmoScale, gizmoScale, gizmoScale));

			}
	}
	else
	{
		if (EntityManager::HasComponent<FGizmo>(Gizmo) && EntityManager::HasComponent<FTransformComponent>(Gizmo))
		{
			auto& gizmo = EntityManager::GetComponent<FGizmo>(Gizmo);
			gizmo.bNeedsToRender = false;
		}
		
	}
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glEnable(GL_DEPTH_TEST);

	




}
#endif
