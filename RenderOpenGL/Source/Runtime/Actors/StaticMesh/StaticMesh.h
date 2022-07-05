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

		std::vector<float>VertexBuffer;

	private:

	};

	class FStaticMeshSystem : public FSystem
	{
	public:
		FStaticMeshSystem() = default;
		 void Init() override;
		 void Run()  override;
		 void End() override;
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
