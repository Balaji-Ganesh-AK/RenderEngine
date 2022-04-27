#pragma once
#include "Entity/Entity.h"


namespace KREngine
{
	class FVertexBuffer;
	class FVertexArray;
	class FShader;
	struct FCameraComponent;
	class FRenderer;

	struct FLine 
	{
		friend struct FLineSystem;
		public:
			FLine(){};
			FLine(const FVector startLocation, const FVector endLocation, const FColor color = FColor::Red()):StartLocation(startLocation), EndLocation(endLocation), Color(color)
			{
			}
	
		private:
			std::shared_ptr<FShader> Shader;
			FVertexBuffer* VertexBufferData = nullptr;
			FVertexArray* VertexArray = nullptr;
			FVector StartLocation;
			FVector EndLocation;
			FColor Color;
	};


	class FLineSystem: public FSystem
	{
	public:
	
		~FLineSystem() override;
		void Init() override;
		void Run(const FCameraComponent& mainCamera, const std::shared_ptr<FRenderer>& renderer);
		void End() override;
		void GUIInit() override;
		void GUIRun() override;
		void GUIEnd() override;

	private:
		std::vector<float>VertexBuffer;
		float vertexpos[6] = { 0,0,0, 0.0f,100.0f,0 };
		std::filesystem::path DefaultVertexShaderPath = "../Content/Shaders/Source/DefaultLineVertexShader.GLSL";
		std::filesystem::path DefaultFragmentShaderPath = "../Content/Shaders/Source/DefaultLineFragmentShader.GLSL";

	};

}
