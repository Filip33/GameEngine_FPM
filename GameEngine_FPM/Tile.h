#pragma once
#include <iostream>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Tile
{
public:
	bool bColliding;
	sf::RectangleShape shape;

	Tile();
	Tile(float xPos, float yPos, float gridSizeF, bool bColliding);

	void Render(sf::RenderTarget& target);

	const bool& GetCollision()const;

	const sf::Vector2f& GetPosition()const;

	std::string ToString();

	~Tile();
};