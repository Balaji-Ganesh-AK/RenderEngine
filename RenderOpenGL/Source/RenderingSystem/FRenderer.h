#pragma once
#include <memory>

#include "utility/Defines.h"


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

	/*Base render interface class*/
	class FRenderer
	{
	public:
		FRenderer() = default;
		virtual ~FRenderer();

		static FRenderer* CreateRenderer();

		/*Submit to the GPU*/
		virtual void Draw(const std::shared_ptr<FVertexArray>& vertexArray, const uint32 indexBufferCount) const =0 ;

		virtual void DrawIndexed(const std::shared_ptr<FVertexArray>& vertexArray, const uint32 indexBufferCount, uint32_t instanceID) const = 0 ;


		/*Init*/
		virtual void Init() = 0 ;
		virtual void ClearColor() = 0;
		virtual void SetClearColor(FColor color) = 0;
		virtual void SetViewPort(FViewPort viewport)=0;

	private:
		
	};
}
