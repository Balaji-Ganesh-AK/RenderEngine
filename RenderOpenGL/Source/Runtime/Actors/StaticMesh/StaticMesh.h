#pragma once
#include "Entity/Entity.h"
#include "RenderingSystem/Buffers.h"


namespace KREngine
{
	struct FModel;
	class FVertexArray;
	class FIndexBuffer;
	class FVertexBuffer;


	

	struct FStaticMesh 
	{
	public:

		FStaticMesh();
		FStaticMesh(const std::string& Name);
		


		std::shared_ptr<FModel> Model;
		FVertexBuffer* VertexBufferData = nullptr;
		FIndexBuffer* IndexBufferData= nullptr;
		FVertexArray* VertexArray=nullptr;

	
		uint32 MaxInstances = 10000;


		std::vector<float>VertexBuffer
		{



//0.0f,0.0f,0.0f,           0.0f, 0.0f,		0.0f,0.0f,-1.0f,
//1.0f,0.0f,0.0f,			1.0f, 0.0f,		0.0f,0.0f,-1.0f,
//1.0f,1.0f,0.0f,			1.0f, 1.0f,		0.0f,0.0f,-1.0f,
//0.0f,1.0f,0.0f,			0.0f, 1.0f,		0.0f,0.0f,-1.0f,
//
//0.0f,0.0f,1.0f,			1.0f, 0.0f,		 0.0f,0.0f,1.0f,
//1.0f,0.0f,1.0f,			0.0f, 0.0f,		 0.0f,0.0f,1.0f,
//1.0f,1.0f,1.0f,			0.0f, 1.0f,		 0.0f,0.0f,1.0f,
//0.0f,1.0f,1.0f,			1.0f, 1.0f,		 0.0f,0.0f,1.0f,
//
//0.0f,0.0f,1.0f,			0.0f, 0.0f,		-1.0f,0.0f,0.0f,
//0.0f,0.0f,0.0f,			1.0f, 0.0f,		-1.0f,0.0f,0.0f,
//0.0f,1.0f,0.0f,			1.0f, 1.0f,		-1.0f,0.0f,0.0f,
//0.0f,1.0f,1.0f,			0.0f, 1.0f,		-1.0f,0.0f,0.0f,
//
//1.0f,0.0f,0.0f,			0.0f, 0.0f,		1.0f,0.0f,0.0f,
//1.0f,0.0f,1.0f,			1.0f, 0.0f,		1.0f,0.0f,0.0f,
//1.0f,1.0f,1.0f,			1.0f, 1.0f,		1.0f,0.0f,0.0f,
//1.0f,1.0f,0.0f,			0.0f, 1.0f,		1.0f,0.0f,0.0f,
//
//0.0f,1.0f,0.0f,			0.0f, 0.0f,		 0.0f,1.0f,0.0f,
//1.0f,1.0f,0.0f,			1.0f, 0.0f,		 0.0f,1.0f,0.0f,
//1.0f,1.0f,1.0f,			1.0f, 1.0f,		 0.0f,1.0f,0.0f,
//0.0f,1.0f,1.0f,			0.0f, 1.0f,		 0.0f,1.0f,0.0f,
//
//0.0f,0.0f,1.0f,			0.0f, 0.0f,		 0.0f,-1.0f,0.0f,
//1.0f,0.0f,1.0f,			1.0f, 0.0f,		 0.0f,-1.0f,0.0f,
//1.0f,0.0f,0.0f,			1.0f, 1.0f,		 0.0f,-1.0f,0.0f,
//0.0f,0.0f,0.0f,			0.0f, 1.0f,		 0.0f,-1.0f,0.0f

		};
	private:


	};

	class FStaticMeshSystem : public FSystem
	{
	public:
		FStaticMeshSystem() = default;
		 void Init();
		 void Run() ;
		 void Stop();
		~FStaticMeshSystem();

#ifdef GUI
		void GUIInit();
		void GUIRun() ;
		void GUIStop();
#endif
	private:
	
		void LoadMesh();
		void SetUpMesh();

	};
}
