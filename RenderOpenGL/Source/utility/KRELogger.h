#pragma once
#include <iostream>

namespace KREngine
{
	class KRELogger
	{
	public:
		template <typename T>
		static void Warning(T data)
		{
			std::cout << data << std::endl;
		}
		template <typename T>
		static void Log( T data )
		{
			std::cout << data << std::endl;
		}
		template <typename T>
		static void Success( T data )
		{
			std::cout << data << std::endl;
		}
		template <typename T>
		static void Error( T data )
		{
			std::cout << data << std::endl;
		}
	};
}
