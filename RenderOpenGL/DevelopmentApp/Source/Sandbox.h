#pragma once

#include "GameManager.h"
#include "Systems/SceneManagement/LevelSystem.h"


namespace KREngine
{
	class FEntity;

	class TestGame : public FApplication
	{
	public:
		TestGame() ;
		void Test() {}
		~TestGame() override {}
		
	private:

	};

	class LevelOne : public FLevel
	{
	public:
		LevelOne(const std::string& Name);
		void Init() override;
		void Run() override;
		void End() override;
		void Test() {}
		~LevelOne() override {}
		void GUIInit() override;
		void GUIRun() override;
		void GUIEnd() override;

	private:

		FEntity* entity{};
		FEntity* entity1{};
		FEntity* CameraEntity{};
	};
	class LevelTwo : public FLevel
	{
	public:
		LevelTwo(const std::string& Name);
		void Init() override;
		void Run() override;
		void End() override;
		void Test() {}
		~LevelTwo() override {}
		void GUIInit() override;
		void GUIRun() override;
		void GUIEnd() override;

	private:

		FEntity* entity{};
		FEntity* entity1{};
		FEntity* CameraEntity{};
	};
}
