#pragma once
#include "../../RenderingSystem/Buffers.h"

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
		uint32 BufferCount{1};
	};

	class OpenGLIndexBuffer : public FIndexBuffer
	{

	public:
		OpenGLIndexBuffer( unsigned int* VertexPos, uint32 count );
		void BindBuffer() override;
		void UnBindBuffer() override;

		virtual void SetData() override;
		~OpenGLIndexBuffer() override;

	private:
		uint32 BufferCount{ 1 };
	};

	class OpenGLVertexArray: public FVertexArray
	{
		
	public:
		OpenGLVertexArray();
		virtual void BindBuffer() override;
		virtual void UnBindBuffer() override;


		void BindBufferLayout() override;
		~OpenGLVertexArray();

		
	};
	
}
