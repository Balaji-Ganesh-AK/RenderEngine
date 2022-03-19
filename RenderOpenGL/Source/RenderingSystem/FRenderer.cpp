#include "FRenderer.h"

#include "RenderingAPI/OpenGL/OpenGLRenderer.h"

namespace KREngine
{
	FRenderer::~FRenderer()
	{
	}

	FRenderer* KREngine::FRenderer::CreateRenderer()
	{
		
		return new OpenGLRenderer();
	}
}
