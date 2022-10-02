#include "Collider.h"

#include "GameManager.h"
#include "Entity/Components/TransformComponent.h"
#include "RenderingSystem/Buffers.h"
#include "RenderingSystem/FRenderer.h"
#include "RenderingSystem/Shader.h"
#include "Runtime/Camera/FCameraComponent.h"


namespace KREngine
{

	FColliderRenderer::~FColliderRenderer()
	{
	}
#pragma optimize ("", off)
	void FColliderRenderer::Init()
	{

		VertexBufferLayout layout{
									BufferElement{"v_Pos", EShaderDataType::FVec3, true}

		};


		for (auto entityHandle : EntityHandles)
		{
			auto& sphere = EntityManager::GetComponent<FSphereCollider>(entityHandle);

			sphere.Shader.reset(FShader::CreateShader(DefaultVertexShaderPath, DefaultFragmentShaderPath));
			sphere.Shader->BindShader();
			sphere.Model = FApplication::GetAssetManager().GetModel("Sphere");
			sphere.VertexArray = FVertexArray::Create();

			/*Combine all the buffer to a single buffer object*/
			for (int i = 0; i < sphere.Model->VertexPositionBuffer.size(); i++)
			{

				sphere.VertexBuffer.push_back(sphere.Model->VertexPositionBuffer[i].x);
				sphere.VertexBuffer.push_back(sphere.Model->VertexPositionBuffer[i].y);
				sphere.VertexBuffer.push_back(sphere.Model->VertexPositionBuffer[i].z);
				/*		sphere.VertexBuffer.push_back(sphere.Model->TextureCordBuffer[i].x);
						sphere.VertexBuffer.push_back(sphere.Model->TextureCordBuffer[i].y);
						sphere.VertexBuffer.push_back(sphere.Model->NormalBuffer[i].x);
						sphere.VertexBuffer.push_back(sphere.Model->NormalBuffer[i].y);
						sphere.VertexBuffer.push_back(sphere.Model->NormalBuffer[i].z);
						*/


			}
			sphere.VertexBufferData = FVertexBuffer::CreateVertexBuffer(sphere.VertexBuffer.data(), sphere.VertexBuffer.size());
			sphere.IndexBufferData = FIndexBuffer::CreateIndexBuffer(sphere.Model->IndexPositions.data(), sphere.Model->IndexPositions.size());

			sphere.VertexArray->SetLayOut(layout);
			sphere.VertexArray->BindBufferLayout();
			sphere.VertexArray->UnBindBuffer();

			sphere.Shader->UnBindShader();
		}
	}

