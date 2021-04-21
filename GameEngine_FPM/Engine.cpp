#include "Engine.h"

Engine& Engine::GetInstance()
{
	// TODO: insert return statement here
	static Engine _instance;

	return _instance;
}

void Engine::Start(sf::RenderWindow* window)
{
	bQuit = false;
	this->window = window;

	while (window->isOpen() == true)
	{
		Update();
	}
}

Engine::Engine() = default;

void Engine::Update()
{
	sf::Event _event;

	while (window->pollEvent(_event) == true)
	{
		if (_event.type == sf::Event::Closed)
		{
			window->close();
		}
	}
}

Engine::~Engine() = default;