#pragma once
#include "Systems/SceneManagement/LevelSystem.h"


class FBoidSystem;

struct vec2_t
{
	float x = 0.0f, y = 0.0f;

	float Magnitude() const
	{
		return sqrt(x * x + y * y);
	}
	vec2_t Normalize() const
	{
		float temp = Magnitude();
		return vec2_t(x / temp, y / temp);
	}
	void SetMagnitue(float new_mag)
	{
		const float mag = Magnitude();
		x = x * new_mag / mag;
		y = y * new_mag / mag;
	}

	vec2_t Subtract(const vec2_t& other) const
	{
		return vec2_t(x - other.x, y - other.y);
	}

	vec2_t& operator-(const vec2_t& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}


	float Distance(const vec2_t& other) const
	{
		const float diffy = y - other.y;
		const float diffx = x - other.x;
		return sqrt((diffy * diffy) + (diffx * diffx));
	}

	vec2_t Multiply(float value) const
	{
		return vec2_t(x * value, y * value);
	}

	vec2_t& Add(const vec2_t& other)
	{
		x = x + other.x;
		y = y + other.y;
		return *this;
	}


};

struct game_object_t
{
	vec2_t position;
	vec2_t velocity;
};



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
	KREngine::FEntity* entity2{};
	KREngine::FEntity* entity3{};
	KREngine::FEntity* CameraEntity{};
};

class LevelTwo : public KREngine::FLevel
{

public:
	LevelTwo(const std::string& Name);
	void PreInit() override;
	void Init() override;
	void Run() override;
	void End() override;

	~LevelTwo() override {}
	void GUIInit() override;
	void GUIRun() override;
	void GUIEnd() override;
	//game_object_t a;
	//game_object_t b;
	game_object_t a;
	game_object_t b;
	game_object_t c;
	void MoveTo(const game_object_t* Target, const game_object_t* Follower);

	void Test();

private:

	void LineCircle();
	std::shared_ptr<FBoidSystem> BoidSystem;

	KREngine::FEntity* Ray;
	KREngine::FEntity* Ray1;
	KREngine::FEntity* entity{};
	KREngine::FEntity* entity1{};
	KREngine::FEntity* entity2{};
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

