#pragma once

#include "Game.h"


namespace KREngine
{
	class TestGame : public FGame
	{
	public:
		TestGame() ;
		virtual void Init() override;
		virtual void Run() override;
		virtual void Stop() override;

		void Test() {};
	};


}
