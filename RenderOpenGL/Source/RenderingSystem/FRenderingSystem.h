#pragma once




#include "Buffers.h"
#include "Shader.h"
#include "Textures.h"
#include "../utility/Pch.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "Runtime/Containers/FTransform.h"
#include "Systems/Systems.h"


namespace KREngine
{
	class WindowsWindow;

	struct FRenderingObject
	{
	public:
		std::shared_ptr<FVertexBuffer> VertexBufferData;
		std::shared_ptr<FIndexBuffer> IndexBufferData;
		std::shared_ptr<FVertexArray> VertexArray;
		std::shared_ptr<FTexture2D> Texture2D;
		std::shared_ptr<FShader> Shader;
	};


	class FRenderingSystem : public KREngine::FGameSystem
	{
	public:
		FRenderingSystem(WindowsWindow* window);
		~FRenderingSystem();
		void SetRenderingAPI( ERenderingAPI API )
		{
			RenderingAPI = API;
		}

		ERenderingAPI GetRenderingAPI() const;

		virtual void Init() override;
		virtual void Run() override;
		virtual void Stop() override;

#if GUI
		void GUIInit() override;
		void GUIRun() override;
		void GUIStop() override;
#endif

		FORCEINLINE const WindowsWindow* GetWindowsWindow() const
		{
			return WindowWindow;
		}
		GLFWwindow* GetGFLWWindow() const;


	private:

		

	private:
		ERenderingAPI RenderingAPI = ERenderingAPI::OpenGL;
		WindowsWindow* WindowWindow = nullptr;
		glm::mat4 WorldProjection;

		std::vector<FRenderingObject> RenderingObjectList;
		std::shared_ptr<FFrameBuffer> Framebuffer;
		//const std::string DefaultVertexShaderPath = "Content/Shaders/Default/DefaultVertexShader.GLSL";
		std::filesystem::path DefaultVertexShaderPath = "../Content/Shaders/Default/DefaultVertexShader.GLSL";
		std::filesystem::path DefaultFragmentShaderPath = "../Content/Shaders/Default/DefaultFragmentShader.GLSL";
		//const std::string DefaultFragmentShaderPath = "Content/Shaders/Default/DefaultFragmentShader.GLSL";

		float pos [8 * 24] = {
			                //Vertex Positions	    //Color				//Tex Cord   
			/** 0 */		-0.5f,-0.5f,-0.5f,		0.0f, 0.0f, 0.0f,	0.5f, 0.5f, 
			/** 1 */		0.5f,-0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.5f,
			/** 2 */		0.5f,0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			/** 3 */		-0.5f,0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	0.5f, 1.0f,

			/** 4 */		-0.5f,-0.5f,0.5f,		0.0f, 0.0f, 0.0f,	0.5f, 0.5f,
			/** 5 */		0.5f,-0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.5f,
			/** 6 */		-0.5f,0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	0.5f, 1.0f,
			/** 7 */		0.5f,0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,

			/** 8 */		-0.5f,0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
			/** 9 */		0.5f,0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
			/** 10 */		0.5f,0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			/** 11 */		-0.5f,0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,

			/** 12 */		-0.5f,-0.5f,-0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
			/** 13 */		0.5f,-0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
			/** 14 */		0.5f,-0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			/** 15 */		-0.5f,-0.5f,0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,

			/** 16 */		0.5f,-0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
			/** 17 */		0.5f,-0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
			/** 18 */		0.5f,0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
			/** 19 */		0.5f,0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			
			/** 20 */		-0.5f,-0.5f,-0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
			/** 21 */		-0.5f,-0.5f,0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
			/** 22 */		-0.5f,0.5f,	0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
			/** 23 */		-0.5f,0.5f,	-0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f

		};


		float testpos [1000] =
		{
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		uint32 indices [3 * 4 *3] = {
			0,1,2,
			0,2,3,

			4,5,7,
			4,7,6,

			8,9,10,
			10,11,8,

			12,13,14,
			14,15,12,

			16,17,18,
			18,19,16,

			20,21,22,
			22,23,20
		};
		FColor Color{ 1.0f,1.0f,1.0f,1.0f };
		FColor GlobalColor{ 1.0f,1.0f,1.0f,1.0f };
		KREngine::FTransform Transform;
		KREngine::FTransform CameraTransform;
		std::string DefaultTexture = "Content/Textures/Checkerboard.png";
		std::string SecondTexture = "Content/Textures/awesomeface.png";
		//std::string DefaultTexture = "Content/Textures/Checkerboard.png";
		float test{0.0f};
	};
}
