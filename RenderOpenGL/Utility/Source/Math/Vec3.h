#pragma once
#include <ostream>
#include "../Defines.h"
#include "../../../Dependencies/rapidjson/fwd.h"
#include "../../../Dependencies/nlohmann/json.hpp"
#include "../glm/glm/glm.hpp"


namespace  KREngine
{
	
	struct  vec3
	{
		float x, y, z;
		vec3();
		vec3( float x, float y, float z );
		
		static vec3 Random(float min = 0.000f , float max = 1.000f)
		{
			vec3 temp;
		
			temp.x = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
			temp.y = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
			temp.z = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
			return temp;
		};

		static vec3 Down();
		static vec3 Zero();
		static vec3 Up();
		static vec3 Right();
		static vec3 Left();

		vec3& Add( const vec3& other );
		vec3& Subtract( const vec3& other );
		vec3& Multiply( const vec3& other );
		vec3& Divide( const vec3& other );

		vec3& Add( float value );
		vec3& Subtract( float value );
		vec3& Multiply( float value );
		vec3& Divide( float value );
		float Distance(const vec3& other) const;
		float DistanceSqrt(const vec3& other) const;


		friend vec3 operator+( vec3 left, const vec3& right );
		friend vec3 operator-( vec3 left, const vec3& right );
		friend vec3 operator*( vec3 left, const vec3& right );
		friend vec3 operator/( vec3 left, const vec3& right );

		friend vec3 operator+( vec3 left, float value );
		friend vec3 operator-( vec3 left, float value );
		friend vec3 operator*( vec3 left, float value );
		friend vec3 operator/( vec3 left, float value );


		friend vec3 operator+(float value, vec3 left);
		friend vec3 operator-(float value, vec3 left);
		friend vec3 operator*(float value, vec3 left);
		friend vec3 operator/(float value, vec3 left);
	

		bool operator==( const vec3& other ) const;
		bool operator!=( const vec3& other ) const;
		bool operator>( const vec3& other ) const;
		bool operator<( const vec3& other ) const;
		bool operator>=( const vec3& other ) const;
		bool operator<=( const vec3& other ) const;

		vec3 operator+=( const vec3& other );
		vec3 operator-=( const vec3& other );
		vec3 operator*=( const vec3& other );
		vec3 operator/=( const vec3& other );

		vec3 operator+=( float value );
		vec3 operator-=( float value );
		vec3 operator*=( float value );
		vec3 operator/=( float value );


		float Magnitude() const;
		vec3 Normalize() const;
		float Dot( const vec3& other )const;

		
		//void Serialize(Writer<StringBuffer>& writer)
		//{
		//	/*writer.StartObject();
		//	writer.SetMaxDecimalPlaces(10);
		//	writer.Double(x);
		//	writer.Double(y);
		//	writer.Double(z);
		//	writer.EndObject();*/
		//}
		
		//glm::vec3 AsGLMVec3() const;
		//
		//static vec3  AsVec3(const glm::vec3& other);


	
		
		friend std::ostream& operator<<( std::ostream& stream, const vec3& other );
		const char* ToPrint() const
		{
			std::string return_string;
			return_string += "(" +  std::to_string(x) + "," + std::to_string(y)+ "," + std::to_string(z) + ")";
			return return_string.c_str();
		}
		std::string ToString() const
		{
			std::string return_string;
			return_string += "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
			return return_string;
		}

		KREngine::vec3 operator-(const glm::vec3& vec) const;
	};

	typedef KREngine::vec3 FVector;
	typedef KREngine::vec3 FRotation;

	
}
