#pragma once


namespace KREngine
{

	
	class INonCopyableClass
	{
	private:
	
		INonCopyableClass( const INonCopyableClass& );
		const INonCopyableClass& operator=( const INonCopyableClass& );
	protected:
		INonCopyableClass() = default;
		~INonCopyableClass() = default;
	};

}
