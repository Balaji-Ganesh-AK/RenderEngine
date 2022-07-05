#pragma once
#include <filesystem>
#include <memory>
#include <set>
#include <unordered_map>


#include "Math/FTriangle.h"
#include "Math/Vec3.h"
#include "RenderOpenGL/Utility/Source/Math/Vec2.h"
#include "RenderOpenGL/Utility/Source/Math/NumericLimit.h"

namespace KREngine
{





	struct FStaticMesh;
	struct FModel
	{
	
		FModel(FGeometryID ID);

		uint32 Indices[3 * 4 * 3] = {

			/**Front*/		 0, 1, 3,
			/**Front*/		3, 1, 2,

			/**Back*/		 1, 5, 2,
			/**Back*/		2, 5, 6,

			/**SideRight*/		 5, 4, 6,
			/**SideRight*/		6, 4, 7,

			/**SideLeft*/		 4, 0, 7,
			/**SideLeft*/		7, 0, 3,

			/**UP*/				  3, 2, 7,
			/**UP*/				 7, 2, 6,

			/**DOWN*/			 4, 5, 0,
			/**DOWN*/			 0, 5, 1
		};



		std::vector<uint32> TexIndices
		{
			0,1,2,
			3,1,2,
		};
		std::vector<uint32> IndexPositions{
		};
		std::vector<FVector> VertexPositionBuffer =
		{
		};
		std::vector<Vec2> TextureCordBuffer =
		{

		};
		std::vector<FVector> NormalBuffer =
		{

		};

		std::vector<FTriangleID> TriangleIDToClusterIDBuffer;

		std::vector<FTriangle> Triangles;
		std::unordered_map<uint64, std::set<FTriangle>> Clusters;
		std::string FName;

	private:
		FGeometryID GeometryId { TNumericLimit<uint64>::Max() };
	};
	class FAssetManager
	{
	public:
		static FAssetManager* Create();

		void Init();

		std::shared_ptr<FModel> GetModel(const std::string& name);
		std::shared_ptr<FModel> GetModel(const FGeometryID id);

	private:


		FAssetManager();
		void LoadAssets(const std::string path);

		void ReadStaticMesh(const std::string path);


		void CalculateAdjacentTriangle(FModel& model);

		std::unordered_map<std::string, FGeometryID> AssetNameToID;

		std::unordered_map<FGeometryID, std::shared_ptr<FModel>> AssetMap;

		std::unordered_map < std::string, std::filesystem::path> AssetNameToFullPath;

		std::vector<std::string>AllowedExtenstion{ ".staticmesh" };

		double SceneScale;

		uint64 GeometryAssetCount{ 0 };
	};
}
