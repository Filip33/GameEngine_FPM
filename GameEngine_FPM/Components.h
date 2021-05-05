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

struct Animator
{
	ECS_DECLARE_TYPE;
public:
	int spriteWidth, spriteHeight;
	int currentColumn, currentRow;
	int totalColumns, totalRows;
	float currentTime, nextFrameTime;
	bool bFacingRight;

	Animator(int newWidth, int newHeight, float timeBetweenFrames, int columns, int rows)
	{
		spriteWidth = newWidth;
		spriteHeight = newHeight;

		currentColumn = 0;
		currentRow = 0;

		totalColumns = columns;
		totalRows = rows;

		nextFrameTime = timeBetweenFrames;
		currentTime = 0;

		bFacingRight = true;
	}
};

struct InputController
{
	ECS_DECLARE_TYPE;
public:
	bool bInputActive;
	bool wKey;
	bool sKey;
	bool aKey;
	bool dKey;

	InputController()
	{
		bInputActive = true;
		wKey = false;
		sKey = false;
		aKey = false;
		dKey = false;
	}
}

ECS_DEFINE_TYPE(Transform);
ECS_DEFINE_TYPE(Sprite2D);
ECS_DEFINE_TYPE(Animator);
ECS_DEFINE_TYPE(InputController);