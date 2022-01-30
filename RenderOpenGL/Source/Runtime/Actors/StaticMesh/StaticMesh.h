#pragma
#include "Entity/Entity.h"
#include "RenderingSystem/Mesh.h"

namespace KREngine
{
	struct FStaticMesh : IComponents
	{
	public:


	private:
		std::shared_ptr<FVertexBuffer> VertexBufferData;
		std::shared_ptr<FIndexBuffer> IndexBufferData;
		std::shared_ptr<FVertexArray> VertexArray;
		friend class FRenderingSystem;
		KREngine::FTransform Transform;

		uint32 Indices [3 * 4 * 3] = {
			/**Front*/		0,1,2,
			/**Front*/		2,3,0,

			/**Back*/		4,5,6,
			/**Back*/		6,7,4,

			/**SideRight*/		8,9,10,
			/**SideRight*/		10,11,8,

			/**SideLeft*/		12,13,14,
			/**SideLeft*/		14,15,12,

			/**UP*/				16,17,18,
			/**UP*/				18,19,16,

			/**DOWN*/			20,21,22,
			/**DOWN*/			22,23,20
		};

		float s [8 * 24] = {
			//Vertex Positions	//Tex Cord		//Normals
			/** 0 */		-0.5f,-0.5f,-0.5f,		0.5f, 0.5f,		0.0f,0.0f,-1.0f,
			/** 1 */		0.5f,-0.5f,	-0.5f,		1.0f, 0.5f,		0.0f,0.0f,-1.0f,
			/** 2 */		0.5f,0.5f,	-0.5f,		1.0f, 1.0f,		0.0f,0.0f,-1.0f,
			/** 3 */		-0.5f,0.5f,	-0.5f,		0.5f, 1.0f,		0.0f,0.0f,-1.0f,

			/** 4 */		-0.5f,-0.5f,0.5f,		0.5f, 0.5f,		 0.0f,0.0f,1.0f,
			/** 5 */		0.5f,-0.5f,	0.5f,		1.0f, 0.5f,		 0.0f,0.0f,1.0f,
			/** 6 */		-0.5f,0.5f,	0.5f,		0.5f, 1.0f,		 0.0f,0.0f,1.0f,
			/** 7 */		0.5f,0.5f,	0.5f,		1.0f, 1.0f,		 0.0f,0.0f,1.0f,

			/** 8 */		-0.5f,0.5f,	-0.5f,		0.0f, 0.0f,		1.0f,0.0f,0.0f,
			/** 9 */		0.5f,0.5f,	-0.5f,		1.0f, 0.0f,		1.0f,0.0f,0.0f,
			/** 10 */		0.5f,0.5f,	0.5f,		1.0f, 1.0f,		1.0f,0.0f,0.0f,
			/** 11 */		-0.5f,0.5f,	0.5f,		0.0f, 1.0f,		1.0f,0.0f,0.0f,

			/** 12 */		-0.5f,-0.5f,-0.5f,		0.0f, 0.0f,		 -1.0f,0.0f,0.0f,
			/** 13 */		0.5f,-0.5f,	-0.5f,		1.0f, 0.0f,		 -1.0f,0.0f,0.0f,
			/** 14 */		0.5f,-0.5f,	0.5f,		1.0f, 1.0f,		 -1.0f,0.0f,0.0f,
			/** 15 */		-0.5f,-0.5f,0.5f,		0.0f, 1.0f,		 -1.0f,0.0f,0.0f,

			/** 16 */		0.5f,-0.5f,	-0.5f,		1.0f, 0.0f,		 0.0f,1.0f,0.0f,
			/** 17 */		0.5f,-0.5f,	0.5f,		0.0f, 0.0f,		 0.0f,1.0f,0.0f,
			/** 18 */		0.5f,0.5f,	0.5f,		0.0f, 1.0f,		 0.0f,1.0f,0.0f,
			/** 19 */		0.5f,0.5f,	-0.5f,		1.0f, 1.0f,		 0.0f,1.0f,0.0f,

			/** 20 */		-0.5f,-0.5f,-0.5f,		0.0f, 0.0f,		 0.0f,-1.0f,0.0f,
			/** 21 */		-0.5f,-0.5f,0.5f,		1.0f, 0.0f,		 0.0f,-1.0f,0.0f,
			/** 22 */		-0.5f,0.5f,	0.5f,		1.0f, 1.0f,		 0.0f,-1.0f,0.0f,
			/** 23 */		-0.5f,0.5f,	-0.5f,		0.0f, 1.0f,		 0.0f,-1.0f,0.0f

		};


