
#include "FScopedLock.h"

#include <cassert>
#include <Windows.h>

namespace KREngine
{
	FScopedMutex::FScopedMutex(bool bTakeOwnership, const char* name)
	{
#ifdef _WIN32
		MutexLock = CreateMutex(nullptr, (bool)bTakeOwnership, LPCWSTR(name));
#else
		/*Implement other platform here*/
#endif

	}

	FScopedMutex::~FScopedMutex()
	{
		BOOL result = CloseHandle(MutexLock);
		assert(result == TRUE);
	}
}
