#pragma once
#include <memory>

#include "Entity/Entity.h"


namespace KREngine
{
	class FShader;
	class FRenderer;
	class FTransformSystem;
	class FDefaultLitMaterialSystem;
	class FDefaultUnLitMaterialSystem;
	class FStaticMeshSystem;
	struct FCamera;

	class FFrameBuffer;


	class FRenderingSystem /*: public FSystem*/
	{

	public:
		FRenderingSystem();
		~FRenderingSystem()= default;
		void Init();
		void Run(const FCamera& mainCamera, uint32 currentSelectedEntity);
		void Stop();

		void GUIInit();
		void GUIStop();
		void GUIRun();
		std::shared_ptr<FRenderer> GetRenderer() const
		{
			return Renderer;
		}
		void OutLine(const FCamera& mainCamera, const std::shared_ptr<FRenderer>& renderer, uint32 currentSelectedEntity) const;
	

	private:
		float test = 0.0;

//	public:
//		FRenderingSystem(WindowsWindow* window);
//		~FRenderingSystem();
//		void SetRenderingAPI( ERenderingAPI API )
//		{
//			RenderingAPI = API;
//		}
//
//		ERenderingAPI GetRenderingAPI() const;
//
//		virtual void Init() override;
//		virtual void Run() override;
//		virtual void Stop() override;
//
//#if GUI
//		void GUIInit() override;
//		void GUIRun() override;
//		void GUIStop() override;
//#endif
//
//		FORCEINLINE const WindowsWindow* GetWindowsWindow() const
//		{
//			return WindowWindow;
//		}
//		GLFWwindow* GetGFLWWindow() const;
//
//
//	private:
//
//		
//
//	private:
//		ERenderingAPI RenderingAPI = ERenderingAPI::OpenGL;
//		WindowsWindow* WindowWindow = nullptr;
//		glm::mat4 WorldProjection;
//
//		std::vector<FRenderingObject> RenderingObjectList;
//	
//		
//		
//		
//		//std::filesystem::path DefaultVertexShaderPath = "../Content/Shaders/Default/DefaultLitVertexShader.GLSL";
//		//std::filesystem::path DefaultFragmentShaderPath = "../Content/Shaders/Default/DefaultLitFragmentShader.GLSL";
//		
//		
//
//		
//		
//		
//		
//		
//		
//		//std::string DefaultTexture = "Content/Textures/Checkerboard.png";
//
//		FStaticMesh CubeMesh;
//		FMaterials Material;
//		bool bAmbientColor = false;
//		float TestTime = 0;
//		FLight GlobalLight;

	private:

	
		std::shared_ptr<FStaticMeshSystem> StaticMeshSystem;
		std::shared_ptr<FDefaultUnLitMaterialSystem> DefaultShaderSystem;
		std::shared_ptr<FDefaultLitMaterialSystem> DefaultLitShaderSystem;
		std::shared_ptr<FTransformSystem> TransformSystem;
		
		std::shared_ptr<FFrameBuffer> Framebuffer;

		std::shared_ptr<FRenderer> Renderer;

		std::filesystem::path DefaultVertexShaderPath = "../Content/Shaders/Source/DefaultVertexShader.GLSL";
		std::filesystem::path DefaultFragmentShaderPath = "../Content/Shaders/Source/DefaultFragmentShaderOutliner.GLSL";
		std::shared_ptr<FShader> Shader;
		//FRenderer* Renderer;
		FColor Color{ 1.0f,0.0f,0.0f,1.0f };
	};
}
