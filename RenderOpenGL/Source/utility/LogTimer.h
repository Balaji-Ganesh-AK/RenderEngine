#pragma once
#include <chrono>
#include "Pch.h"

class UTimerLog
{
#ifdef PROFILE
	std::chrono::time_point<std::chrono::steady_clock> Start, End;
	std::chrono::duration <float >Duration;
	std::string FunctionName = "Timer Took ";
#else
#endif
public:
#ifdef PROFILE
	explicit UTimerLog(const std::string& functionName = ""): Duration()
	{
		if (!functionName.empty())
		{
			FunctionName = functionName;
		}
		Start = std::chrono::high_resolution_clock::now();
	}
	~UTimerLog()
	{
		End = std::chrono::high_resolution_clock::now();
		Duration = End - Start;
		float MS = Duration.count() * 1000.0f;
		std::cout << FunctionName << " Took :" << MS << " MS" << std::endl;
	}
#else
	explicit UTimerLog( const std::string& functionName = "" )
	{
	}
	~UTimerLog()
	{
	}
#endif

};
