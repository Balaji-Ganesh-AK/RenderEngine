#pragma once


#include "Buffers.h"
#include "Shader.h"
#include "../utility/Pch.h"



namespace KREngine
{

	struct FRenderingObject
	{
	public:
		std::shared_ptr<KREngine::FVertexBuffer> VertexBufferData;
		std::shared_ptr<KREngine::FIndexBuffer> IndexBufferData;
		std::shared_ptr<KREngine::FVertexArray> VertexArray;
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
	private:
		RenderingSystem();
		ERenderingAPI RenderingAPI = ERenderingAPI::OpenGL;
		WindowsProperties Properties;
		WindowsWindow  WindowWindow;

		static RenderingSystem* Instance;

		std::vector<FRenderingObject> RenderingObjectList;

		const std::string DefaultVertexShaderPath = "Content/Shaders/Default/DefaultVertexShader.GLSL";
		const std::string DefaultFragmentShaderPath = "Content/Shaders/Default/DefaultFragmentShader.GLSL";

		float pos [6] = {
			//Vertex Positions //Color
			0.0f,0.5f,
			-0.5f,0.0f,
			0.0f,0.5f

		};
	/*	0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 1.0f*/
		float testpos [6] =
		{
		-0.5f,0.5f,
	   0.0f, 0.75f,
	   0.75f,0.0f };

		unsigned int indices [3] = {
			0,1,2
		};
		FColor Color{ 0.2f,0.3f,0.8f,1.0f };
	};
}
