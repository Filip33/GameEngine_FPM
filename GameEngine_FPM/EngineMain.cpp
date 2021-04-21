#include <sfml/Graphics.hpp>
#include "Engine.h"

int main(int argc, char* args[])
{
	// Declare and get instance singleton
	Engine& GameEngine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "MyEngine");

	// Pass window reference to Engine to start
	GameEngine.Start(&window);

	return 0;
}