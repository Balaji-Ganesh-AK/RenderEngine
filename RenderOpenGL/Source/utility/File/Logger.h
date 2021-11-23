#pragma once

#include "utility/Pch.h"

#include "ctime"
#include <windows.h>



namespace KREngine
{
	class Logger
	{
	public:
	

		static void Verbose( const char* format, ... );
		static void Error( const char* format, ... );
		static void Fatal( const char* format, ... );
		~Logger();
	private:

		static Logger& Get();
		Logger()
		{
		};
		const std::string GetTimeStamp(const std::time_t* TimeStamp = nullptr );
		
		
		void Print(const char* format, va_list arguments);

		void UpdateTextColor( WORD newColor );
		

		uint16 BufferSize = 8192;
		
		//std::ofstream LogFile;
		
	};
}
