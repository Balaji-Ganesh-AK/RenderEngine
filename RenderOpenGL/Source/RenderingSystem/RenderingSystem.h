#pragma once


#include "Buffers.h"
#include "Shader.h"
#include "Textures.h"
#include "../utility/Pch.h"
#include "ImGUI/imgui.h"


namespace KREngine
{

	struct FRenderingObject
	{
	public:
		std::shared_ptr<KREngine::FVertexBuffer> VertexBufferData;
		std::shared_ptr<KREngine::FIndexBuffer> IndexBufferData;
		std::shared_ptr<KREngine::FVertexArray> VertexArray;
		std::shared_ptr<FTexture2D> Texture2D;
		std::shared_ptr<FShader> Shader;
	};


	class RenderingSystem : KREngine::System
	{
	public:
		void SetRenderingAPI( ERenderingAPI API )
		{
			RenderingAPI = API;
		}
		ERenderingAPI GetRenderingAPI() const
		{
			return RenderingAPI;
		}

		virtual void Init() override;
		virtual void Run() override;
		virtual void Stop() override;


		static RenderingSystem* GetInstance()
		{
			return Instance;
		}
		GLFWwindow* GetGFLWWindow()
		{
			return WindowWindow.GetCurrentWindow();
		}
	private:
		
		RenderingSystem();
		ERenderingAPI RenderingAPI = ERenderingAPI::OpenGL;
		WindowsProperties Properties;
		WindowsWindow  WindowWindow;

		static RenderingSystem* Instance;

		std::vector<FRenderingObject> RenderingObjectList;

		const std::string DefaultVertexShaderPath = "Content/Shaders/Default/DefaultVertexShader.GLSL";
		const std::string DefaultFragmentShaderPath = "Content/Shaders/Default/DefaultFragmentShader.GLSL";

		float pos [28] = {
						//Vertex Positions	//Color				//Tex Cord
		/** 0 */		-0.5f,-0.5f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 
		/** 1 */		0.5f,-0.5f,			1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		/** 2 */		0.5f,0.5f,			1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		/** 3 */		-0.5f,0.5f,			1.0f, 1.0f, 1.0f,	0.0f, 1.0f
						
		};
		float testpos [15] =
		{
		0.0f,-1.0f, 0.5f, 0.0f, 0.0f,
	   1.0f, 0.0f, 0.0f, 0.5f, 0.0f,
	   -1.0f,0.0f, 0.0f, 0.0f, 0.5f
		};

		unsigned int indices [6] = {
			0,1,2,
			2,3,0
			
			
		};
		FColor Color{ 0.0f,0.0f,0.0f,0.0f };


		std::string DefaultTexture = "Content/Textures/Checkerboard.png";


		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4( 1.0f,1.0f,1.0f,1.0f );
	};
}
