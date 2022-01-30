#pragma once
namespace KREngine
{
	class FGame
	{
	public:
		~FGame() = default;
		FGame() = default;
		virtual void Init() = 0;
		virtual void Run() = 0;
		virtual void Stop() = 0;

		friend class FApplication;
	};


	
}
