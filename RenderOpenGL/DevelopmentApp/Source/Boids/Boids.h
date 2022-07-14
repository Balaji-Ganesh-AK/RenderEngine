#pragma once
#include "Entity/Entity.h"

using namespace KREngine;


struct FBoidComponent
{
	bool bIsLeader = false;

	FVector velocity = FVector::Random(0.0f, 0.1f);
	//FVector velocity  {0,0,0.01f};
	FVector acceleration;
};

class FBoidSystem : public FSystem
{
public:
	FBoidSystem() = default;
	void Init() override;
	void Run()  override;
	void End() override;
	~FBoidSystem();

#ifdef GUI
	void GUIInit() override;
	void GUIRun() override;
	void GUIEnd() override;
#endif

	float speed=0.5f;
	float Preception = 1000.0f;
	float Preception_Cohesion = 100.0f;
	float Preception_Sep = 100.0f;
private:

	FVector Align(FEntityHandle boid);
	FVector Cohesion(FEntityHandle boid);
	FVector Separation(FEntityHandle i_boid);
	FVector Max{ 50,50,50 };
	FVector Min{ -50,-50,-50 };
	void EdgeLimit(FVector& pos);
};