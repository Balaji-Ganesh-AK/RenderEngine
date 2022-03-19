#include "OpenGLBuffers.h"

#include "glad.h"


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

KREngine::OpenGLIndexBuffer::OpenGLIndexBuffer( unsigned int* indices, uint32 count ) : BufferCount(count)
{
	glGenBuffers(BufferSize, &RendererID );
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
	glDeleteFramebuffers( 1, &RendererID );
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
	glDeleteFramebuffers( 1, &RendererID );
}

//************************************************************** Frame buffer ******************************************************************
KREngine::OpenGLFrameBuffer::OpenGLFrameBuffer( float Width, float Height )
{
	InitializeFrameBuffer( Width, Height);
}

KREngine::OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
	glDeleteFramebuffers( 1, &RendererID );
	glDeleteFramebuffers( 1, &RendererTextureID );
	glDeleteFramebuffers( 1, &DepthAttachmentID );
}

void KREngine::OpenGLFrameBuffer::BindBuffer()
{
	glBindFramebuffer( GL_FRAMEBUFFER, RendererID );
}

void KREngine::OpenGLFrameBuffer::UnBindBuffer()
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

uint32 KREngine::OpenGLFrameBuffer::GetTextureRendererID()
{
	return RendererTextureID;
}

void KREngine::OpenGLFrameBuffer::InitializeFrameBuffer(float Width, float Height)
{
	if(RendererID)
	{
		glDeleteFramebuffers( 1, &RendererID );
		glDeleteFramebuffers( 1, &RendererTextureID );
		glDeleteFramebuffers( 1, &DepthAttachmentID );
	}


	glCreateFramebuffers( 1, &RendererID );
	glBindFramebuffer( GL_FRAMEBUFFER, RendererID );

	glCreateTextures( GL_TEXTURE_2D, 1, &RendererTextureID );
	glBindTexture( GL_TEXTURE_2D, RendererTextureID );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, static_cast< int >( Width ), static_cast< int >( Height ), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RendererTextureID, 0 );

	//depth texture
	glCreateTextures( GL_TEXTURE_2D, 1, &DepthAttachmentID );
	glBindTexture( GL_TEXTURE_2D, DepthAttachmentID );
	glTexStorage2D( GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, static_cast< int >( Width ), static_cast< int >( Height ) );
	//glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, Width, Height, 0,GL_DEPTH24_STENCIL8,GL_UNSIGNED_INT_24_8, NULL );

	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, DepthAttachmentID, 0 );

	//Error check
	//glCheckFramebufferStatus( GL_FRAMEBUFFER ) == GL_FRAMEBUFFER_COMPLETE;
	//
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void KREngine::OpenGLFrameBuffer::OnWindowResize(float width, float height)
{
	InitializeFrameBuffer( width, height );
}

