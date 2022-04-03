#pragma once



#include <string>

#include "ctime"
#include <windows.h>

#include "Defines.h"



namespace KREngine
{
	class Logger
	{
	public:


		static void Verbose(const char* format, ...);
		static void Loader(const char* format, ...);
		static void Error(const char* format, ...);
		static void Warning(const char* format, ...);
		static void Fatal(const char* format, ...);
		~Logger();
	private:

		static Logger& Get();
		Logger()
		{
		};
		const std::string GetTimeStamp(const std::time_t* TimeStamp = nullptr);


		void Print(const char* format, va_list arguments);
		void PrintSameLine(const char* format, va_list arguments);

		void UpdateTextColor(WORD newColor);


		uint16 BufferSize = 8192;

		//std::ofstream LogFile;

	};




}
