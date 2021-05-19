#pragma once
#include <iostream>
#include <sfml/Graphics.hpp>
#include "ECS.h"
#include "Components.h"
#include "Systems/RenderingSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Interface/Button.h"
#include "Interface/ButtonMap.h"
#include "Interface/States.h"
#include "Interface/PauseMenu.h"

class Engine
{
public:
	sf::RenderWindow* window;
	ECS::World* world;
	class PauseMenu pauseMenu;

	static Engine& GetInstance();

	void Start(sf::RenderWindow* window);
	void AddSystem(ECS::EntitySystem* newSys);

private:
	bool bQuit;

	Engine();
	
	// Required to prevent the reference from being copied, moved, or assigned
	Engine(Engine& copy); // Hide copy constructor
	Engine(Engine&& move); // Hide move constructor
	Engine& operator=(Engine& copy); // Hide assignement operator
	
	~Engine();

	void Update();
	void ShowPauseMenu();
};

