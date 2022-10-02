#pragma once
#include "Entity/Entity.h"
#include "Systems/AssetSystem/AssetSystem.h"

namespace KREngine
{
	struct FCameraComponent;
	class FRenderer;
	class FIndexBuffer;
	class FVertexBuffer;
	class FShader;
	class FVertexArray;

	struct FSphereCollider
	{

		friend class FColliderRenderer;
		
		float Radius = 1.0f;
		bool bShowCollider{ false };

	private:
		friend class FColliderRenderer;
		std::shared_ptr<FShader> Shader;
		std::shared_ptr<FModel> Model;
		FVertexBuffer* VertexBufferData = nullptr;
		FIndexBuffer* IndexBufferData = nullptr;
		FVertexArray* VertexArray = nullptr;

		std::vector<float>VertexBuffer;
		float ActualRadius = 1.0f;
	};

	
	class FColliderRenderer: public FSystem
	{
	public:
		~FColliderRenderer() override;
		void Init() override;
		void RenderRun(const FCameraComponent& mainCamera, const std::shared_ptr<FRenderer>& renderer);
		void RunCollision();
		void End() override;
		void GUIInit() override;
		void GUIRun() override;
		void GUIEnd() override;
	private:
		static float FindMaxSize(const FVector& vector)
		{
			float return_data = 1.0f;
			if(vector.x >= vector.y && vector.x >= vector.y)
			{
				return_data= vector.x;
			}
			else if (vector.y >= vector.x && vector.y >= vector.z)
			{
				return_data =  vector.y;
			}
			else if (vector.z >= vector.x && vector.z >= vector.y)
			{
				return_data =  vector.z;
			}
			return return_data;
		}

		void MakeSphere(float ring, float sector, std::vector<float>& buffer, std::vector<uint32>& indexBuffer);
		bool SphereSphere(const float& a, const float& b, const FVector& location_a, const FVector& location_b);
		std::filesystem::path DefaultVertexShaderPath = "../Content/Shaders/Source/DefaultUnlitColorVS.GLSL";
		std::filesystem::path DefaultFragmentShaderPath = "../Content/Shaders/Source/DefaultUnlitColorFS.GLSL";
	};

	class FColliderSystem : public FSystem
	{
		void RunCollision();
	public:
		~FColliderSystem() override;
		void Init() override;
		void Run() override;
		void End() override;
		void GUIInit() override;
		void GUIRun() override;
		void GUIEnd() override;
	};
}
