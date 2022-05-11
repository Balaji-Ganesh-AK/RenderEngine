#include "AssetSystem.h"

#include <stack>

#include "RenderOpenGL/Utility/Source/File/FileHelper.h"
#include "RenderOpenGL/Utility/Source/File/FJson.h"
#include "Runtime/Actors/StaticMesh/StaticMesh.h"
#include "utility/File/Logger.h"



namespace KREngine
{
	FModel::FModel(FGeometryID ID) : GeometryId(ID)
	{
	}

	FAssetManager* FAssetManager::Create()
	{
		return new FAssetManager();
	} 

	void FAssetManager::Init()
	{
		const std::string Path = DefaultContentPath;
		LoadAssets(Path);
	}

	std::shared_ptr<FModel> FAssetManager::GetModel(const std::string& name)
	{
		return AssetMap[AssetNameToID[name]];
	
	}

	std::shared_ptr<FModel> FAssetManager::GetModel(const FGeometryID id)
	{
		return AssetMap[id];
	}

	FAssetManager::FAssetManager()
	{
	}

	void FAssetManager::LoadAssets(const std::string path)
	{
		AssetNameToID["Default"] = GeometryAssetCount;
		AssetMap[GeometryAssetCount] = std::make_shared<FModel>(GeometryAssetCount);
		AssetNameToFullPath["Default"] = "Default";
		GeometryAssetCount++;

		for (const std::filesystem::directory_entry& asset_path : std::filesystem::recursive_directory_iterator(path))
		{
			for (const std::string& it : AllowedExtenstion)
			{
				if (asset_path.path().extension().compare(it) == 0 )
				{
					/*TODO make is better*/
					Logger::Verbose("Reading %s", asset_path.path().generic_string().c_str());
					EFileExtension file_extension = StringToFileExtension(it);
					switch (file_extension)
					{
					case EFileExtension::StaticMesh:
						ReadStaticMesh(asset_path.path().generic_string());
						break;
					case EFileExtension::UnKnown:
					default:
						Logger::Error("Error reading unknown file type");
						
					}
				}
			}
		}

	}

