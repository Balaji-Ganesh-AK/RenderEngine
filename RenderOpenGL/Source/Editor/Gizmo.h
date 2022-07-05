#pragma once
#include "Runtime/Line/Line.h"


namespace KREngine
{


	struct FGizmo
	{
		friend class FGizmoSystem;
		void SetLocation(FVector location);
		
		bool bNeedsToRender = true;
	private:
	
		std::vector<FLine> Axes{ { FVector{0,0,0}, FVector{10,0,0} , FColor::Red() } ,
			{ FVector{0,0,0}, FVector{0,10,0} , FColor::Green() } ,
			{ FVector{0,0,0},FVector{0,0,10} , FColor::Blue()} };
		std::shared_ptr<FShader> Shader;
		FVertexBuffer* VertexBufferData = nullptr;
		FVertexArray* VertexArray = nullptr;
		
		//FColor Color{ FColor::Blue() };
		std::vector<float>VertexBuffer;
	};

	class FGizmoSystem : public FSystem
	{
	public:
		~FGizmoSystem() override;
		void Init() override;
		void Run(const FCameraComponent& mainCamera, const std::shared_ptr<FRenderer>& renderer);
		void End() override;
		void GUIInit() override;
		void GUIRun() override;
		void GUIEnd() override;

		std::filesystem::path DefaultVertexShaderPath = "../Content/Shaders/Source/LineVertexColorVertexShader.GLSL";
		std::filesystem::path DefaultFragmentShaderPath = "../Content/Shaders/Source/LineVertexColorFragmentShader.GLSL";

	private:
	
	};
}
