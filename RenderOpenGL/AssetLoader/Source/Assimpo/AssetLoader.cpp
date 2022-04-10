

#include <filesystem>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

//#include "Math/Vec3.h"
#include "../Utility/Source/Defines.h"
//#include "Math/Vec3.h"
#include <fstream>

#include "MeshLoader.h"
#include "RenderOpenGL/Utility/Source/Logger.h"
#include "RenderOpenGL/Utility/Source/File/FileHelper.h"
#include "RenderOpenGL/Utility/Source/File/FJson.h"
#include "RenderOpenGL/Utility/Source/Math/FMath.h"
#include "RenderOpenGL/Utility/Source/Math/Vec2.h"
#include "RenderOpenGL/Utility/Source/Math/Vec3.h"
#include "utility/Parameters.h"


//namespace  KREngine
//NEEDS TO GO INTO UTILITY PROJECT WHEN IT HAPPENS.
/**
 * \brief Default Object path
 */
#define DEFAULT_OBj_PATH "../Content/Models"
#define DEFAULT_OUTPUT_PATH   "../Content/"


class FLoader
{
public:
    /*Loads in all the FBX from the default folder ../Content/Models/ */
    void LoadAllFBX();

    /*Loads in all the OBJ from the default folder ../Content/Models/ */
    void LoadAllOBJ();

    void LoadFBX(const std::string& path);
    void LoadOBJ(std::filesystem::path::iterator::reference path);
    std::vector<std::string>AllowedExtenstion{ ".obj" ,".FBX", ".fbx"};
private:
    void ProcessMesh(aiMesh* mesh, const aiScene* scene, KREngine::FMeshLoader &loader);
    void ProcessNode(aiNode* node, const aiScene* scene, KREngine::FMeshLoader& loader);

    void ProcessScene(aiNode* node, const aiScene* scene , const std::string& filename);
};
	int main(int argumentCount, char* arguments[])
	{
		KREngine::FParameters parameters(argumentCount, arguments);
        FLoader loader;
			switch (
				parameters.CurrentCommand)
			{
			case KREngine::ECommand::LoadFBX:
                loader.LoadAllFBX();
                KREngine::Logger::Verbose("Loading Fbx files");
				break;
			case KREngine::ECommand::LoadOBJ:
                KREngine::Logger::Verbose("Loading OBJ files");
                loader.LoadAllOBJ();
				break;
			default:
				std::cout << "Error";
			}

		std::cout << "Testing!";
		
		return 0;
	}

	

	void FLoader::LoadAllFBX()
	{
		
	}
   
	void FLoader::LoadAllOBJ()
	{
        for (const std::filesystem::directory_entry& obj_path : std::filesystem::recursive_directory_iterator(DEFAULT_OBj_PATH))
        {
            for (const std::string& it : AllowedExtenstion)
            {
                if (obj_path.path().extension().compare(it) == 0)
                {

                    LoadOBJ(obj_path.path());
                }
            }
        }
	}

void FLoader::LoadFBX(const std::string& path)
{
	



}

void FLoader::LoadOBJ(std::filesystem::path::iterator::reference path)
{
    const std::string& file_path = path.generic_string();

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        //TODO: Replace here
        KREngine::Logger::Error("Loading OBJ failed with the following error: ", importer.GetErrorString());
        return;
    }
    const std::string& file_name = path.stem().generic_string();
    KREngine::FMeshLoader Loader;
   
    Loader.FileName = file_name;
    ProcessNode(scene->mRootNode, scene, Loader);

    std::string tes = DEFAULT_OUTPUT_PATH;
    std::string tesa = Loader.FileName;
    tes = tes + tesa + ".staticmesh";
    std::ofstream files_ofstream(tes);

    FJson j;
    j["Name"] = Loader.FileName.c_str();

    j["VertexPosition"] = KREngine::FJsonHelper::ToJson(Loader.VertexPositions);
    j["Normal"] = KREngine::FJsonHelper::ToJson(Loader.VertexNormals);
    j["TexCord"] = KREngine::FJsonHelper::ToJson(Loader.TextureCords);
    j["Indices"] = KREngine::FJsonHelper::ToJson(Loader.Indices);
    j["MeshCount"] = FJson{ Loader.MeshCount };

    files_ofstream << j.dump(2);
}

void FLoader::ProcessNode(aiNode* node, const aiScene* scene, KREngine::FMeshLoader& loader)
{
  
    // process each mesh located at the current node
    for (uint32 i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        loader.MeshCount++;
        if(loader.MeshCount > 1)
			loader.Offset = loader.Indices[loader.Indices.size()-1] + 1 ;
        KREngine::Logger::Warning("Name %s count %d:", mesh->mName.C_Str(), loader.MeshCount);
        ProcessMesh(mesh, scene, loader);
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (uint32 i = 0; i < node->mNumChildren; i++)
    {
        
        ProcessNode(node->mChildren[i], scene, loader);
    }
 

}



void FLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene, KREngine::FMeshLoader& loader)
{
    

    /* Get all the vertex*/
    for (uint32 i = 0; i < mesh->mNumVertices; i++)
    {
      //  KREngine::Logger::Verbose("Vertex {%f, %f, %f}, ", mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        loader.VertexPositions.emplace_back(mesh->mVertices[i].x);
        loader.VertexPositions.emplace_back(mesh->mVertices[i].y);
        loader.VertexPositions.emplace_back(mesh->mVertices[i].z);


        if (mesh->HasNormals())
        {
        	//KREngine::Logger::Verbose("Normals {%f, %f, %f}, ", mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            loader.VertexNormals.emplace_back(mesh->mNormals[i].x);
            loader.VertexNormals.emplace_back(mesh->mNormals[i].y);
            loader.VertexNormals.emplace_back(mesh->mNormals[i].z);
            
        }

        /*Reading only the first UV. Later we can support multiple uv maps*/
        if (mesh->mTextureCoords[0])
        {
			//KREngine::Logger::Verbose("Tex {%f, %f, %f}, ", mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, mesh->mTextureCoords[0][i].z);
            loader.TextureCords.emplace_back(mesh->mTextureCoords[0][i].x);
            loader.TextureCords.emplace_back(mesh->mTextureCoords[0][i].y);
        }
        //Push back empty?
        else
        {
            loader.TextureCords.emplace_back(0);
            loader.TextureCords.emplace_back(0);
        }
    }

    //Now Run through each face and get the index;
    for (uint64 i =0; i < mesh->mNumFaces;i++)
    {
        aiFace face = mesh->mFaces[i];
        for(uint64 j=0; j < face.mNumIndices; j++)
        {
          
            loader.Indices.push_back(face.mIndices[j] + loader.Offset);
        }
    }

  


 
  

}

	