	void FAssetManager::ReadStaticMesh(const std::string path)
	{
		std::ifstream input(path, std::ios::binary);
		std::vector<uint8_t> static_mesh_data(std::istreambuf_iterator<char>(input), {});
		FJson json = FJson::from_cbor((static_mesh_data));
		
		std::string Name;
		FModel static_mesh_model(GeometryAssetCount);
		if (json.contains("Name"))
		{
			Name = json["Name"];
			Logger::Verbose("Reading static mesh from file : %s", Name.c_str());
		}
		else
		{
			Logger::Warning("The static mesh file has no name, file: %s", path.c_str());
		}
		if (json.contains("VertexPosition"))
		{
		/*	const std::string name = json["VertexPosition"];
			Logger::Verbose("Reading static mesh from file : %s", name.c_str());*/
			
			for(int i =0;i<json["VertexPosition"].size() ; i = i+ 3)
			{
				float x = json["VertexPosition"][i + 0];
				float y = json["VertexPosition"][i + 1 ];
				float z = json["VertexPosition"][i + 2];
				static_mesh_model.VertexPositionBuffer.emplace_back(x,y,z);
				
			}
			
			for (int i = 0; i < json["Normal"].size(); i = i + 3)
			{
				float x = json["Normal"][i + 0];
				float y = json["Normal"][i + 1];
				float z = json["Normal"][i + 2];
				static_mesh_model.NormalBuffer.emplace_back(x, y, z);
			}
			for (int i = 0; i < json["TexCord"].size(); i = i + 2)
			{
				float x = json["TexCord"][i + 0];
				float y = json["TexCord"][i + 1];
				static_mesh_model.TextureCordBuffer.emplace_back(x, y);
			}

			for (int i = 0; i < json["Indices"].size(); i++)
			{
				int x = json["Indices"][i];
				static_mesh_model.IndexPositions.emplace_back(x);
			}

			FTriangleID TriangleID = 0;

			for (int i = 0; i < json["Indices"].size(); i = i+3)
			{
				int index_one = json["Indices"][i + 0];
				int index_two = json["Indices"][i + 1];
				int index_three = json["Indices"][i + 2];
				FVector vertex_one = static_mesh_model.VertexPositionBuffer[index_one];
				FVector vertex_two = static_mesh_model.VertexPositionBuffer[index_two];
				FVector vertex_three = static_mesh_model.VertexPositionBuffer[index_three];



				FTriangle triangle{ vertex_one,vertex_two,vertex_three, TriangleID };
				static_mesh_model.Triangles.push_back(triangle);
				static_mesh_model.TriangleIDToClusterIDBuffer.push_back(TriangleID);
				static_mesh_model.TriangleIDToClusterIDBuffer.push_back(TriangleID);
				static_mesh_model.TriangleIDToClusterIDBuffer.push_back(TriangleID);
				TriangleID++;
			}
			CalculateAdjacentTriangle(static_mesh_model);
			Logger::Verbose("Total triangles %d", static_mesh_model.Triangles.size());

		}
		else
		{
			Logger::Error("The static mesh file has no vertex position, file: %s", path.c_str());
		}



		AssetNameToID[Name] = GeometryAssetCount;
		AssetMap[GeometryAssetCount] = std::make_shared<FModel>(static_mesh_model);
		AssetNameToFullPath[Name] = path;
		GeometryAssetCount++;
	}
	void FAssetManager::CalculateAdjacentTriangle(FModel& model)
	{
		{
			std::unordered_map<uint64, std::set<FTriangle>> clusters;
			std::unordered_map<FTriangleID, FTriangle> TriangleList;
			std::unordered_map<FTriangle, std::vector<FTriangle>, hash_fn> adjacent_list;
			FScopedTimer test{ "Tesitng" };

			for (FTriangle& triangle : model.Triangles)
			{
				TriangleList.insert_or_assign(triangle.GetTrianlgeID(),triangle);
				std::vector<FTriangle> temp_triangle;
				temp_triangle.reserve(model.Triangles.size());
				for (int i = 0; i < model.Triangles.size(); i++)
				{

					if (triangle.IsEdgeConnected(model.Triangles[i]))
					{
						temp_triangle.emplace_back(model.Triangles[i]);
					}
				}
				if (adjacent_list.contains(triangle))
				{
					auto& list = adjacent_list[triangle];
					list.insert(list.end(), temp_triangle.begin(), temp_triangle.end());
			

				}
				else
				{
					adjacent_list.insert_or_assign(triangle, temp_triangle);
				}


			}

			
				
			
				std::queue<FTriangle> stack_triangles;
				/*Index to triangles*/
			
				
				std::set<FTriangle> temp_cluster_triangles;
				stack_triangles.push(model.Triangles[0]);
			{
				uint8 cluster_count = 0;
				uint64 cluster_index = 0;
				std::set<FTriangle> visited_triangles;
				while (!stack_triangles.empty())
					{


						if (cluster_count == 20)
						{
							cluster_count = 0;
							clusters[cluster_index] = temp_cluster_triangles;
							temp_cluster_triangles.clear();

							cluster_index++;
						}

						FTriangle& current_triangles_id = stack_triangles.front();
						stack_triangles.pop();



						if (!visited_triangles.contains(current_triangles_id))
						{
							visited_triangles.insert(current_triangles_id);
							model.Triangles[current_triangles_id.GetTrianlgeID()].ClusterID = cluster_index;
							temp_cluster_triangles.insert(current_triangles_id);
							cluster_count++;
							auto& connected_triangles = adjacent_list[current_triangles_id];
							for (int i = 0; i < connected_triangles.size(); i++)
							{
								if (!visited_triangles.contains(connected_triangles[i]))
								{
									stack_triangles.push(connected_triangles[i]);

								}
							}
						}



						if (stack_triangles.empty())
						{
							cluster_count = 0;
							clusters[cluster_index] = temp_cluster_triangles;
							temp_cluster_triangles.clear();

							cluster_index++;
						}
						if (stack_triangles.empty() && visited_triangles.size() != adjacent_list.size())
						{
							stack_triangles.push(model.Triangles[visited_triangles.size()+1]);
							
						}

					}
				}

				int totalsize = 0;
			for (auto cluster : clusters)
			{
				totalsize += cluster.second.size();
			}
			model.Clusters.clear();
			model.Clusters = clusters;
			Logger::Warning("Total size %d", totalsize);
		}
		//model.TriangleAdjacentList = adjacent_list;


		/*for(const auto& toprint: adjacent_list)
		{
			for (const FTriangle& toprintvalue : toprint.second)
			{
				Logger::Warning("Adjacent list for id: %d %s", toprint.first.GetTrianlgeID(), toprintvalue.Print());
			}
		}*/
	}
}
