#include "MainCamera.h"

MainCamera::MainCamera() = default;

MainCamera::MainCamera(sf::Vector2f pivot)
{
	cameraView.setCenter(pivot);
}

void MainCamera::Update(ECS::World* world, float deltaTime, sf::RenderWindow* window)
{
	float _cameraMoveSpeed = 0.1f;

	sf::Vector2f _windowSize(window->getSize().x, window->getSize().y);
	cameraView.setSize(_windowSize);

	// Camera Moving Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		cameraView.move(-_cameraMoveSpeed * deltaTime, 0);
	}

	// Camera Moving Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		cameraView.move(_cameraMoveSpeed * deltaTime, 0);
	}

	// Camera Moving Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		cameraView.move(0, -_cameraMoveSpeed * deltaTime);
	}

	// Camera Moving Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		cameraView.move(0, _cameraMoveSpeed * deltaTime);
	}

	window->setView(cameraView);
}

MainCamera::~MainCamera() = default;