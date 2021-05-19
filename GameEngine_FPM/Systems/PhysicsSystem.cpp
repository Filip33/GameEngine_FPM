#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() = default;

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<struct BoxCollider> touchingBox, ECS::ComponentHandle<struct BoxCollider> touchedBox, float x, float y)
{
	return touchingBox->rightEdge + x > touchedBox->leftEdge &&
		touchedBox->rightEdge > touchingBox->leftEdge + x &&
		touchingBox->bottomEdge + y > touchedBox->topEdge &&
		touchedBox->bottomEdge > touchingBox->topEdge + y;

}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<struct BoxCollider> touchingBox, sf::RectangleShape touchedRectangle, float x, float y)
{
	float _touchedRectLeft = touchedRectangle.getPosition().x;
	float _touchedRectRight = _touchedRectLeft + touchedRectangle.getGlobalBounds().width;
	float _touchedRectTop = touchedRectangle.getPosition().y;
	float _touchedRectBottom = _touchedRectTop + touchedRectangle.getGlobalBounds().height;

	return touchingBox->rightEdge + x > _touchedRectLeft &&
		_touchedRectRight > touchingBox->leftEdge + x &&
		touchingBox->bottomEdge + y > _touchedRectTop &&
		_touchedRectBottom > touchingBox->topEdge + y;
}

// Usable for potential events such as damage etc...
bool PhysicsSystem::IsColliding(ECS::ComponentHandle<struct BoxCollider> touchingBox, sf::RectangleShape touchedRectangle)
{
	float _touchedRectLeft = touchedRectangle.getPosition().x;
	float _touchedRectRight = touchedRectangle.getPosition().x + _touchedRectLeft + touchedRectangle.getGlobalBounds().width;
	float _touchedRectTop = touchedRectangle.getPosition().y;
	float _touchedRectBottom = touchedRectangle.getPosition().y + _touchedRectTop + touchedRectangle.getGlobalBounds().height;

	return touchingBox->rightEdge > _touchedRectLeft &&
		_touchedRectRight > touchingBox->leftEdge &&
		touchingBox->bottomEdge > _touchedRectTop &&
		_touchedRectBottom > touchingBox->topEdge;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<struct BoxCollider> touchingBox, ECS::ComponentHandle<struct BoxCollider> touchedBox)
{
	return touchingBox->rightEdge > touchedBox->leftEdge &&
		touchedBox->rightEdge > touchingBox->leftEdge &&
		touchingBox->bottomEdge > touchedBox->topEdge &&
		touchedBox->bottomEdge > touchingBox->topEdge;
}

void PhysicsSystem::PushEntity(ECS::ComponentHandle<struct Transform> transform, ECS::ComponentHandle<struct BoxCollider> touchingBox, ECS::ComponentHandle<struct BoxCollider> touchedBox)
{
	// Scenario dealing with collision from the right side by accelerating right 
	if (transform->xSpeed > 0 &&
		touchedBox->rightEdge + transform->xSpeed > touchedBox->leftEdge &&
		touchingBox->topEdge < touchedBox->bottomEdge &&
		touchingBox->bottomEdge > touchedBox->topEdge)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the bottom side by accelerating down
	if (transform->ySpeed > 0 &&
		touchedBox->bottomEdge + transform->ySpeed > touchedBox->topEdge &&
		touchingBox->leftEdge < touchedBox->rightEdge &&
		touchingBox->rightEdge > touchedBox->leftEdge)
	{
		transform->ySpeed = 0;
	}

	// Scenario dealing with collision from the left side by accelerating left 
	if (transform->xSpeed < 0 &&
		touchedBox->leftEdge + transform->xSpeed > touchedBox->rightEdge &&
		touchingBox->topEdge < touchedBox->bottomEdge &&
		touchingBox->bottomEdge > touchedBox->topEdge)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the top side by accelerating up
	if (transform->ySpeed < 0 &&
		touchedBox->topEdge + transform->ySpeed > touchedBox->bottomEdge &&
		touchingBox->leftEdge < touchedBox->rightEdge &&
		touchingBox->rightEdge > touchedBox->leftEdge)
	{
		transform->ySpeed = 0;
	}
}

