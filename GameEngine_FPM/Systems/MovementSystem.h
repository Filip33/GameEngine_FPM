#pragma once
#include "../Engine.h"
class MovementSystem : public ECS::EntitySystem
{
public:
	MovementSystem();

	void tick(ECS::World* world, float deltaTime) override;

	~MovementSystem();
};

