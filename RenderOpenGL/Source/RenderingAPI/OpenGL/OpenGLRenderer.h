#pragma once
#include "RenderingSystem/FRenderer.h"


namespace KREngine
{
	class OpenGLRenderer: public FRenderer
	{
	public:
		OpenGLRenderer();
		~OpenGLRenderer() {};
		void Draw( const uint32 indexBufferCount) const override;
		void DrawIndexed( const uint32 indexBufferCount, uint32 instanceTotalCount) const override;
		void Init() override;
		void ClearColor() override;
		void SetClearColor(FColor color) override;
		void SetViewPort(FViewPort viewport) override;
		void DrawLine(const uint32 count) const override;

		void EnableWireFrameMode() const override;
		void NormalRenderMode() const override;
	private:

	};
}
