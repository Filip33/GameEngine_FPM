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
	mainCam = MainCamera(sf::Vector2f(
		this->window->getSize().x / 2,
		this->window->getSize().y / 2));
	pauseMenu = PauseMenu(this->window);

	while (window->isOpen() == true)
	{
		Update();
	}
}

void Engine::AddSystem(ECS::EntitySystem* newSys)
{
	world->registerSystem(newSys);
	world->enableSystem(newSys);
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

		pauseMenu.Update(_event, 10.0f, window);
	}

	world->tick(10.0f);
	mainCam.Update(world, 10.0f, window);

	if (States::GetPausedState() == true)
	{
		ShowPauseMenu();
	}
}

void Engine::ShowPauseMenu()
{
	pauseMenu.Render(window, 10.0f, mainCam.cameraView.getCenter());
}

Engine::~Engine() = default;