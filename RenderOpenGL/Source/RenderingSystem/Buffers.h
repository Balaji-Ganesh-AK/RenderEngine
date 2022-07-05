#pragma once
#include <string>
#include <vector>
#include "../Utility/Source/Defines.h"
#include "glad.h"
#include "glm/fwd.hpp"



namespace KREngine
{
	class FVertexArray;

	enum class EShaderDataType
	{
		None = 0,
		Float, FVec2, FVec3, FVec4,
		Int, IVec2, IVec3, IVec4,
		Mat3, Mat4,
		Bool
	};

	static glm::uint32_t ShaderDataTypeSize( EShaderDataType Type )
	{
		switch ( Type )
		{
			case EShaderDataType::Float:   return 4;
			case EShaderDataType::FVec2:  return 4 * 2;
			case EShaderDataType::FVec3:  return 4 * 3;
			case EShaderDataType::FVec4:  return 4 * 4;
			case EShaderDataType::Int:   return 4;
			case EShaderDataType::Bool:  return 1;
			case EShaderDataType::Mat3:  return 4 * 3 * 3;
			case EShaderDataType::Mat4:  return 4 * 4 * 4;
			case EShaderDataType::None: return 0;
			case EShaderDataType::IVec2:  return 4 * 2;
			case EShaderDataType::IVec3: return 4 * 3;
			case EShaderDataType::IVec4:  return 4 * 4;
			default:;
		}
		return 0;
	}

	static GLenum ShaderDataTypeToGLEnum(EShaderDataType type)
	{
		switch ( type )
		{

			case EShaderDataType::Float: return GL_FLOAT;
			case EShaderDataType::FVec2:return GL_FLOAT;
			case EShaderDataType::FVec3:return GL_FLOAT;
			case EShaderDataType::FVec4:return GL_FLOAT;
			case EShaderDataType::Mat3: return GL_FLOAT;
			case EShaderDataType::Mat4: return GL_FLOAT;
			case EShaderDataType::Int:  return GL_INT;
			case EShaderDataType::Bool: return GL_BOOL; 
			case EShaderDataType::None: break;
			case EShaderDataType::IVec2: break;
			case EShaderDataType::IVec3: break;
			case EShaderDataType::IVec4: break;
			//default: ;
		}
	}
	
	
	class FVertexBuffer
	{
	public:
		virtual ~FVertexBuffer() = default;

		static FVertexBuffer* CreateVertexBuffer(float* vertexPosition, uint32 size);
		
		virtual void BindBuffer() = 0;
		virtual void UnBindBuffer() = 0;
		virtual void SetData() = 0;
	protected:
		uint32 RendererID{0} ;
		float* VertexPosition = nullptr;
		

	};
	class FIndexBuffer
	{
	public:
		virtual ~FIndexBuffer() = default;

		static FIndexBuffer* CreateIndexBuffer( unsigned int* VertexPos, uint32 count );

		virtual void BindBuffer() = 0;
		virtual void UnBindBuffer() = 0;
		virtual void SetData() = 0;
		virtual uint32 GetIndexBufferCount() = 0;
	protected:
		uint32 RendererID{0};
		
		int* Indices = nullptr;

	};
	struct FFrameBufferSettings
	{
		float Width;
		float Height;

	};
	class FFrameBuffer
	{
	public:
		virtual ~FFrameBuffer() = default;

		static FFrameBuffer* CreateFrameBuffer(FFrameBufferSettings settings);

		virtual void BindBuffer() = 0;
		virtual void UnBindBuffer() = 0;
		virtual uint32 GetTextureRendererID() = 0 ;
		virtual void OnWindowResize( float width, float height ) = 0;


		virtual int ReadPixel(uint32 attachmentID, int x, int y) = 0;
	protected:
		FFrameBufferSettings Settings;
		uint32 RendererID{ 0 };
		uint32 RendererTextureID{ 0 };
		uint32 DepthAttachmentID{ 0 };
		uint32 EntityID{ 0 };

		std::vector<uint32_t> ColorAttachments;
	};

	struct BufferElement
	{
		std::string Name;
		EShaderDataType Type{EShaderDataType::None};
		uint32 Size;
		uint32 Offset;
		bool bNormalized;
		BufferElement( const std::string& name, EShaderDataType shaderDataType, bool normalized ) :Name( name ), Type( shaderDataType ), Size( ShaderDataTypeSize( shaderDataType ) ), Offset( 0 ),bNormalized( normalized )
		{
			
		}


		uint32 GetComponentCount() const
		{
			switch (Type) {
			case EShaderDataType::None: break;
			case EShaderDataType::Float: return 1;
			case EShaderDataType::FVec2: return 2;
			case EShaderDataType::FVec3: return 3;
			case EShaderDataType::FVec4: return 4;
			case EShaderDataType::Int: return 1;
			case EShaderDataType::IVec2:  return 2;
			case EShaderDataType::IVec3:  return 3;
			case EShaderDataType::IVec4:  return 4;
			case EShaderDataType::Mat3:  return 4*3;
			case EShaderDataType::Mat4:  return 4*4;
			case EShaderDataType::Bool:  return 1;
			default:return 0; }
			return 0;
		}
	};
	class VertexBufferLayout
	{
	public:
		VertexBufferLayout(const std::initializer_list<BufferElement>& inElements):BufferElementList(inElements)
		{
			CalculateStride();
		}
		std::vector<BufferElement> GetElements() const { return BufferElementList; }
		uint32 GetStride()const { return Stride; }
	private:
		void CalculateStride();
		std::vector<BufferElement> BufferElementList;
		uint32 Stride{ 0 };
	};
	class FVertexArray
	{
	public:
		virtual ~FVertexArray() = default;

		static FVertexArray* Create();

		virtual void BindBufferLayout() = 0;
		virtual void BindBuffer() = 0;
		virtual void UnBindBuffer() = 0;
		
		void SetLayOut(const VertexBufferLayout& vertex_buffer )
		{
	
				BufferLayout = vertex_buffer;
			
		}

	protected:

		VertexBufferLayout BufferLayout{};
		uint32 RendererID{0};
		
		
	};



}
