#include <sfml/Graphics.hpp>
#include "../GameEngine_FPM/Engine.h"

int main(int argc, char* args[])
{
	// Declare and get instance singleton
	Engine& GameEngine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "MyEngine");

	// Create the world for attaching entities and systems to
	GameEngine.world = ECS::World::createWorld();

	// Create entities here
	ECS::Entity* background;
	ECS::Entity* stickFigure;
	ECS::Entity* tux;

	// Add systems to the engine here
	GameEngine.AddSystem(new RenderingSystem());
	GameEngine.AddSystem(new AnimationSystem());
	GameEngine.AddSystem(new InputSystem(&window));
	GameEngine.AddSystem(new MovementSystem());

	// Create and assign entities to the world
	background = GameEngine.world->create();
	stickFigure = GameEngine.world->create();
	tux = GameEngine.world->create();

	// Assign components to entities after creation
	background->assign<Transform>(0, 0);
	background->assign<Sprite2D>("../Debug/Pics/bg.jpg");

	stickFigure->assign<Transform>(300, 300, 0.2f, 0.2f);
	stickFigure->assign<Sprite2D>("../Debug/Pics/hero.png");
	stickFigure->assign<Animator>(32, 32, 200.0f, 4, 1);

	tux->assign<Transform>(200, 200, 0.3f, 0.3f);
	tux->assign<Sprite2D>("../Debug/Pics/tux_from_linux.png");
	tux->assign<Animator>(56, 72, 2000.0f, 3, 9);
	tux->assign<InputController>();
	tux->get<Animator>()->currentRow = 0; // Idle row
	

	std::cout << background->getEntityId() << " is the entity ID." << std::endl;
	std::cout << stickFigure->getEntityId() << " is the entity ID." << std::endl;
	std::cout << tux->getEntityId() << " is the entity ID." << std::endl;

	// Pass window reference to Engine to start
	GameEngine.Start(&window);

	return 0;
}