	void FColliderRenderer::RenderRun(const FCameraComponent& mainCamera, const std::shared_ptr<FRenderer>& renderer)
	{
		SCOPED_TIMER("Collider System");
		renderer->EnableWireFrameMode();
		const glm::mat4 ViewProjection = mainCamera.ViewProjection;
		const glm::mat4 WorldProjection = FApplication::Get().GetWorldProjection();
		for (const auto entityHandle : EntityHandles)
		{

			auto& sphere = EntityManager::GetComponent<FSphereCollider>(entityHandle);
			if (sphere.bShowCollider)
			{

				auto& shader = sphere.Shader;
				auto& transform = EntityManager::GetComponent<FTransformComponent>(entityHandle).Transform;
				glm::mat4 model_projection = glm::mat4(1.0f);
				model_projection = glm::translate(model_projection, FVectorHelper::AsGLMVec3(transform.GetLocation()));
				model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
				model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
				model_projection = glm::rotate(model_projection, glm::radians(transform.GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
				sphere.ActualRadius = FColliderRenderer::FindMaxSize(EntityManager::GetComponent<FTransformComponent>(entityHandle).Transform.GetScale()) * sphere.Radius;

				model_projection = glm::scale(model_projection, FVectorHelper::AsGLMVec3(FVector{ sphere.ActualRadius, sphere.ActualRadius, sphere.ActualRadius
			
			}));
				if (shader)
				{

					shader->BindShader();
					shader->SetUniformMat4("u_WorldProjection", WorldProjection * ViewProjection * model_projection);
					shader->SetUniformMat4("u_Model", /*ViewProjection*/ model_projection);
					shader->SetUniform4f("u_Color", FColor::Green());
					sphere.VertexArray->BindBuffer();
					renderer->Draw(static_cast<int>(sphere.VertexBuffer.size()));
					sphere.VertexArray->UnBindBuffer();
					shader->UnBindShader();
				}
			}

		}
		renderer->NormalRenderMode();
	}

	void FColliderRenderer::RunCollision()
	{
		for (const auto & entityHandle: EntityHandles)
		{
			const float sphere_a_r  = EntityManager::GetComponent<FSphereCollider>(entityHandle).ActualRadius;
			const FVector& location_a = EntityManager::GetComponent<FTransformComponent>(entityHandle).Transform.GetLocation();
			for (const auto& other : EntityHandles)
			{
				if(entityHandle != other)
				{
					
				const float sphere_b_r = EntityManager::GetComponent<FSphereCollider>(other).ActualRadius;
				const FVector& location_b = EntityManager::GetComponent<FTransformComponent>(other).Transform.GetLocation();
				bool hit = SphereSphere(sphere_a_r, sphere_b_r, location_a, location_b);
				if(hit)
				{
					Logger::Warning("Sphere hit!");
				}
				}
			}
		}
	}
#pragma optimize ("", on)
	void FColliderRenderer::End()
	{
		FSystem::End();
	}

	void FColliderRenderer::GUIInit()
	{
		FSystem::GUIInit();
	}

	void FColliderRenderer::GUIRun()
	{
		FSystem::GUIRun();
	}

	void FColliderRenderer::GUIEnd()
	{
		FSystem::GUIEnd();
	}

	void FColliderRenderer::MakeSphere(float ring, float sector, std::vector<float>& buffer, std::vector<uint32>& indexBuffer)
	{
		float R = 1.0f / (float)(ring - 1);
		float S = 1.0f / (float)(sector - 1);
		constexpr float PI = 3.1415926535897932384626433f;
		constexpr float PI_BY_2 = 1.57079632679489661923f;

		int v = 0;
		int n = 0;
		int i = 0;

		for (int r = 0; r < ring; r++)
		{
			for (int s = 0; s < sector; s++)
			{

				float x = (float)sin(-PI_BY_2 + PI * r * R);
				float y = (float)cos(2.0f * PI * s * S) * (float)sin(PI * r * R);
				float z = (float)sin(2.0f * PI * s * S) * (float)sin(PI * r * R);

				buffer.push_back(x);
				buffer.push_back(y);
				buffer.push_back(z);

			}
		}

		for (int r = 0; r < ring - 1; r++)
		{
			for (int s = 0; s < sector - 1; s++)
			{
				indexBuffer.push_back(r * sector + static_cast<float>(s));
				indexBuffer.push_back(r * sector + static_cast<float>(s + 1));
				indexBuffer.push_back(r + 1 * sector + static_cast<float>(s + 1));
				indexBuffer.push_back(r + 1 * sector + static_cast<float>(s));
			}
		}

	}

	bool FColliderRenderer::SphereSphere(const float& a, const float& b, const FVector& location_a,
		const FVector& location_b)
	{
		FVector distance = location_a - location_b;
		float distance_sqrd = FVector::Dot(distance, distance);

		const float radius_sum = a + b;
		float sqrd_radius = radius_sum * radius_sum;



		return distance_sqrd < sqrd_radius;
	}

	void FColliderSystem::RunCollision()
	{
	}

	FColliderSystem::~FColliderSystem()
	{
	}

	void FColliderSystem::Init()
	{
		FSystem::Init();
	}

	void FColliderSystem::Run()
	{
		FSystem::Run();
	}

	void FColliderSystem::End()
	{
		FSystem::End();
	}

	void FColliderSystem::GUIInit()
	{
		FSystem::GUIInit();
	}

	void FColliderSystem::GUIRun()
	{
		FSystem::GUIRun();
	}

	void FColliderSystem::GUIEnd()
	{
		FSystem::GUIEnd();
	}
}
