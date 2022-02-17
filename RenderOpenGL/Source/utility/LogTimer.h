#pragma once
#include <chrono>

#include <vector>

#include "File/Logger.h"


#ifdef PROFILE
struct ProfileResults
{
	/*Name of the function, passed in via the timer.*/
	const char* Name;

	/*Time in millisecond*/
	float Time;
};
#define  SCOPED_TIMER(name) UTimerLog timer##__LINE__(name,  [&] ( ProfileResults profileResult ) { EProfileDebugger::AddTimer( profileResult ); } )
#else
#define SCOPED_TIMER(name)
#endif




class FScopedProfiler
{
	
};
class FScopedTimer
{
public:

#ifdef PROFILE
	std::chrono::time_point<std::chrono::steady_clock> Start, End;
	std::chrono::duration <float >Duration;
	std::string FunctionName;
#else
#endif
public:
#ifdef PROFILE
	FScopedTimer(std::string functionName) :Duration(), FunctionName(std::move(functionName))
	{
		Start = std::chrono::high_resolution_clock::now();
		KREngine::Logger::Verbose("%s : Function Started... :", FunctionName.c_str());
	}
	~FScopedTimer()
	{
		End = std::chrono::high_resolution_clock::now();
		const long long start_time = std::chrono::time_point_cast<std::chrono::microseconds>(Start).time_since_epoch().count();
		const long long end_time = std::chrono::time_point_cast<std::chrono::microseconds>(End).time_since_epoch().count();
		const float duration = (end_time - start_time) * 0.001f;
		KREngine::Logger::Verbose("%s : Function took : %f MS", FunctionName.c_str(), duration);
		
		//float MS = duration * 1000.0f;
		//std::cout << FunctionName << " Took :" << MS << " MS" << std::endl;
	}
#else
	explicit FScopedTimer(const std::string& functionName = "")
	{
	}
	~FScopedTimer()
	{
	}
#endif
};

template<typename  Func>
class UTimerLog
{
#ifdef PROFILE
	std::chrono::time_point<std::chrono::steady_clock> Start, End;
	std::chrono::duration <float >Duration;
	const char* FunctionName ;
	Func Function;

#else
#endif
public:
#ifdef PROFILE
	explicit UTimerLog(const char* functionName, Func&& functionPtr):Duration(), FunctionName(functionName),Function(functionPtr)
	{
		Start = std::chrono::high_resolution_clock::now();
	}
	~UTimerLog()
	{
		End = std::chrono::high_resolution_clock::now();
		const long long start_time = std::chrono::time_point_cast<std::chrono::microseconds>( Start ).time_since_epoch().count();
		const long long end_time = std::chrono::time_point_cast<std::chrono::microseconds>( End ).time_since_epoch().count();
		const float duration = ( end_time - start_time ) * 0.001f;
		Function( { FunctionName, duration } );

		//float MS = duration * 1000.0f;
		//std::cout << FunctionName << " Took :" << MS << " MS" << std::endl;
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


/*Singleton class which records all the profile timers.*/
class EProfileDebugger
{
public:

	void Init();
	void Run();
	void Stop();
	void GUIRun();

	static EProfileDebugger& Instance()
	{
		static EProfileDebugger instance;
		return instance;
	}

private:
	EProfileDebugger() = default;
#ifdef PROFILE
public:
	void static AddTimer( ProfileResults Result );
private:
	std::vector<ProfileResults> TimerProfileResults;
#endif

public:

};


