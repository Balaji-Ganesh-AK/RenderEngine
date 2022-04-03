#include "Color.h"

namespace KREngine
{
	FColor::FColor() :r( 0.0f ), g( 0.0f ), b( 0.0f ), a( 0.0f )
	{
	}

	FColor::FColor( float r, float g, float b, float a ) : r( r ), g( g ), b( b ), a( a )
	{

	}

	/*FColor::FColor(vec4& vec4): r( vec4.x ), g( vec4.y ), b( vec4.z ), a( vec4.w )
	{
		
	}*/

	//FColor::FColor( vec4& vec4 ) : r( vec4.x ), g( vec4.y ), b( vec4.z ), a( vec4.w )
	//{
	//	
	//}

	FColor FColor::Down()
	{
		FColor temp;
		temp.r = 0.0;
		temp.g = -1.0;
		temp.b = 0.0;
		temp.a = 0.0;
		return temp;
	}

	FColor FColor::Zero()
	{
		FColor temp;
		temp.r = 0.0;
		temp.g = 0.0;
		temp.b = 0.0;
		temp.a = 0.0;
		return temp;
	}

	FColor FColor::Up()
	{
		FColor temp;
		temp.r = 0;
		temp.g = 1;
		temp.b = 0;
		temp.a = 0.0;
		return temp;
	}

	FColor FColor::Right()
	{
		FColor temp;
		temp.r = 1;
		temp.g = 0;
		temp.b = 0;
		temp.a = 0.0;
		return temp;
	}

	FColor FColor::Left()
	{
		FColor temp;
		temp.r = -1;
		temp.g = 0;
		temp.b = 0;
		temp.a = 0.0;
		return temp;
	}

	FColor& FColor::Add( const FColor& other )
	{
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;
		return *this;
	}

	FColor& FColor::Subtract( const FColor& other )
	{
		g -= other.g;
		r -= other.r;
		b -= other.b;
		a -= other.a;
		return *this;
	}

	FColor& FColor::Multiply( const FColor& other )
	{
		r *= other.r;
		g *= other.g;
		b *= other.b;
		a *= other.a;
		return *this;
	}

	FColor& FColor::Divide( const FColor& other )
	{
		r /= other.r;
		g /= other.g;
		g /= other.b;
		a /= other.a;
		return *this;
	}

	FColor& FColor::Add( float value )
	{
		r += value;
		g += value;
		b -= value;
		a -= value;
		return *this;
	}

	FColor& FColor::Subtract( float value )
	{
		r -= value;
		g -= value;
		b -= value;
		a -= value;
		return *this;
	}

	FColor& FColor::Multiply( float value )
	{
		r *= value;
		g *= value;
		b *= value;
		a *= value;
		return *this;
	}

	FColor& FColor::Divide( float value )
	{
		r /= value;
		g /= value;
		b /= value;
		a /= value;
		return *this;
	}

	bool FColor::operator==( const FColor& other ) const
	{
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}

	bool FColor::operator!=( const FColor& other ) const
	{
		return !( *this == other );
	}

	bool FColor::operator>( const FColor& other ) const
	{
		return r > other.r && g > other.g && b > other.b && a > other.a;
	}

	bool FColor::operator<( const FColor& other ) const
	{
		return r < other.r&& g < other.g&& b < other.b&& a < other.a;
	}

	bool FColor::operator>=( const FColor& other ) const
	{
		return r >= other.r && g >= other.g && b >= other.b && a >= other.a;
	}

	bool FColor::operator<=( const FColor& other ) const
	{
		return r <= other.r && g <= other.g && b <= other.b && a <= other.a;
	}

	FColor FColor::operator+=( const FColor& other )
	{
		return Add( other );
	}

	FColor FColor::operator-=( const FColor& other )
	{
		return Subtract( other );
	}

	FColor FColor::operator*=( const FColor& other )
	{
		return Multiply( other );
	}

	FColor FColor::operator/=( const FColor& other )
	{
		return Divide( other );
	}

	FColor FColor::operator+=( float value )
	{
		return Add( value );
	}

	FColor FColor::operator-=( float value )
	{
		return Subtract( value );
	}

	FColor FColor::operator*=( float value )
	{
		return Multiply( value );
	}

	FColor FColor::operator/=( float value )
	{
		return Divide( value );
	}

	float FColor::Magnitude() const
	{
		return sqrt( r * r + g * g + b * b + a * a );
	}

	FColor FColor::Normalize() const
	{
		float temp = Magnitude();
		return FColor( r / temp, g / temp, b / temp, a / temp );
	}

	float FColor::Dot( const FColor& other ) const
	{
		return r * other.r + g * other.g + b * other.b + a * other.a;
	}

	FColor operator+( FColor left, const FColor& right )
	{
		return left.Add( right );
	}

	FColor operator-( FColor left, const FColor& right )
	{
		return left.Subtract( right );
	}

	FColor operator*( FColor left, const FColor& right )
	{
		return left.Multiply( right );
	}

	FColor operator/( FColor left, const FColor& right )
	{
		return left.Divide( right );
	}

	FColor operator+( FColor left, float value )
	{
		return  FColor( left.r + value, left.g + value, left.b + value, left.a + value );
	}

	FColor operator-( FColor left, float value )
	{
		return  FColor( left.r - value, left.g - value, left.b - value, left.a - value );
	}

	FColor operator*( FColor left, float value )
	{
		return  FColor( left.r * value, left.g * value, left.b * value, left.a * value );
	}

	FColor operator/( FColor left, float value )
	{
		return  FColor( left.r / value, left.g / value, left.b / value, left.b / value );
	}

	std::ostream& operator<<( std::ostream& stream, const FColor& other )
	{
		stream << "(" << other.r << "," << other.g << "," << other.b << "," << other.a << ")";
		return stream;
	}
}
