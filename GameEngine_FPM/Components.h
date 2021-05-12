#pragma once
#include "Engine.h"

struct Transform
{
	ECS_DECLARE_TYPE;
public:
	float xPos, yPos;
	float rotation;
	float xSpeed, ySpeed;
	float xSpeedMod, ySpeedMod;
	bool bColliding;

	Transform(float newX, float newY, float newXSpeed = 0.0f, float newYSpeed = 0.0f)
		:xPos(newX), yPos(newY), xSpeedMod(newXSpeed), ySpeedMod(newYSpeed)
	{
		this->rotation = 0.0f;
		this->xSpeed = 0.0f;
		this->ySpeed = 0.0f;
		this->bColliding = false;
	}

	void UpdateSpeed(float x, float y)
	{
		this->xSpeed = x;
		this->ySpeed = y;
	}

	void Move()	
	{
		if (bColliding == false)
		{
			// Halve the speed when moving diagonally
			if (xSpeed != 0 && ySpeed != 0)
			{
				xSpeed /= 2;
				ySpeed /= 2;
			}

			xPos += xSpeed;
			yPos += ySpeed;
		}
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
};

struct BoxCollider
{
	ECS_DECLARE_TYPE;
public:
	// Round up collision with tiles to avoid getting stuck
	int leftEdge, rightEdge, topEdge, bottomEdge;

	BoxCollider()
	{
		// Set all structure's members to 0
		std::memset(this, '\0', sizeof(BoxCollider));
	}

	void Update(int xSide, int ySide, int width, int height)
	{
		leftEdge = xSide;
		rightEdge = xSide + width;
		topEdge = ySide;
		bottomEdge = ySide + height;
	}
};

ECS_DEFINE_TYPE(Transform);
ECS_DEFINE_TYPE(Sprite2D);
ECS_DEFINE_TYPE(Animator);
ECS_DEFINE_TYPE(InputController);
ECS_DEFINE_TYPE(BoxCollider);