#include "RenderingSystem.h"

RenderingSystem::RenderingSystem() = default;


void RenderingSystem::tick(ECS::World * world, float deltaTime)
{
	if (States::GetPausedState() == false)
	{
		// Clear before drawing all textures
		Engine::GetInstance().window->clear();

		// This is a lambda function where we pass a anonymous function to another function ('each' in this case)
		// We are passing the entity and components by reference with no return type (void)
		world->each<struct Transform, struct Sprite2D>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<Sprite2D> sprite) -> void
			{
				// This is where we implement the anonymous function
				// Check if an entity has their texture loaded first
				if (textureMap.count(sprite->texture) < 1)
				{
					textureMap[sprite->texture] = LoadTexture(sprite->texture);
				}

				// If no texture is found, then add a texture to the map
				if (sprite->picture.getTexture() == nullptr)
				{
					sprite->picture.setTexture(*textureMap[sprite->texture]);
					sprite->width = (int)std::floor(sprite->picture.getGlobalBounds().width);
					sprite->height = (int)std::floor(sprite->picture.getGlobalBounds().height);
				}

				// Update and draw to the screen
				sprite->picture.setPosition(transform->xPos, transform->yPos);

				Engine::GetInstance().window->draw(sprite->picture);
			});

		world->each<struct TileMap>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<TileMap> tileMap) -> void
			{
				// Loops through each tile and render onto the engines window instance
				// Note that this is looping through a vector which stores a vector which stores the tile value
				for (auto& x : tileMap->map)
				{
					for (auto& y : x)
					{
						for (auto& z : y)
						{
							if (z != nullptr)
							{
								sf::RenderWindow* winRef = Engine::GetInstance().window;
								winRef->draw(z->shape);

								if (z->GetCollision() == true)
								{
									tileMap->collisionBox.setPosition(z->GetPosition());
									winRef->draw(tileMap->collisionBox);
								}
							}
						}
					}
				}
			});

		// Display updates
		Engine::GetInstance().window->display();
	}
}

RenderingSystem::~RenderingSystem() = default;

sf::Texture* RenderingSystem::LoadTexture(std::string texturePath)
{
	sf::Texture* _texture = new sf::Texture();

	if (_texture->loadFromFile(texturePath) == false)
	{
		std::cerr << "Error: Unable to load image " << texturePath << ".\nIs this image in the correct directory?" << std::endl;

		system("pause");
		exit(EXIT_FAILURE);
	}

	return _texture;
}
