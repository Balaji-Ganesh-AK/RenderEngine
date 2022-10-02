#pragma once


namespace KREngine
{
	class Time
	{
	public:
		static Time& GetInstance()
		{
			static Time instance;
			return instance;
		}
		static float GetTimeInMS()
		{
			return GetInstance().GetDeltaTimeInternal();
		};
		static float GetDeltaTime()
		{
		
			return GetInstance().DeltaSeconds;
		};

		
	private:
		float GetDeltaTimeInternal();
		float DeltaSeconds;
		Time(){};
	};
}
