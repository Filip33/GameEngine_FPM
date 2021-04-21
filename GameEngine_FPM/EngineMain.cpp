#include <sfml/Graphics.hpp>

int main(int argc, char* args[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "MyEngine");

	// Run the program as long as the window is open
	while (window.isOpen() == true)
	{
		sf::Event _event;

		while (window.pollEvent(_event) == true)
		{
			if (_event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
	}

	return 0;
}

