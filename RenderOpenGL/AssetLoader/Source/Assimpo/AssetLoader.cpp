

#include <filesystem>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include "../rapidjson/filewritestream.h"
#include "../rapidjson/writer.h"
//#include "Math/Vec3.h"
#include "../Utility/Source/Defines.h"
//#include "Math/Vec3.h"
#include "RenderOpenGL/Utility/Source/Logger.h"
#include "utility/Parameters.h"


//namespace  KREngine
//NEEDS TO GO INTO UTILITY PROJECT WHEN IT HAPPENS.
/**
 * \brief Default Object path
 */
#define DEFAULT_OBj_PATH "../Content/Models"


class FLoader
{
public:
    /*Loads in all the FBX from the default folder ../Content/Models/ */
    void LoadAllFBX();

    /*Loads in all the OBJ from the default folder ../Content/Models/ */
    void LoadAllOBJ();

    void LoadFBX(const std::string& path);
private:
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
    void ProcessNode(aiNode* node, const aiScene* scene);
};
	int main(int argumentCount, char* arguments[])
	{
		KREngine::FParameters Test(argumentCount, arguments);
        FLoader Loader;
			switch (
				Test.CurrentCommand)
			{
			case KREngine::ECommand::LoadFBX:
                Loader.LoadAllFBX();
                KREngine::Logger::Verbose("Loading Fbx files"); break;
			case KREngine::ECommand::LoadOBJ: break;
			default:
				std::cout << "Error";
			}

		std::cout << "Testing!";
		const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
		rapidjson::Document d;
		d.Parse(json);
		// ...
		rapidjson::Value& s = d["stars"];
		s.SetInt(s.GetInt() + 1);
		FILE* fp = fopen("../Content/output.json", "wb"); // non-Windows use "w"

		char writeBuffer[65536];
		rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

		rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
		d.Accept(writer);

		fclose(fp);
		return 0;
	}

	

	void FLoader::LoadAllFBX()
	{
		for (const std::filesystem::directory_entry& obj_path : std::filesystem::recursive_directory_iterator(DEFAULT_OBj_PATH))
		{
			if (obj_path.path().extension().compare( ".obj")  == 0 )
			{
				LoadFBX(obj_path.path().generic_string());
			}
		}
	}
   
	void FLoader::LoadAllOBJ()
	{
	}

void FLoader::LoadFBX(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		//TODO: Replace here
        KREngine::Logger::Error("Loading FBX failed with the following error: ", importer.GetErrorString());
		return;
	}
	std::string directory = path.substr(0,path.find_last_not_of("/"));

    ProcessNode(scene->mRootNode, scene);



}
void FLoader::ProcessNode(aiNode* node, const aiScene* scene)
{
	// process each mesh located at the current node
	for (uint32 i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene);
	}
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (uint32 i = 0; i < node->mNumChildren; i++)
	{
        ProcessNode(node->mChildren[i], scene);
	}

}
void FLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    for (uint32 i = 0; i < mesh->mNumVertices; i++)
    {
        KREngine::Logger::Verbose("Vertex {%f, %f, %f}, ", mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
      
    }
    // data to fill
    //std::vector<KREngine::FVector> vertices;
    //vector<unsigned int> indices;
    //vector<Texture> textures;

    //// walk through each of the mesh's vertices
    //for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    //{
    //    Vertex vertex;
    //    glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
    //    // positions
    //    vector.x = mesh->mVertices[i].x;
    //    vector.y = mesh->mVertices[i].y;
    //    vector.z = mesh->mVertices[i].z;
    //    vertex.Position = vector;
    //    // normals
    //    if (mesh->HasNormals())
    //    {
    //        vector.x = mesh->mNormals[i].x;
    //        vector.y = mesh->mNormals[i].y;
    //        vector.z = mesh->mNormals[i].z;
    //        vertex.Normal = vector;
    //    }
    //    // texture coordinates
    //    if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
    //    {
    //        glm::vec2 vec;
    //        // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
    //        // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
    //        vec.x = mesh->mTextureCoords[0][i].x;
    //        vec.y = mesh->mTextureCoords[0][i].y;
    //        vertex.TexCoords = vec;
    //        // tangent
    //        vector.x = mesh->mTangents[i].x;
    //        vector.y = mesh->mTangents[i].y;
    //        vector.z = mesh->mTangents[i].z;
    //        vertex.Tangent = vector;
    //        // bitangent
    //        vector.x = mesh->mBitangents[i].x;
    //        vector.y = mesh->mBitangents[i].y;
    //        vector.z = mesh->mBitangents[i].z;
    //        vertex.Bitangent = vector;
    //    }
    //    else
    //        vertex.TexCoords = glm::vec2(0.0f, 0.0f);

    //    vertices.push_back(vertex);
    //}
    //// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    //for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    //{
    //    aiFace face = mesh->mFaces[i];
    //    // retrieve all indices of the face and store them in the indices vector
    //    for (unsigned int j = 0; j < face.mNumIndices; j++)
    //        indices.push_back(face.mIndices[j]);
    //}
    //// process materials
    //aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    //// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    //// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    //// Same applies to other texture as the following list summarizes:
    //// diffuse: texture_diffuseN
    //// specular: texture_specularN
    //// normal: texture_normalN

    //// 1. diffuse maps
    //vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    //textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    //// 2. specular maps
    //vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    //textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    //// 3. normal maps
    //std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    //textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    //// 4. height maps
    //std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    //textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    //// return a mesh object created from the extracted mesh data
    //return Mesh(vertices, indices, textures);
}

	
