#include "OpenGLBuffers.h"


KREngine::OpenGLVertexBuffer::OpenGLVertexBuffer(float* VertexPos, uint32 count )
{
	glGenBuffers( BufferCount, &RendererID );
	glBindBuffer( GL_ARRAY_BUFFER, RendererID );
	glBufferData( GL_ARRAY_BUFFER, count * sizeof( float ), VertexPos, GL_STATIC_DRAW );
}

void KREngine::OpenGLVertexBuffer::BindBuffer()
{
	glBindBuffer( GL_ARRAY_BUFFER, RendererID );
}

void KREngine::OpenGLVertexBuffer::UnBindBuffer()
{
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void KREngine::OpenGLVertexBuffer::SetData()
{
}

KREngine::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers( BufferCount, &RendererID );
}
//************************************************************** Index Buffer *********************************

KREngine::OpenGLIndexBuffer::OpenGLIndexBuffer( unsigned int* indices, uint32 count )
{
	glGenBuffers( BufferCount, &RendererID );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, RendererID );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, count * sizeof( unsigned int ), indices, GL_STATIC_DRAW );

}

void KREngine::OpenGLIndexBuffer::BindBuffer()
{
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, RendererID );
}

void KREngine::OpenGLIndexBuffer::UnBindBuffer()
{
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);
}

void KREngine::OpenGLIndexBuffer::SetData()
{
	glDeleteBuffers( BufferCount, &RendererID );
}

KREngine::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
}
//************************************************************** FVertexArray *********************************
KREngine::OpenGLVertexArray::OpenGLVertexArray()
{
	glGenVertexArrays( 1, &RendererID );
	glBindVertexArray( RendererID );
}

void KREngine::OpenGLVertexArray::BindBuffer()
{
	glBindVertexArray( RendererID );
}

void KREngine::OpenGLVertexArray::UnBindBuffer()
{
	glBindVertexArray( 0 );
}

void KREngine::OpenGLVertexArray::BindBufferLayout()
{
	uint8 index{ 0 };
	for ( const BufferElement& bufferElement : BufferLayout.GetElements() )
	{	
		glEnableVertexAttribArray( index );
		glVertexAttribPointer( index, bufferElement.GetComponentCount(), ShaderDataTypeToGLEnum( bufferElement.Type ), bufferElement.bNormalized, BufferLayout.GetStride(), reinterpret_cast< void* >( bufferElement.Offset ) );
		index++;
	}
}

KREngine::OpenGLVertexArray::~OpenGLVertexArray()
{
}
