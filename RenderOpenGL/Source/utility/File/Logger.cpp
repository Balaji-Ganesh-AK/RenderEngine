
#include "Logger.h"

#include <cstdarg>

#include "utility/Pch.h"


namespace KREngine
{
#define COLOR_VERBOSE ( FOREGROUND_INTENSITY )
#define COLOR_ERROR ( FOREGROUND_RED | FOREGROUND_INTENSITY )
#define COLOR_FATAL ( FOREGROUND_RED | FOREGROUND_INTENSITY )
#define COLOR_WARNING ( FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY )
#define COLOR_LOADING ( FOREGROUND_GREEN | FOREGROUND_INTENSITY )

	
	void Logger::Verbose(const char* format, ...)
	{
#ifdef LOGGING
		Get().UpdateTextColor(COLOR_VERBOSE);
		va_list Arguments;
		va_start( Arguments, format );
		Get().Print( format, Arguments );
		va_end( Arguments );
#endif


	}


	/*void Logger::Warning(const char* format, ...)
	{
#ifdef LOGGING
		Get().UpdateTextColor(COLOR_WARNING);
		va_list Arguments;
		va_start(Arguments, format);
		Get().Print(format, Arguments);
		va_end(Arguments);
#endif


	}*/


	void Logger::Loader(const char* format, ...)
	{
#ifdef LOGGING
		Get().UpdateTextColor(COLOR_LOADING);
		va_list Arguments;
		va_start(Arguments, format);
		Get().PrintSameLine(format, Arguments);
		va_end(Arguments);
#endif


	}

	void Logger::Error(const char* format, ...)
	{
#ifdef LOGGING
		Get().UpdateTextColor( COLOR_ERROR );
		va_list Arguments;
		va_start( Arguments, format );
		Get().Print( format, Arguments );
		va_end( Arguments );
#endif
	}

	void Logger::Fatal(const char* format, ...)
	{
#ifdef LOGGING
		Get().UpdateTextColor( COLOR_FATAL );
		va_list Arguments;
		va_start( Arguments, format );
		Get().Print( format, Arguments );
		va_end( Arguments );
		throw std::runtime_error("Fatal Error!");
#endif
	}

	Logger::~Logger()
	{
		
	}

	const std::string Logger::GetTimeStamp(const std::time_t* TimeStamp)
	{
		std::time_t Time = std::time( const_cast< std::time_t* >( TimeStamp ) );
		std::tm LocalTime;
		localtime_s( &LocalTime, &Time );

		char Buffer [32] = { 0 };
		strftime( Buffer, 32, "%H.%M.%S", &LocalTime );

		return std::string( Buffer ) + ": ";
	}

	Logger& Logger::Get()
	{
		static Logger Instance;
		return Instance;
	}

	void Logger::Print(const char* format, va_list arguments) 
	{
		std::vector<char> buffer( BufferSize );
		std::string output = GetTimeStamp();

		if(true)
		{
			const int written = vsnprintf_s( buffer.data(), buffer.size(), _TRUNCATE, format, arguments );

			if( written  > 0 )
			{
				buffer.resize( written );
			}

			const std::string line = std::string( buffer.begin(), buffer.end() );
			output += line;


			output +="\n";
			fprintf( stdout, "%s", output.c_str() );
		}
	}

	void Logger::PrintSameLine(const char* format, va_list arguments)
	{
		std::vector<char> buffer(BufferSize);
		std::string output = GetTimeStamp();

		if (true)
		{
			const int written = vsnprintf_s(buffer.data(), buffer.size(), _TRUNCATE, format, arguments);

			if (written > 0)
			{
				buffer.resize(written);
			}

			const std::string line = std::string(buffer.begin(), buffer.end());
			output += line;


		//	output += "\n";
			output = "\r" + output;
			fprintf(stdout, "%s", output.c_str());
		}
	}

	void Logger::UpdateTextColor(WORD newColor)
	{
		static WORD old_color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

		if ( newColor != old_color )
		{
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), newColor );
			old_color = newColor;
		}
	}
}

	

