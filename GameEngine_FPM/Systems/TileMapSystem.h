#pragma once
#include "..\Engine.h"
#include "..\Interface\Button.h"
class TileMapSystem : public ECS::EntitySystem
{
public:
	TileMapSystem();

	void tick(ECS::World* world, float deltaTime) override;
	void AddTileOnClick(bool bHasCollision, ECS::ComponentHandle<struct TileMap> tileMap);

	~TileMapSystem();
};

