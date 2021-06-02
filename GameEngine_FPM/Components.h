#pragma once
#include "Engine.h"
#include "Tile.h"
#include <iostream>
#include <fstream>

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

struct Camera
{
	ECS_DECLARE_TYPE;
public:
	sf::View cameraView;

	Camera(sf::Vector2f pivot)
	{
		cameraView.setCenter(pivot);
	}
};

struct Tag
{
	ECS_DECLARE_TYPE;
public:
	std::vector<std::string> tagNames;

	Tag() = default;

	void AddTag(std::string tag)
	{
		tagNames.push_back(tag);
	}
};

struct TileMap
{
	ECS_DECLARE_TYPE;
public:
	float gridSizeF; // This is the size of the world grid
	uint32_t gridSizeU;
	uint32_t layers;
	sf::Vector2u maxSize;
	sf::RectangleShape collisionBox;

	/*
		Map structure
		1 - Column of Vectors
		2 - Row of Vectors
		3 - Collection of Tile Pointers
	*/
	// std::vector is the Java equivalent of an Array List
	std::vector < std::vector < std::vector < Tile* >>> map;

	TileMap()
	{
		gridSizeF = 50.0f;

		// Return a value of new type, convert float to unsigned int
		this->gridSizeU = static_cast <uint32_t>(gridSizeF);

		// Number of Tiles (Size of Tiles given by gridSize)
		maxSize.x = 20;
		maxSize.y = 20;

		layers = 1;

		map.resize(maxSize.x);

		for (size_t x = 0; x < maxSize.x; x++)
		{
			map.push_back(std::vector < std::vector < Tile* >>());

			for (size_t y = 0; y < maxSize.y; y++)
			{
				map.at(x).resize(maxSize.y);
				map[x].push_back(std::vector < Tile* >());

				for (size_t z = 0; z < layers; z++)
				{
					map.at(x).at(y).resize(layers);
					map[x][y].push_back(nullptr);
				}
			}
		}

		collisionBox.setSize(sf::Vector2f(gridSizeF, gridSizeF));
		collisionBox.setFillColor(sf::Color::Blue);
		collisionBox.setOutlineColor(sf::Color::Green);
		collisionBox.setOutlineThickness(-1.0f);
	}

	void AddTile(const int x, const int y, const int z, bool bHasCollision)
	{
		if (x < maxSize.x && x >= 0 &&
			y < maxSize.y && y >= 0 &&
			z < layers && z >= 0)
		{
			if (map[x][y][z] == nullptr)
			{
				map[x][y][z] = new Tile(x, y, gridSizeF, bHasCollision);

				std::cout << "Added Tile" << std::endl;
			}
		}
	}

	void Clear()
	{
		for (size_t x = 0; x < maxSize.x; x++)
		{
			for (size_t y = 0; y < maxSize.y; y++)
			{
				for (size_t z = 0; z < layers; z++)
				{
					delete map[x][y][z];
				}
				map[x][y].clear();
			}
			map[x].clear();
		}
		map.clear();
	}

	void SaveTileMap(std::string filename)
	{
		std::ofstream saveFile;

		saveFile.open(filename);

		if (saveFile.is_open() == true)
		{
			saveFile << maxSize.x << " " << maxSize.y << "\n"
				<< gridSizeF << "\n"
				<< layers << "\n";

			for (size_t x = 0; x < maxSize.x; x++)
			{
				for (size_t y = 0; y < maxSize.y; y++)
				{
					for (size_t z = 0; z < layers; z++)
					{
						if (map[x][y][z] != nullptr)
						{
							saveFile << x << " " << y << " " << z << " "
								<< map[x][y][z]->ToString() << " \n";
						}
					}

				}

			}
		}
		else
		{
			std::cerr << "Tile Map could not be saved to File " << filename << "\n";
		}

		saveFile.close();
	}

	void LoadTileMap(std::string filename)
	{
		std::ifstream loadFile;

		loadFile.open(filename);

		if (loadFile.is_open() == true)
		{
			bool _bColliding = false;

			loadFile >> maxSize.x >> maxSize.y >> gridSizeF >> layers;

			Clear();

			map.resize(maxSize.x, std::vector < std::vector < Tile* >>());

			for (size_t x = 0; x < maxSize.x; x++)
			{
				for (size_t y = 0; y < maxSize.y; y++)
				{
					map[x].resize(maxSize.y, std::vector < Tile* >());

					for (size_t z = 0; z < layers; z++)
					{
						map[x][y].resize(layers, nullptr);
					}

				}

			}

			while (loadFile >> maxSize.x >> maxSize.y >> layers >> _bColliding)
			{
				std::cout << maxSize.x << ", " << maxSize.y << ", " << layers << "\n";

				map[maxSize.x][maxSize.y][layers] = new Tile(maxSize.x, maxSize.y, gridSizeF, _bColliding);
			}
		}
		else
		{
			std::cerr << "Couldn't not load the Tile Map " << filename << "\n";
		}

		loadFile.close();
	}

	~TileMap()
	{
		Clear();
	}
};

ECS_DEFINE_TYPE(Transform);
ECS_DEFINE_TYPE(Sprite2D);
ECS_DEFINE_TYPE(Animator);
ECS_DEFINE_TYPE(InputController);
ECS_DEFINE_TYPE(BoxCollider);
ECS_DEFINE_TYPE(Camera);
ECS_DEFINE_TYPE(Tag);
ECS_DEFINE_TYPE(TileMap);