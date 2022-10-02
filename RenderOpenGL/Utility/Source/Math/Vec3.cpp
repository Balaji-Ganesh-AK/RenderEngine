#include "Vec3.h"

#include <iostream>

#include "FMath.h"


namespace KREngine
{
	vec3::vec3() :x( 0.0f ), y( 0.0f ), z( 0.0f )
	{
	}

	vec3::vec3( float x, float y, float z ) : x( x ), y( y ), z( z )
	{
	}

	vec3 vec3::Down()
	{
		vec3 temp;
		temp.x = 0.0;
		temp.y = 1.0;
		temp.z = 0.0;
		return temp;
	}

	vec3 vec3::Zero()
	{
		vec3 temp;
		temp.x = 0.0;
		temp.y = 0.0;
		temp.z = 0.0;
		return temp;
	}

	vec3 vec3::Up()
	{
		vec3 temp;
		temp.x = 0;
		temp.y = -1;
		temp.z = 0;
		return temp;
	}

	vec3 vec3::Right()
	{
		vec3 temp;
		temp.x = 1;
		temp.y = 0;
		temp.z = 0;
		return temp;
	}

	vec3 vec3::Left()
	{
		vec3 temp;
		temp.x = -1;
		temp.y = 0;
		temp.z = 0;
		return temp;
	}

	vec3 vec3::Cross(const vec3 a, const vec3 b)
	{
		return{
		a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x,
		};
	
	}

	float vec3::Dot(const vec3 a, const vec3 b)
	{
		return { a.x * b.x + a.y * b.y + a.z * b.z };
	}

	vec3& vec3::Add( const vec3& other )
	{
		
		x = RoundOff(x) + RoundOff(other.x);
		y = RoundOff(y) + RoundOff(other.y);
		z = RoundOff(z) + RoundOff(other.z);

		//x += other.x;
		//y += other.y;
		//z += other.z;
		return *this;
	}

#pragma optimize("", off)
	vec3& vec3::Subtract( const vec3& other )
	{
		/*x =RoundOff(x);
		
		float tempY =RoundOff(other.y);
		float tempZ = RoundOff(other.z);
		y = RoundOff(y);
		z=  RoundOff(z);*/
		/*if (!close_enough(x, other.x))
			x -= other.x;
		else
			x = 0;
		if (!close_enough(y, other.y))
			y -= other.y;
		else
			y = 0;
		if (close_enough(z, other.z))
			z = 0;
		else
			z -= other.z;
		*/
		x = RoundOff(x) - RoundOff(other.x);
		y = RoundOff(y) - RoundOff(other.y);
		z = RoundOff(z) - RoundOff(other.z);

	/*	x -= other.x;
		y -= other.y;
		z -= other.z;*/
		return *this;
	}

#pragma optimize("", on)

	vec3& vec3::Multiply( const vec3& other )
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	vec3& vec3::Divide( const vec3& other )
	{
		x /= other.x;
		y /= other.y;
		y /= other.z;
		return *this;
	}

	vec3& vec3::Add( float value )
	{
		x += value;
		y += value;
		z -= value;
		return *this;
	}

	vec3& vec3::Subtract( float value )
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

	vec3& vec3::Multiply( float value )
	{
	
	/*	x = RoundOff(x) *value;
		y = RoundOff(y) *value;
		z = RoundOff(z) *value;*/

		x *=value;
		y *=value;
		z *=value;
		return *this;
	}

