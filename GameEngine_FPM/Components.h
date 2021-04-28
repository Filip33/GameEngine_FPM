#pragma once
#include "Engine.h"

struct Transform
{
	ECS_DECLARE_TYPE;
public:
	float xPos;
	float yPos;
	float rotation;

	Transform(float newX, float newY)
		:xPos(newX), yPos(newY)
	{
		this->rotation = 0.0f;
	}
};

struct Sprite2D
{
	ECS_DECLARE_TYPE;
public:
	sf::Sprite picture;
	std::string texture;
	int width;
	int height;

	Sprite2D(std::string filepath)
	{
		this->texture = filepath;
	}
};
ECS_DEFINE_TYPE(Transform);
ECS_DEFINE_TYPE(Sprite2D);