void PhysicsSystem::PushEntity(ECS::ComponentHandle<struct Transform> transform, ECS::ComponentHandle<struct BoxCollider> touchingBox, sf::RectangleShape touchedRectangle)
{
	float _touchedRectLeft = touchedRectangle.getPosition().x;
	float _touchedRectRight = _touchedRectLeft + touchedRectangle.getGlobalBounds().width;
	float _touchedRectTop = touchedRectangle.getPosition().y;
	float _touchedRectBottom = _touchedRectTop + touchedRectangle.getGlobalBounds().height;

	// Scenario dealing with collision from the right side by accelerating right
	if (transform->xSpeed > 0 &&
		touchingBox->rightEdge + transform->xSpeed > _touchedRectLeft &&
		touchingBox->topEdge < _touchedRectBottom &&
		touchingBox->bottomEdge > _touchedRectTop)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the bottom side by accelerating down
	if (transform->ySpeed > 0 &&
		touchingBox->bottomEdge + transform->ySpeed > _touchedRectTop &&
		touchingBox->leftEdge < _touchedRectRight &&
		touchingBox->rightEdge > _touchedRectLeft)
	{
		transform->ySpeed = 0;
	}

	// Scenario dealing with collision from the left side by accelerating left
	if (transform->xSpeed < 0 &&
		touchingBox->leftEdge + transform->xSpeed > _touchedRectRight &&
		touchingBox->topEdge < _touchedRectBottom &&
		touchingBox->bottomEdge > _touchedRectTop)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the top side by accelerating up
	if (transform->ySpeed < 0 &&
		touchingBox->topEdge + transform->ySpeed > _touchedRectBottom &&
		touchingBox->leftEdge < _touchedRectRight &&
		touchingBox->rightEdge > _touchedRectLeft)
	{
		transform->ySpeed = 0;
	}
}

void PhysicsSystem::PushEntity(ECS::Entity * touchingEntity, ECS::Entity * touchedEntity)
{
	float _newTouchingX = touchingEntity->get<struct Transform>()->xPos;
	float _newTouchingY = touchingEntity->get<struct Transform>()->yPos;

	float _newTouchingXSpeed = touchingEntity->get<struct Transform>()->xSpeed;
	float _newTouchingYSpeed = touchingEntity->get<struct Transform>()->ySpeed;

	float _newTouchedX = touchedEntity->get<struct Transform>()->xPos;
	float _newTouchedY = touchedEntity->get<struct Transform>()->yPos;

	// Travelling right, pushing from the left side
	if (_newTouchingXSpeed > 0 && _newTouchingX < _newTouchedX)
	{
		touchedEntity->get<struct Transform>()->xPos++;
	}
	// Travelling left, pushing from the right side
	else if (_newTouchingXSpeed < 0 && _newTouchingX > _newTouchedX)
	{
		touchedEntity->get<struct Transform>()->xPos--;
	}
	// Travelling down, pushing from the top side
	else if (_newTouchingYSpeed > 0 && _newTouchingY < _newTouchedY)
	{
		touchedEntity->get<struct Transform>()->yPos++;
	}
	// Travelling up, pushing from the bottom side
	else if (_newTouchingYSpeed < 0 && _newTouchingY > _newTouchedY)
	{
		touchedEntity->get<struct Transform>()->yPos--;
	}
}

void PhysicsSystem::tick(ECS::World * world, float deltaTime)
{
	// This gets the collision box for each entity
	world->each<struct BoxCollider, struct Sprite2D, struct Transform>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct BoxCollider> collider,
			ECS::ComponentHandle<struct Sprite2D> sprite,
			ECS::ComponentHandle<struct Transform> transform)->void
		{
			collider->Update(transform->xPos, transform->yPos,
				sprite->picture.getTextureRect().width,
				sprite->picture.getTextureRect().height);
		});

	// Collider for box and transform entities
	world->each<struct BoxCollider, struct Transform>(
		[&](ECS::Entity* touchingEntity,
			ECS::ComponentHandle<struct BoxCollider> touchingBox,
			ECS::ComponentHandle<struct Transform> transform)->void
		{
			world->each<struct BoxCollider>(
				[&](ECS::Entity* touchedEntity,
					ECS::ComponentHandle<struct BoxCollider> touchedBox)->void
				{
					// Statement to avoid comparing the same entity to itself 
					if (touchingEntity->getEntityId() == touchedEntity->getEntityId())
					{
						return;
					}

					// Initial collision check
					if (IsColliding(touchingBox, touchedBox) == false)
					{
						return;
					}

					// Final collision check
					PushEntity(touchingEntity, touchedEntity);
				});
		});

	world->each<struct Transform>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct Transform> transform)->void
		{
			transform->Move();
		});
}

PhysicsSystem::~PhysicsSystem() = default;