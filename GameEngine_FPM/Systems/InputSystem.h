#pragma once
#include "../Engine.h"
class InputSystem : public ECS::EntitySystem
{
public:
	InputSystem(sf::RenderWindow* window);

	void tick(ECS::World* world, float deltaTime) override;
	void GetKeyEvents(ECS::World* world);

	~InputSystem();

private:
	sf::RenderWindow* window;
};