	vec3& vec3::Divide( float value )
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}

	float vec3::Distance(const vec3& other) const
	{
		const float diffx = x - other.x;
		const float diffy = y - other.y;
		const float diffz = z - other.z;

		return sqrt((diffx * diffx) + (diffy * diffy) + (diffz * diffz));
	}

	float vec3::DistanceSqrt(const vec3& other) const
	{
		const float diffx = x - other.x;
		const float diffy = y - other.y;
		const float diffz = z - other.z;

		return ((diffx * diffx) + (diffy * diffy) + (diffz * diffz));
	}

	bool vec3::operator==( const vec3& other ) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool vec3::operator!=( const vec3& other ) const
	{
		return !( *this == other );
	}

	bool vec3::operator>( const vec3& other ) const
	{
		return x > other.x && y > other.y && z > other.z;
	}

	bool vec3::operator<( const vec3& other ) const
	{
		return x < other.x&& y < other.y&& z < other.z;
	}

	bool vec3::operator>=( const vec3& other ) const
	{
		return x >= other.x && y >= other.y && z >= other.z;
	}

	bool vec3::operator<=( const vec3& other ) const
	{
		return x <= other.x && y <= other.y && z <= other.z;
	}

	vec3 vec3::operator+=( const vec3& other )
	{
		return Add( other );
	}

	vec3 vec3::operator-=( const vec3& other )
	{
		return Subtract( other );
	}

	vec3 vec3::operator*=( const vec3& other )
	{
		return Multiply( other );
	}

	vec3 vec3::operator/=( const vec3& other )
	{
		return Divide( other );
	}

	vec3 vec3::operator+=( float value )
	{
		return Add( value );
	}

	vec3 vec3::operator-=( float value )
	{
		return Subtract( value );
	}

	vec3 vec3::operator*=( float value )
	{
		return Multiply( value );
	}

	vec3 vec3::operator/=( float value )
	{
		return Divide( value );
	}

	float vec3::Magnitude() const
	{
		return sqrt( x * x + y * y + z * z );
	}

	void vec3::SetMagnitude(float new_mag)
	{
		
			const float mag = Magnitude();
			x = x * new_mag / mag;
			y = y * new_mag / mag;
			z = z * new_mag / mag;
		
	}

	vec3 vec3::Normalize() const
	{
		float temp = Magnitude();
		return vec3( x / temp, y / temp, z / temp );
	}

	float vec3::Dot( const vec3& other ) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	vec3 vec3::Cross(const vec3& other) const
	{
		return {
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x,
		};
	}

	KREngine::vec3 vec3::operator-(const glm::vec3& vec) const
	{
		return vec3{ x - vec.x, y - vec.y, z - vec.z };
	}


	//void vec3::Serialize(rapidjson::Writer<rapidjson::StringBuffer> stringwriter)
	


	
		

	

	//glm::vec3 vec3::AsGLMVec3() const
	//{
	//	/*const vec3 tempVec3 = Normalize();
	//	return glm::vec3( tempVec3.x, tempVec3.y, tempVec3.z );*/
	//	return glm::vec3( x, y, z );
	//}

	//vec3 vec3::AsVec3(const glm::vec3& other)
	//{
	//	return vec3{other.x, other.y, other.z};
	//}

	vec3 operator+( vec3 left, const vec3& right )
	{
		return left.Add( right );
	}

	vec3 operator-( vec3 left, const vec3& right )
	{
		return left.Subtract( right );
	}

	vec3 operator*( vec3 left, const vec3& right )
	{
		return left.Multiply( right );
	}

	vec3 operator/( vec3 left, const vec3& right )
	{
		return left.Divide( right );
	}

	vec3 operator+( vec3 left, float value )
	{
		return  vec3( left.x + value, left.y + value, left.z + value );
	}

	vec3 operator-( vec3 left, float value )
	{
		return  vec3( left.x - value, left.y - value, left.z - value );
	}

	vec3 operator*( vec3 left, float value )
	{
		return  { left.x * value, left.y * value, left.z * value };
	}

	vec3 operator/( vec3 left, float value )
	{
		return  vec3( left.x / value, left.y / value, left.z / value );
	}

	vec3 operator+(float value, vec3 left)
	{
		return  vec3(left.x + value, left.y + value, left.z + value);
	}

	vec3 operator-(float value, vec3 left)
	{
		return  vec3(left.x - value, left.y - value, left.z - value);
	}

	vec3 operator/(float value, vec3 left)
	{
		return  vec3(left.x / value, left.y / value, left.z / value);
	}

	vec3 operator*(float value, vec3 left)
	{
		return  vec3(left.x * value, left.y * value, left.z * value);
	}

	std::ostream& operator<<( std::ostream& stream, const vec3& other )
	{
		stream << "(" << other.x << "," << other.y << "," << other.z << ")";
		return stream;
	}
}
