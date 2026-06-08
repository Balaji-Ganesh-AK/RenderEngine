#include "Gizmo.h"

#include <cmath>

#include "GameManager.h"
#include "Entity/Components/TransformComponent.h"
#include "RenderingSystem/Buffers.h"
#include "RenderingSystem/FRenderer.h"
#include "RenderingSystem/Shader.h"
#include "RenderingSystem/WindowsWindow.h"
#include "Systems/Input/Input.h"
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

			gizmo.VertexBuffer.clear();

			/*Helpers that append vertices (7 floats each: xyz + rgba) and whole line segments.*/
			auto pushVertex = [&](float x, float y, float z, const FColor& c)
			{
				gizmo.VertexBuffer.push_back(x);
				gizmo.VertexBuffer.push_back(y);
				gizmo.VertexBuffer.push_back(z);
				gizmo.VertexBuffer.push_back(c.r);
				gizmo.VertexBuffer.push_back(c.g);
				gizmo.VertexBuffer.push_back(c.b);
				gizmo.VertexBuffer.push_back(c.a);
			};
			auto pushLine = [&](float ax, float ay, float az, float bx, float by, float bz, const FColor& c)
			{
				pushVertex(ax, ay, az, c);
				pushVertex(bx, by, bz, c);
			};
			auto vertexCount = [&]() { return static_cast<int>(gizmo.VertexBuffer.size() / 7); };

			const FColor red = FColor::Red();
			const FColor green = FColor::Green();
			const FColor blue = FColor::Blue();
			const float L = 10.0f;

			/*--- Translate: three axis lines ---*/
			gizmo.ModeVertexOffset[static_cast<int>(EGizmoMode::Translate)] = vertexCount();
			pushLine(0, 0, 0, L, 0, 0, red);
			pushLine(0, 0, 0, 0, L, 0, green);
			pushLine(0, 0, 0, 0, 0, L, blue);
			gizmo.ModeVertexCount[static_cast<int>(EGizmoMode::Translate)] =
				vertexCount() - gizmo.ModeVertexOffset[static_cast<int>(EGizmoMode::Translate)];

			/*--- Rotate: three rings (one per plane) ---*/
			gizmo.ModeVertexOffset[static_cast<int>(EGizmoMode::Rotate)] = vertexCount();
			{
				const int segments = 32;
				const float radius = L;
				const float twoPi = 6.28318530718f;
				for (int i = 0; i < segments; ++i)
				{
					const float t0 = (static_cast<float>(i) / segments) * twoPi;
					const float t1 = (static_cast<float>(i + 1) / segments) * twoPi;
					/*ring around X (YZ plane)*/
					pushLine(0, radius * cosf(t0), radius * sinf(t0), 0, radius * cosf(t1), radius * sinf(t1), red);
					/*ring around Y (XZ plane)*/
					pushLine(radius * cosf(t0), 0, radius * sinf(t0), radius * cosf(t1), 0, radius * sinf(t1), green);
					/*ring around Z (XY plane)*/
					pushLine(radius * cosf(t0), radius * sinf(t0), 0, radius * cosf(t1), radius * sinf(t1), 0, blue);
				}
			}
			gizmo.ModeVertexCount[static_cast<int>(EGizmoMode::Rotate)] =
				vertexCount() - gizmo.ModeVertexOffset[static_cast<int>(EGizmoMode::Rotate)];

			/*--- Scale: three axis lines with a small box at each tip ---*/
			gizmo.ModeVertexOffset[static_cast<int>(EGizmoMode::Scale)] = vertexCount();
			{
				auto pushBox = [&](float cx, float cy, float cz, float s, const FColor& c)
				{
					const float x0 = cx - s, x1 = cx + s, y0 = cy - s, y1 = cy + s, z0 = cz - s, z1 = cz + s;
					pushLine(x0, y0, z0, x1, y0, z0, c); pushLine(x1, y0, z0, x1, y1, z0, c);
					pushLine(x1, y1, z0, x0, y1, z0, c); pushLine(x0, y1, z0, x0, y0, z0, c);
					pushLine(x0, y0, z1, x1, y0, z1, c); pushLine(x1, y0, z1, x1, y1, z1, c);
					pushLine(x1, y1, z1, x0, y1, z1, c); pushLine(x0, y1, z1, x0, y0, z1, c);
					pushLine(x0, y0, z0, x0, y0, z1, c); pushLine(x1, y0, z0, x1, y0, z1, c);
					pushLine(x1, y1, z0, x1, y1, z1, c); pushLine(x0, y1, z0, x0, y1, z1, c);
				};
				pushLine(0, 0, 0, L, 0, 0, red);   pushBox(L, 0, 0, 0.6f, red);
				pushLine(0, 0, 0, 0, L, 0, green); pushBox(0, L, 0, 0.6f, green);
				pushLine(0, 0, 0, 0, 0, L, blue);  pushBox(0, 0, L, 0.6f, blue);
			}
			gizmo.ModeVertexCount[static_cast<int>(EGizmoMode::Scale)] =
				vertexCount() - gizmo.ModeVertexOffset[static_cast<int>(EGizmoMode::Scale)];

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
		const glm::mat4 WorldProjection = FApplication::GetWorldProjection();

		/*Mode switch (Unreal W/E/R) only when not flying the camera (right mouse not held),
		 *so it doesn't fight the WASD fly controls.*/
		FInput& input = FApplication::Get().GetInputSystem();
		const bool rightMouseHeld = input.IsMouseKeyPressed(Input::MouseCode::Button2);

		for (const auto entityHandle : EntityHandles)
		{
			auto& gizmo = EntityManager::GetComponent<FGizmo>(entityHandle);

			if (!rightMouseHeld)
			{
				if (input.IsKeyPressed(Input::KeyCodes::W)) gizmo.Mode = EGizmoMode::Translate;
				else if (input.IsKeyPressed(Input::KeyCodes::E)) gizmo.Mode = EGizmoMode::Rotate;
				else if (input.IsKeyPressed(Input::KeyCodes::R)) gizmo.Mode = EGizmoMode::Scale;
			}

			const auto& model_projection = EntityManager::GetComponent<FTransformComponent>(entityHandle).ModelProjection;
			if (gizmo.Shader && gizmo.bNeedsToRender)
			{
				gizmo.Shader->BindShader();
				gizmo.Shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);

				gizmo.VertexArray->BindBuffer();
				const int m = static_cast<int>(gizmo.Mode);
				glDrawArrays(GL_LINES, gizmo.ModeVertexOffset[m], gizmo.ModeVertexCount[m]);
				gizmo.VertexArray->UnBindBuffer();
				gizmo.Shader->UnBindShader();
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
