#pragma once
#include <iostream>
#include <sfml/Graphics.hpp>

class Engine
{
public:
	sf::RenderWindow* window;

	static Engine& GetInstance();

	void Start(sf::RenderWindow* window);

private:
	bool bQuit;

	Engine();
	
	// Required to prevent the reference from being copied, moved, or assigned
	Engine(Engine& copy); // Hide copy constructor
	Engine(Engine&& move); // Hide move constructor
	Engine& operator=(Engine& copy); // Hide assignement operator
	
	~Engine();

	void Update();
};

