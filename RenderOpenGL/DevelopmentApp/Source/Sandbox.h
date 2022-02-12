#pragma once

#include "GameManager.h"


namespace KREngine
{
	class TestGame : public FApplication
	{
	public:
		TestGame() ;
		void Init() override;
		void Run() override;
		void End() override;
		void Test() {};
		~TestGame() {};

	private:

		FEntity* entity{};
	};


}
