#pragma once
#include "Systems/SceneManagement/LevelSystem.h"




	class LevelOne : public KREngine::FLevel
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

		KREngine::FEntity* entity{};
		KREngine::FEntity* entity1{};
		KREngine::FEntity* CameraEntity{};
	};

	class LevelTwo : public KREngine::FLevel
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

		KREngine::FEntity* entity{};
		KREngine::FEntity* entity1{};
		KREngine::FEntity* CameraEntity{};
	};

class InstanceStaticMeshTestMap :public KREngine::FLevel
{
public:
	InstanceStaticMeshTestMap(const std::string& Name);
	~InstanceStaticMeshTestMap() override;
	void Init() override;
	void Run() override;
	void End() override;
	void GUIInit() override;
	void GUIRun() override;
	void GUIEnd() override;
};

