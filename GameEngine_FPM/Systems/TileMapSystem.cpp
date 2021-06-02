#include "TileMapSystem.h"

TileMapSystem::TileMapSystem() = default;

void TileMapSystem::tick(ECS::World* world, float deltaTime)
{
	Engine::GetInstance().world->each<TileMap>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<TileMap> tileMap)->void
		{
			if (States::GetPausedState() == false)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
				{
					AddTileOnClick(true, tileMap);
					std::cout << entity->getEntityId() << " is the entity id (With collision)" << std::endl;
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) == true)
				{
					AddTileOnClick(false, tileMap);
					std::cout << entity->getEntityId() << " is the entity id (Without collision)" << std::endl;
				}
			}
			if (ButtonMap::GetMap()["SAVE"]->bClicked == true)
			{
				tileMap->SaveTileMap("TileTest.txt");
				std::cout << "Saved" << std::endl;
				ButtonMap::GetMap()["SAVE"]->bClicked = false;
			}
			if (ButtonMap::GetMap()["LOAD"]->bClicked == true)
			{
				tileMap->LoadTileMap("TileTest.txt");
				std::cout << "Loaded" << std::endl;
				ButtonMap::GetMap()["LOAD"]->bClicked = false;
			}
		});
}

void TileMapSystem::AddTileOnClick(bool bHasCollision, ECS::ComponentHandle<struct TileMap> tileMap)
{
	/*
		Reference for window pointer that is used below to determine active cursor position for adding tiles
	*/
	sf::RenderWindow* _winRef = Engine::GetInstance().window;
	sf::Vector2f _mousePosView = _winRef->mapPixelToCoords(sf::Mouse::getPosition(*_winRef));
	sf::Vector2i _mousePosGrid(
		static_cast<int>(_mousePosView.x / tileMap->gridSizeF),
		static_cast<int>(_mousePosView.y / tileMap->gridSizeF)
	);

	tileMap->AddTile(_mousePosGrid.x, _mousePosGrid.y, 0, bHasCollision);
}

TileMapSystem::~TileMapSystem() = default;