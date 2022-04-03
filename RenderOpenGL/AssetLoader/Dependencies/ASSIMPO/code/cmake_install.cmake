# Install script for directory: E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.2.0-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/lib/Debug/assimp-vc142-mtd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/lib/Release/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/lib/MinSizeRel/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/lib/RelWithDebInfo/assimp-vc142-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.2.0x" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/bin/Debug/assimp-vc142-mtd.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/bin/Release/assimp-vc142-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/bin/MinSizeRel/assimp-vc142-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/bin/RelWithDebInfo/assimp-vc142-mt.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/anim.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/aabb.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/ai_assert.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/camera.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/color4.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/color4.inl"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/config.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/ColladaMetaData.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/commonMetaData.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/defs.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/cfileio.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/light.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/material.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/material.inl"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/matrix3x3.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/matrix3x3.inl"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/matrix4x4.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/matrix4x4.inl"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/mesh.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/ObjMaterial.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/pbrmaterial.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/GltfMaterial.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/postprocess.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/quaternion.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/quaternion.inl"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/scene.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/metadata.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/texture.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/types.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/vector2.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/vector2.inl"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/vector3.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/vector3.inl"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/version.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/cimport.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/importerdesc.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/Importer.hpp"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/DefaultLogger.hpp"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/ProgressHandler.hpp"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/IOStream.hpp"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/IOSystem.hpp"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/Logger.hpp"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/LogStream.hpp"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/NullLogger.hpp"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/cexport.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/Exporter.hpp"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/DefaultIOStream.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/DefaultIOSystem.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/ZipArchiveIOSystem.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/SceneCombiner.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/fast_atof.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/qnan.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/BaseImporter.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/Hash.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/MemoryIOWrapper.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/ParsingUtils.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/StreamReader.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/StreamWriter.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/StringComparison.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/StringUtils.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/SGSpatialSort.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/GenericProperty.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/SpatialSort.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/SkeletonMeshBuilder.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/SmallVector.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/SmoothingGroups.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/SmoothingGroups.inl"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/StandardShapes.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/RemoveComments.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/Subdivision.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/Vertex.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/LineSplitter.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/TinyFormatter.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/Profiler.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/LogAux.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/Bitmap.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/XMLTools.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/IOStreamBuffer.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/CreateAnimMesh.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/XmlParser.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/BlobIOSystem.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/MathFunctions.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/Exceptional.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/ByteSwapper.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/Base64.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/Compiler/pushpack1.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/Compiler/poppack1.h"
    "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/Debug/assimp-vc142-mtd.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "E:/Personal Projects/RenderEngine/RenderOpenGL/AssetLoader/Dependencies/ASSIMPO/code/RelWithDebInfo/assimp-vc142-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

