#pragma once
#include <ostream>


namespace  KREngine
{

	struct  FColor
	{
		float r, g, b, a;
		FColor();
		FColor( float r, float g, float b, float a );
		//FColor( vec4& vec4 );

		static FColor Red();
		static FColor Blue();
		static FColor Green();
		static FColor Down();
		static FColor Zero();
		static FColor Up();
		static FColor Right();
		static FColor Left();
		
		FColor& Add( const FColor& other );
		FColor& Subtract( const FColor& other );
		FColor& Multiply( const FColor& other );
		FColor& Divide( const FColor& other );

		FColor& Add( float value );
		FColor& Subtract( float value );
		FColor& Multiply( float value );
		FColor& Divide( float value );

		friend FColor operator+( FColor left, const FColor& right );
		friend FColor operator-( FColor left, const FColor& right );
		friend FColor operator*( FColor left, const FColor& right );
		friend FColor operator/( FColor left, const FColor& right );

		friend FColor operator+( FColor left, float value );
		friend FColor operator-( FColor left, float value );
		friend FColor operator*( FColor left, float value );
		friend FColor operator/( FColor left, float value );

		bool operator==( const FColor& other ) const;
		bool operator!=( const FColor& other ) const;
		bool operator>( const FColor& other ) const;
		bool operator<( const FColor& other ) const;
		bool operator>=( const FColor& other ) const;
		bool operator<=( const FColor& other ) const;

		FColor operator+=( const FColor& other );
		FColor operator-=( const FColor& other );
		FColor operator*=( const FColor& other );
		FColor operator/=( const FColor& other );

		FColor operator+=( float value );
		FColor operator-=( float value );
		FColor operator*=( float value );
		FColor operator/=( float value );


		float Magnitude() const;
		FColor Normalize() const;
		float Dot( const FColor& other )const;


		//FVector Test() { return FVector(); }
		
		friend std::ostream& operator<<( std::ostream& stream, const FColor& other );


	};


}
