#pragma once



namespace KREngine
{
	class FScopedMutex
	{
		public:
			FScopedMutex(bool bTakeOwnership = false, const char* name = nullptr);
			~FScopedMutex();
		private:

			void* MutexLock;

	};
}
