#pragma once
#include "RenderOpenGL/Utility/Source/Math/Color.h"
#include "RenderOpenGL/Utility/Source/Math/NumericLimit.h"
#include "RenderOpenGL/Utility/Source/Math/Vec3.h"


namespace KREngine
{
	class FVertexBuffer;
	class FShader;
	class FVertexArray;

	struct FRay
	{
		friend struct FLineSystem;

	public:
		FRay() = default;
		FRay(const FVector& direction, const float magnitude = 10, const FColor color = FColor::Red()) : Direction(direction), Magnitude(magnitude), Color(color)
		{
			EndLocation = Direction * Magnitude;
		}

	private:
		FVector Direction;
		float Magnitude = TNumericLimit<float>::Min();

		FVector EndLocation;
		FColor Color;


		std::shared_ptr<FShader> Shader;
		FVertexBuffer* VertexBufferData = nullptr;
		std::vector<float>VertexBuffer;
		FVertexArray* VertexArray = nullptr;
	};
}
