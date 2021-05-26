#include "AnimationSystem.h"

AnimationSystem::AnimationSystem() = default;


AnimationSystem::~AnimationSystem() = default;


void AnimationSystem::tick(ECS::World* world, float deltaTime)
{
	if (States::GetPausedState() == false)
	{
		world->each<struct Animator, struct Sprite2D>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<struct Animator> animator,
				ECS::ComponentHandle<struct Sprite2D> sprite) -> void
			{
				animator->currentTime += deltaTime;
				if (animator->currentTime >= animator->nextFrameTime)
				{
					animator->currentTime = 0;
					animator->currentColumn = (animator->currentColumn + 1) % animator->totalColumns;
				}
				sprite->picture.setTextureRect(
					sf::IntRect(animator->currentColumn * animator->spriteWidth, // Rect left/right
						animator->currentRow * animator->spriteHeight, // Rect top/bottom
						animator->spriteWidth,
						animator->spriteHeight));
			});
	}
}
