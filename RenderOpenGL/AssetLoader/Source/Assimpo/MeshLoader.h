#pragma once
#include <string>
#include <vector>

#include "RenderOpenGL/Utility/Source/Defines.h"


namespace KREngine
{
	class Vec2;
	/*Base class for loading a mesh
	 * combine all the nodes from a scene into a single static mesh.
	 */
	class FMeshLoader
	{
	public:
		std::string FileName;
		uint8 MeshCount{0};
		/*When combining the meshes as a single mesh, we need to keep a count to offset the index positions*/
		uint32 Offset {0};
		std::vector<float> VertexPositions;
		std::vector<float> VertexNormals;
		std::vector<float> TextureCords;
		std::vector<float> TextureTangent;
		std::vector<float> TextureBitTangent;
		std::vector<uint32> Indices;

		std::string DiffuseTexturePath;
		std::string SpecularTexturePath;
	};
}
