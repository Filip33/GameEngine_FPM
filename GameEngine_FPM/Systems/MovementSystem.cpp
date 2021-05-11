#include "MovementSystem.h"

MovementSystem::MovementSystem() = default;

void MovementSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<struct InputController, struct Transform, struct Animator>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct InputController> input,
			ECS::ComponentHandle<struct Transform> transform,
			ECS::ComponentHandle<struct Animator> animator) -> void
		{
			if (input->bInputActive)
			{
				// UP
				if (input->wKey)
				{
					transform->ySpeed = -transform->ySpeedMod;
					transform->Move();
				}
				// DOWN
				else if (input->sKey)
				{
					transform->ySpeed = transform->ySpeedMod;
					transform->Move();
				}
				else
				{
					// STOP
					animator->currentRow = 0;
					transform->ySpeed = 0;
				}

				// LEFT
				if (input->aKey)
				{
					animator->bFacingRight = false;
					animator->currentRow = 1;
					transform->xSpeed = -transform->xSpeedMod;
					transform->Move();
				}
				// RIGHT
				else if (input->dKey)
				{
					animator->bFacingRight = true;
					animator->currentRow = 1;
					transform->xSpeed = transform->xSpeedMod;
					transform->Move();
				}
				else
				{
					// STOP
					animator->currentRow = 0;
					transform->xSpeed = 0;
				}
			}
		});
}

MovementSystem::~MovementSystem() = default;