#include "OpenGLBuffers.h"

#include "glad.h"


KREngine::OpenGLVertexBuffer::OpenGLVertexBuffer(float* VertexPos, uint32 count )
{
	glGenBuffers( BufferSize, &RendererID );
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
	glDeleteBuffers( BufferSize, &RendererID );
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
KREngine::OpenGLFrameBuffer::OpenGLFrameBuffer(const FFrameBufferSettings settings)
{
	Settings = settings;
	InitializeFrameBuffer( );
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
	glViewport(0, 0, static_cast<int>(Settings.Width), static_cast<int>(Settings.Height));
	int invalidId = -1;
	glClearTexImage(ColorAttachments[1], 0, GL_RED_INTEGER, GL_INT, &invalidId);
}

void KREngine::OpenGLFrameBuffer::UnBindBuffer()
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

uint32 KREngine::OpenGLFrameBuffer::GetTextureRendererID()
{
	/*Refactor this*/
	return ColorAttachments[0];
}

void KREngine::OpenGLFrameBuffer::InitializeFrameBuffer()
{
	if(RendererID)
	{
		glDeleteFramebuffers( 1, &RendererID );
		glDeleteFramebuffers( 1, &RendererTextureID );
		glDeleteFramebuffers(1, &DepthAttachmentID);
		glDeleteFramebuffers( 2, ColorAttachments.data());
	}


	glCreateFramebuffers( 1, &RendererID );
	glBindFramebuffer( GL_FRAMEBUFFER, RendererID );


	ColorAttachments.resize(2);
	glCreateTextures( GL_TEXTURE_2D, 2, ColorAttachments.data());
	glBindTexture( GL_TEXTURE_2D, ColorAttachments[0]);

	//Goes into color attachment function
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, static_cast< int >( Settings.Width ), static_cast< int >(Settings.Height), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorAttachments[0], 0 );



	glBindTexture(GL_TEXTURE_2D, ColorAttachments[1]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, static_cast<int>(Settings.Width), static_cast<int>(Settings.Height), 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, ColorAttachments[1], 0);



	//depth texture
	glCreateTextures( GL_TEXTURE_2D, 1, &DepthAttachmentID );
	glBindTexture( GL_TEXTURE_2D, DepthAttachmentID );
	glTexStorage2D( GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, static_cast< int >(Settings.Width), static_cast< int >(Settings.Height) );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, Width, Height, 0,GL_DEPTH24_STENCIL8,GL_UNSIGNED_INT_24_8, NULL );

	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, DepthAttachmentID, 0 );


	GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(2, buffers);
	


	//Error check
	glCheckFramebufferStatus( GL_FRAMEBUFFER ) == GL_FRAMEBUFFER_COMPLETE;
	//
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void KREngine::OpenGLFrameBuffer::OnWindowResize(float width, float height)
{
	Settings.Width = width;
	Settings.Height = height;
	InitializeFrameBuffer();
}

int KREngine::OpenGLFrameBuffer::ReadPixel(uint32 attachmentID, int x, int y)
{
	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentID);
	int pixelData;
	glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
	return pixelData;
}

