#pragma once
#include <memory>

#include "Buffers.h"
#include "RenderOpenGL/Utility/Source/Defines.h"
#include "RenderOpenGL/Utility/Source/Math/Vec3.h"


namespace KREngine
{
	class FIndexBuffer;
	struct FColor;
	class FVertexArray;


	struct FViewPort
	{
		uint32_t  X;
		uint32_t Y;
		uint32_t Width;
		int32_t Height;

	};

	struct FRenderSettings
	{
		uint32 MaxTrianglePerDrawCall = 10000;
		uint32 MaxVertexCount = 3 * MaxTrianglePerDrawCall;
		uint32 MaxIndexCount = 3 * MaxTrianglePerDrawCall;
		uint8 MaxTextureSlots = 32;
	};
	/*Contains all the info needed to render*/
	struct FRenderData
	{
		FRenderSettings Settings;
		VertexBufferLayout VertexBufferLayout;

		
	};
	/*Base render interface class*/
	class FRenderer
	{
	public:
		FRenderer() = default;
		virtual ~FRenderer();

		static FRenderer* CreateRenderer();

		/*Submit to the GPU*/
		/*Bind all the buffers before calling this step*/
		virtual void Draw(const uint32 indexBufferCount) const =0 ;
		virtual void DrawIndexed( const uint32 indexBufferCount, uint32 instanceTotalCount) const = 0 ;

		virtual void DrawLine(const uint32 count) const = 0;


		/*Init*/
		virtual void Init() = 0 ;
		virtual void ClearColor() = 0;
		virtual void SetClearColor(FColor color) = 0;
		virtual void SetViewPort(FViewPort viewport)=0;

		virtual void EnableWireFrameMode() const = 0;
		virtual void NormalRenderMode() const = 0;

	
	private:
		
	};
}
