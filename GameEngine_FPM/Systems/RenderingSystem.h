#pragma once
#include "../Engine.h"
class RenderingSystem : public ECS::EntitySystem
{
public:
	RenderingSystem();

	void tick(ECS::World* world, float deltaTime) override;

	~RenderingSystem();

private:
	std::unordered_map<std::string, sf::Texture*> textureMap;

	sf::Texture* LoadTexture(std::string texture);
};

