#include "Buffers.h"
#include "../RenderingAPI/OpenGL/OpenGLBuffers.h"

KREngine::FVertexBuffer* KREngine::FVertexBuffer::CreateVertexBuffer( float* vertexPosition, uint32 size )
{

	return new OpenGLVertexBuffer( vertexPosition,size);
}

KREngine::FIndexBuffer* KREngine::FIndexBuffer::CreateIndexBuffer( unsigned int* indices, uint32 count )
{
	return new OpenGLIndexBuffer( indices, count );
}


KREngine::FFrameBuffer* KREngine::FFrameBuffer::CreateFrameBuffer(FFrameBufferSettings Settings)
{
	return new OpenGLFrameBuffer(Settings);
}


void KREngine::VertexBufferLayout::CalculateStride()
{
	for(std::vector<BufferElement>::value_type& Element : BufferElementList)
	{
		Element.Offset = Stride;
		Stride  = Stride + Element.Size;
	}
}


KREngine::FVertexArray* KREngine::FVertexArray::Create()
{
	return new OpenGLVertexArray();
}


