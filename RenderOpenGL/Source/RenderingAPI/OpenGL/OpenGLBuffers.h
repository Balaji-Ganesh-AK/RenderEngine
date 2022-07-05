#pragma once
#include "RenderingSystem/Buffers.h"
#include "RenderOpenGL/Utility/Source/Defines.h"


namespace KREngine
{
	class OpenGLVertexBuffer : public FVertexBuffer
	{

	public:
		OpenGLVertexBuffer( float* VertexPos, uint32 count );
		void BindBuffer() override;
		void UnBindBuffer() override;

		virtual void SetData() override;
		~OpenGLVertexBuffer() override;

	private:
		int BufferSize{1};
	};

	class OpenGLIndexBuffer : public FIndexBuffer
	{

	public:
		OpenGLIndexBuffer( unsigned int* VertexPos, uint32 count );
		void BindBuffer() override;
		void UnBindBuffer() override;

		virtual void SetData() override;
		~OpenGLIndexBuffer() override;
		uint32 GetIndexBufferCount() override
		{
			return BufferCount;
		}

	private:
		int BufferSize{ 1 };
		uint32 BufferCount{ 0 };
	};

	class OpenGLVertexArray: public FVertexArray
	{
		
	public:
		OpenGLVertexArray();
		virtual void BindBuffer() override;
		virtual void UnBindBuffer() override;


		void BindBufferLayout() override;
		~OpenGLVertexArray() override;

		
	};

	struct OpenGLFrameBufferSettings : public FFrameBufferSettings
	{
		
	};

	class OpenGLFrameBuffer : public FFrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FFrameBufferSettings settings);
		~OpenGLFrameBuffer();
		virtual void BindBuffer() override;
		virtual void UnBindBuffer() override;
		virtual uint32 GetTextureRendererID() override;
		virtual void OnWindowResize(float width, float height) override;
		int ReadPixel(uint32 attachmentID, int x, int y) override;
	private:
		void InitializeFrameBuffer( );

	
	};
	
}
