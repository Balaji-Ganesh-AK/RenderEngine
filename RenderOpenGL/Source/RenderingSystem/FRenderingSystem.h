#pragma once
#include <memory>

#include "Entity/Entity.h"
#include "Runtime/Line/Line.h"


namespace KREngine
{
	class FGizmoSystem;
	class FLineSystem;
	class FFoliageSystem;
	class FShader;
	class FRenderer;
	class FTransformSystem;
	class FDefaultLitMaterialSystem;
	class FDefaultUnLitMaterialSystem;
	class FStaticMeshSystem;
	struct FCameraComponent;

	class FFrameBuffer;

	
	class FRenderingSystem /*: public FSystem*/
	{

	public:
		FRenderingSystem();
		~FRenderingSystem()= default;
		void Init();
		void Run(const FCameraComponent& mainCamera, uint32 currentSelectedEntity);
		void Stop();

		void GUIInit();
		void GUIStop();
		void GUIRun();
		std::shared_ptr<FRenderer> GetRenderer() const
		{
			return Renderer;
		}
		void OutLine(const FCameraComponent& mainCamera, const std::shared_ptr<FRenderer>& renderer, uint32 currentSelectedEntity) const;

	private:
		float test = 0.0;

		float GizmoScreenSize = 0.01f;

	private:

	
		std::shared_ptr<FStaticMeshSystem> StaticMeshSystem;
		std::shared_ptr<FDefaultUnLitMaterialSystem> DefaultShaderSystem;
		std::shared_ptr<FDefaultLitMaterialSystem> DefaultLitShaderSystem;
		std::shared_ptr<FTransformSystem> TransformSystem;
		
		std::shared_ptr<FFrameBuffer> Framebuffer;
		std::shared_ptr<FFoliageSystem> FoliageSystem;
		std::shared_ptr<FLineSystem> LineSystem;
		std::shared_ptr<FGizmoSystem> GizmoSystem;

		std::shared_ptr<FRenderer> Renderer;

		std::filesystem::path DefaultVertexShaderPath = "../Content/Shaders/Source/DefaultVertexShader.GLSL";
		std::filesystem::path DefaultFragmentShaderPath = "../Content/Shaders/Source/DefaultFragmentShaderOutliner.GLSL";
		std::shared_ptr<FShader> Shader;

		//FRenderer* Renderer;
		FEntityHandle Gizmo;
		FColor Color{ 1.0f,0.0f,0.0f,1.0f };
	};
}
