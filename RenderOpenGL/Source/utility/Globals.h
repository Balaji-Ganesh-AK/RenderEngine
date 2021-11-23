#pragma once

#include <iostream>
//*** Local debugging code, should not be in depo, if you see this code please remove it.*/
struct AllocationTracker
{
	uint32_t TotalAllocation = 0;
	uint32_t TotalFreed = 0;
	uint32_t CurrentUsage() { return TotalAllocation - TotalFreed; }
};

static AllocationTracker MemoryTracker;
//__forceinline  void* operator new( size_t size )
//{
//	MemoryTracker.TotalAllocation += size;
//
//	return malloc( size );
//}
//
//__forceinline void operator delete( void* memory, size_t size )
//{
//	MemoryTracker.TotalFreed += size;
//
//	return free( memory );
//}


namespace  KREngine
{

	static void PrintCurrentMemoryUsage( std::string_view Message = "")
	{
		//Logger::Verbose( "Memory Usage: %d", MemoryTracker.CurrentUsage() );
		std::cout << "Memory Usage:" << Message << MemoryTracker.CurrentUsage() << std::endl;
	}
}

/**End of the debug code*/