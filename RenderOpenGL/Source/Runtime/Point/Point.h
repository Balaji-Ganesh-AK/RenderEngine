#pragma once
#include "Entity/Entity.h"

namespace KREngine
{
	class FVertexArray;
	class FVertexBuffer;
	class FShader;

	struct FPoint
	{
		FVector Point;

	private:
		std::shared_ptr<FShader> Shader;
		FVertexBuffer* VertexBufferData = nullptr;
		std::vector<float>VertexBuffer;
		FVertexArray* VertexArray = nullptr;
	};

	class PointSystem: FSystem
	{
	public:
		~PointSystem() override;
		void Init() override;
		void Run() override;
		void End() override;
		void GUIInit() override;
		void GUIRun() override;
		void GUIEnd() override;
	};
}

