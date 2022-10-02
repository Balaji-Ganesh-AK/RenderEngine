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
		friend struct FRenderingSystem;

	public:
		FLine() {};
		FLine(const FVector startLocation, const FVector endLocation, const FColor color = FColor::Red()) :StartLocation(startLocation), EndLocation(endLocation), Color(color)
		{
		}
		FVector GetStartLocation() const
		{
			return StartLocation;
		};
		FVector GetEndLocation() const
		{
			return EndLocation;
		};
		FColor GetColor() const
		{
			return Color;
		}

		void SetStartLocation(FVector startLocation)
		{
			StartLocation = startLocation;
		}

		void SetEndLocation(FVector endLocation)
		{
			EndLocation = endLocation;
		}
		private:
			std::shared_ptr<FShader> Shader;
			FVertexBuffer* VertexBufferData = nullptr;
			std::vector<float>VertexBuffer;
			FVertexArray* VertexArray = nullptr;
			FVector StartLocation;
			FVector EndLocation;
			FColor Color {FColor::Red()};
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
	
		float vertexpos[6] = { 0,0,0, 0.0f,100.0f,0 };
		std::filesystem::path DefaultVertexShaderPath = "../Content/Shaders/Source/DefaultLineVertexShader.GLSL";
		std::filesystem::path DefaultFragmentShaderPath = "../Content/Shaders/Source/DefaultLineFragmentShader.GLSL";

	};

}
