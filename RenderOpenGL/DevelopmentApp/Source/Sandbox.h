#pragma once

#include "GameManager.h"


namespace KREngine
{
	class FEntity;

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
		FEntity* entity1{};
		FEntity* CameraEntity{};
	};


}