		//	|----|
		//	|	 |
		//	|	 |
		//	|----|
		//		
		//|----|
		//|	   |
		//|	   |
		//|----|

		float Positions [8 * 24] = {
			//Vertex Positions		//Tex Cord		//Normals
			/** 0 */		0.0f,0.0f,0.0f,			0.0f, 0.0f,		0.0f,0.0f,-1.0f,
			/** 1 */		1.0f,0.0f,0.0f,			1.0f, 0.0f,		0.0f,0.0f,-1.0f,
			/** 2 */		1.0f,1.0f,0.0f,			1.0f, 1.0f,		0.0f,0.0f,-1.0f,
			/** 3 */		0.0f,1.0f,0.0f,			0.0f, 1.0f,		0.0f,0.0f,-1.0f,

			/** 4 */		0.0f,0.0f,1.0f,			1.0f, 0.0f,		 0.0f,0.0f,1.0f,
			/** 5 */		1.0f,0.0f,1.0f,			0.0f, 0.0f,		 0.0f,0.0f,1.0f,
			/** 6 */		1.0f,1.0f,1.0f,			0.0f, 1.0f,		 0.0f,0.0f,1.0f,
			/** 7 */		0.0f,1.0f,1.0f,			1.0f, 1.0f,		 0.0f,0.0f,1.0f,

			/** 8 */		0.0f,0.0f,1.0f,			0.0f, 0.0f,		-1.0f,0.0f,0.0f,
			/** 9 */		0.0f,0.0f,0.0f,			1.0f, 0.0f,		-1.0f,0.0f,0.0f,
			/** 10 */		0.0f,1.0f,0.0f,			1.0f, 1.0f,		-1.0f,0.0f,0.0f,
			/** 11 */		0.0f,1.0f,1.0f,			0.0f, 1.0f,		-1.0f,0.0f,0.0f,

			/** 12 */		1.0f,0.0f,0.0f,			0.0f, 0.0f,		1.0f,0.0f,0.0f,
			/** 13 */		1.0f,0.0f,1.0f,			1.0f, 0.0f,		1.0f,0.0f,0.0f,
			/** 14 */		1.0f,1.0f,1.0f,			1.0f, 1.0f,		1.0f,0.0f,0.0f,
			/** 15 */		1.0f,1.0f,0.0f,			0.0f, 1.0f,		1.0f,0.0f,0.0f,

			/** 16 */		0.0f,1.0f,0.0f,			0.0f, 0.0f,		 0.0f,1.0f,0.0f,
			/** 17 */		1.0f,1.0f,0.0f,			1.0f, 0.0f,		 0.0f,1.0f,0.0f,
			/** 18 */		1.0f,1.0f,1.0f,			1.0f, 1.0f,		 0.0f,1.0f,0.0f,
			/** 19 */		0.0f,1.0f,1.0f,			0.0f, 1.0f,		 0.0f,1.0f,0.0f,

			/** 20 */		0.0f,0.0f,1.0f,			0.0f, 0.0f,		 0.0f,-1.0f,0.0f,
			/** 21 */		1.0f,0.0f,1.0f,			1.0f, 0.0f,		 0.0f,-1.0f,0.0f,
			/** 22 */		1.0f,0.0f,0.0f,			1.0f, 1.0f,		 0.0f,-1.0f,0.0f,
			/** 23 */		0.0f,0.0f,0.0f,			0.0f, 1.0f,		 0.0f,-1.0f,0.0f

		};
	};

	class FStaticMeshSystem : public FGameSystem
	{
	public:
		virtual void Init() override;
		virtual void Run() override;
		virtual void Stop() override;
		~FStaticMeshSystem() override;

#ifdef GUI
		void GUIInit() override;
		void GUIRun() override;
		void GUIStop() override;
#endif
	private:
		void LoadMesh();
		void SetUpMesh();
	};
}
