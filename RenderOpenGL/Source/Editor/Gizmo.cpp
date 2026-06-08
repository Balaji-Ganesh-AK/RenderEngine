#include "Gizmo.h"

#include <cmath>
#include <glm/glm.hpp>

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
			{
				/*Arrowheads at the axis tips (Unreal-style move handles).*/
				const float h = 2.0f, w = 0.7f;
				pushLine(L - h,  w,  w, L, 0, 0, red);   pushLine(L - h, -w,  w, L, 0, 0, red);
				pushLine(L - h,  w, -w, L, 0, 0, red);   pushLine(L - h, -w, -w, L, 0, 0, red);
				pushLine( w, L - h,  w, 0, L, 0, green); pushLine(-w, L - h,  w, 0, L, 0, green);
				pushLine( w, L - h, -w, 0, L, 0, green); pushLine(-w, L - h, -w, 0, L, 0, green);
				pushLine( w,  w, L - h, 0, 0, L, blue);  pushLine(-w,  w, L - h, 0, 0, L, blue);
				pushLine( w, -w, L - h, 0, 0, L, blue);  pushLine(-w, -w, L - h, 0, 0, L, blue);
			}
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
				glLineWidth(2.0f);
				const int m = static_cast<int>(gizmo.Mode);
				glDrawArrays(GL_LINES, gizmo.ModeVertexOffset[m], gizmo.ModeVertexCount[m]);
				glLineWidth(1.0f);
				gizmo.VertexArray->UnBindBuffer();
				gizmo.Shader->UnBindShader();
			}
		}
	}

	bool FGizmoSystem::UpdateInteraction(const FCameraComponent& mainCamera, FEntityHandle selectedEntity)
	{
		/*Nothing selected (or no transform) -> no gizmo interaction.*/
		if (EntityHandles.empty() || !EntityManager::HasComponent<FTransformComponent>(selectedEntity))
		{
			for (const auto e : EntityHandles)
				EntityManager::GetComponent<FGizmo>(e).ActiveAxis = -1;
			return false;
		}

		FGizmo& gizmo = EntityManager::GetComponent<FGizmo>(*EntityHandles.begin());
		FTransform& targetTransform = EntityManager::GetComponent<FTransformComponent>(selectedEntity).Transform;
		FInput& input = FApplication::Get().GetInputSystem();

		const glm::mat4 viewProj = FApplication::GetWorldProjection() * mainCamera.ViewProjection;
		const float fbW = FApplication::Get().GetWindowsWindow()->Properties->GetWidth();
		const float fbH = FApplication::Get().GetWindowsWindow()->Properties->GetHeight();

		const FVector loc = targetTransform.GetLocation();
		const glm::vec3 origin(loc.x, loc.y, loc.z);
		/*Axis space: world axes (Global) or the object's rotated axes (Local), matching the rendered gizmo.*/
		glm::mat4 spaceRot(1.0f);
		if (FApplication::Get().IsGizmoLocalSpace())
		{
			const FVector rotEuler = targetTransform.GetRotation();
			spaceRot = glm::rotate(spaceRot, glm::radians(rotEuler.x), glm::vec3(1, 0, 0));
			spaceRot = glm::rotate(spaceRot, glm::radians(rotEuler.y), glm::vec3(0, 1, 0));
			spaceRot = glm::rotate(spaceRot, glm::radians(rotEuler.z), glm::vec3(0, 0, 1));
		}
		const glm::vec3 axisDir[3] = {
			glm::normalize(glm::vec3(spaceRot * glm::vec4(1, 0, 0, 0))),
			glm::normalize(glm::vec3(spaceRot * glm::vec4(0, 1, 0, 0))),
			glm::normalize(glm::vec3(spaceRot * glm::vec4(0, 0, 1, 0)))
		};
		/*World length of the handles, matched to the rendered gizmo (constant screen size).*/
		const float axisLen = glm::length(mainCamera.CameraPosition - origin) * 0.1f;

		/*Project a world point to framebuffer pixel coords (same space as GetMousePosition()).*/
		auto worldToScreen = [&](const glm::vec3& p, glm::vec2& out) -> bool
		{
			const glm::vec4 clip = viewProj * glm::vec4(p, 1.0f);
			if (clip.w <= 0.0001f) return false;
			const glm::vec3 ndc = glm::vec3(clip) / clip.w;
			out.x = (ndc.x * 0.5f + 0.5f) * fbW;
			out.y = (ndc.y * 0.5f + 0.5f) * fbH;
			return true;
		};

		const Vec2 mouseRaw = input.GetMousePosition();
		const glm::vec2 mouse(mouseRaw.x, mouseRaw.y);
		const bool lmbDown = input.IsMouseKeyPressedInViewPort(Input::MouseCode::ButtonLeft);

		glm::vec2 screenOrigin;
		const bool originVisible = worldToScreen(origin, screenOrigin);

		/*--- Already dragging a handle: apply the manipulation ---*/
		if (gizmo.ActiveAxis >= 0)
		{
			if (!lmbDown)
			{
				gizmo.ActiveAxis = -1;
				gizmo.bWasMouseDown = lmbDown;
				return false;
			}

			const int a = gizmo.ActiveAxis;
			const glm::vec2 lastMouse(gizmo.LastDragX, gizmo.LastDragY);

			glm::vec2 sO, sTip;
			if (worldToScreen(origin, sO) && worldToScreen(origin + axisDir[a] * axisLen, sTip))
			{
				if (gizmo.Mode == EGizmoMode::Rotate)
				{
					/*Rotate by how far the cursor swept around the gizmo centre.*/
					const float angNow = atan2f(mouse.y - sO.y, mouse.x - sO.x);
					const float angLast = atan2f(lastMouse.y - sO.y, lastMouse.x - sO.x);
					float deltaRad = angNow - angLast;
					if (deltaRad > 3.14159265f) deltaRad -= 6.28318531f;       // unwrap across the atan2 seam
					else if (deltaRad < -3.14159265f) deltaRad += 6.28318531f;
					const float deltaDeg = deltaRad * 57.2957795f;
					FVector rot = targetTransform.GetRotation();
					if (a == 0) rot.x += deltaDeg; else if (a == 1) rot.y += deltaDeg; else rot.z += deltaDeg;
					targetTransform.SetRotation(rot);
				}
				else
				{
					const glm::vec2 sDir = sTip - sO;
					const float sLen = glm::length(sDir);
					if (sLen > 0.001f)
					{
						const glm::vec2 sDirN = sDir / sLen;
						const float pixelsAlong = glm::dot(mouse - lastMouse, sDirN);
						const float worldDelta = (pixelsAlong / sLen) * axisLen;

						if (gizmo.Mode == EGizmoMode::Translate)
						{
							const glm::vec3 p = origin + axisDir[a] * worldDelta;
							targetTransform.SetLocation(FVector(p.x, p.y, p.z));
						}
						else /* Scale */
						{
							FVector sc = targetTransform.GetScale();
							if (a == 0) sc.x += worldDelta; else if (a == 1) sc.y += worldDelta; else sc.z += worldDelta;
							targetTransform.SetScale(sc);
						}
					}
				}
			}

			gizmo.LastDragX = mouseRaw.x;
			gizmo.LastDragY = mouseRaw.y;
			gizmo.bWasMouseDown = lmbDown;
			return true;
		}

		/*--- Not dragging: on a fresh click, grab the nearest axis handle (if any) ---*/
		if (lmbDown && !gizmo.bWasMouseDown && originVisible)
		{
			int best = -1;
			float bestDist = 14.0f; // pixel threshold to grab a handle

			if (gizmo.Mode == EGizmoMode::Rotate)
			{
				/*Rotate handles are RINGS, not axis lines: find the ring (around X/Y/Z) whose
				 *projected outline is closest to the cursor.*/
				const int samples = 64;
				const float twoPi = 6.28318531f;
				for (int a = 0; a < 3; ++a)
				{
					for (int i = 0; i < samples; ++i)
					{
						const float ang = (static_cast<float>(i) / samples) * twoPi;
						const float c = cosf(ang) * axisLen, s = sinf(ang) * axisLen;
						glm::vec3 localOffset;
						if (a == 0) localOffset = glm::vec3(0.0f, c, s);     // ring around X (YZ plane)
						else if (a == 1) localOffset = glm::vec3(c, 0.0f, s); // ring around Y (XZ plane)
						else localOffset = glm::vec3(c, s, 0.0f);            // ring around Z (XY plane)
						const glm::vec3 ringPoint = origin + glm::vec3(spaceRot * glm::vec4(localOffset, 0.0f));

						glm::vec2 sp;
						if (!worldToScreen(ringPoint, sp)) continue;
						const float d = glm::length(mouse - sp);
						if (d < bestDist) { bestDist = d; best = a; }
					}
				}
			}
			else
			{
				/*Translate/Scale handles run along the axes: distance to the origin->tip segment.*/
				for (int a = 0; a < 3; ++a)
				{
					glm::vec2 sTip;
					if (!worldToScreen(origin + axisDir[a] * axisLen, sTip)) continue;
					const glm::vec2 ab = sTip - screenOrigin;
					const float ab2 = glm::dot(ab, ab);
					const float t = ab2 > 0.0001f ? glm::clamp(glm::dot(mouse - screenOrigin, ab) / ab2, 0.0f, 1.0f) : 0.0f;
					const glm::vec2 closest = screenOrigin + ab * t;
					const float d = glm::length(mouse - closest);
					if (d < bestDist) { bestDist = d; best = a; }
				}
			}
			if (best >= 0)
			{
				gizmo.ActiveAxis = best;
				gizmo.LastDragX = mouseRaw.x;
				gizmo.LastDragY = mouseRaw.y;
				gizmo.bWasMouseDown = lmbDown;
				return true; // grabbed a handle -> consume the click (don't change selection)
			}
		}

		gizmo.bWasMouseDown = lmbDown;
		return false;
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
