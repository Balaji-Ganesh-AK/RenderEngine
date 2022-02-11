#pragma once


#include "Buffers.h"
#include "Materials.h"
#include "Shader.h"
#include "Textures.h"
#include "Entity/Entity.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"
#include "Runtime/Camera/FCamera.h"
#include "Runtime/Containers/FTransform.h"


namespace KREngine
{
	class WindowsWindow;

	/*Batch rendering ku use agum*/
	
	struct FRenderingObject
	{
	public:
		std::shared_ptr<FVertexBuffer> VertexBufferData;
		std::shared_ptr<FIndexBuffer> IndexBufferData;
		std::shared_ptr<FVertexArray> VertexArray;
		std::shared_ptr<FShader> Shader;
		FMaterials Material;
		//FStaticMesh* Mesh = nullptr;
		FTransform Transform;
	};


	struct FRenderingComponent
	{
	public:
		std::shared_ptr<FShader> Shader;
		FMaterials Material;
	};

	class FRenderingSystem : public FSystem
	{

	public:
		FRenderingSystem() = default;
		~FRenderingSystem()= default;
		void Init();
		void Run();
		void Stop();

		void GUIInit();
		void GUIStop();
		void GUIRun();


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


		std::shared_ptr<FFrameBuffer> Framebuffer;

		std::filesystem::path DefaultVertexShaderPath = "../Content/Shaders/Default/DefaultVertexShader.GLSL";
		std::filesystem::path DefaultFragmentShaderPath = "../Content/Shaders/Default/DefaultFragmentShader.GLSL";
		FColor Color{ 1.0f,0.0f,0.0f,1.0f };
	//	FCamera CameraTransform;
		std::string DefaultTexture = "../Content/Textures/awesomeface.png";
		std::string SecondTexture = "../Content/Textures/awesomeface.png";
		glm::mat4 WorldProjection;

		FCamera CameraTransform;

		std::shared_ptr<FShader> Shader;
		FMaterials Material;
	};
}
