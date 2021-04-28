#include <sfml/Graphics.hpp>
#include "Engine.h"

int main(int argc, char* args[])
{
	// Declare and get instance singleton
	Engine& GameEngine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "MyEngine");

	// Create the world for attaching entities and systems to
	GameEngine.world = ECS::World::createWorld();

	// Create entities here
	ECS::Entity* stickFigure;

	// Add systems to the engine here
	GameEngine.AddSystem(new RenderingSystem());

	// Create and assign 250 entities to the world
	for (int x = 0; x < 25; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			stickFigure = GameEngine.world->create();

			// Assign components to each entity after creation
			stickFigure->assign<Transform>(x * 25, y * 32);
			stickFigure->assign<Sprite2D>("../Debug/Pics/hero.png");

			std::cout << stickFigure->getEntityId() << " is the entity ID." << std::endl;
		}
	}

	// Pass window reference to Engine to start
	GameEngine.Start(&window);

	return 0;
}