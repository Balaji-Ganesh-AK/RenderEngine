#include "OpenGLRenderer.h"


#include "Math/Color.h"
#include "RenderingSystem/Buffers.h"
#include "RenderOpenGL/Utility/Source/Math/Color.h"


namespace KREngine
{
	OpenGLRenderer::OpenGLRenderer()
	{
	}

	void OpenGLRenderer::Draw(const uint32 indexBufferCount) const
	{
		
		glDrawElements(GL_TRIANGLES, indexBufferCount, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderer::DrawIndexed( const uint32 indexBufferCount, uint32 instanceTotalCount) const 
	{
		
		glDrawElements(GL_TRIANGLES, indexBufferCount * instanceTotalCount, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderer::Init()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_CLAMP);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		//glFrontFace(GL_CCW);
		//glEnable(GL_FRONT);
	}

	void OpenGLRenderer::ClearColor()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	}

	void OpenGLRenderer::SetClearColor(FColor color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderer::SetViewPort(FViewPort viewport)
	{
		glViewport(viewport.X, viewport.Y, viewport.Width, viewport.Height);
	}
}
