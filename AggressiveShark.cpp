#include "pch.h"
#include "AggressiveShark.h"
#include "AnimatedSprite.h"

AggressiveShark::AggressiveShark(Level* level, const Rectf& shape, const Vector2f& speed, int fps)
	: Shark(level, shape, speed, fps)
	, m_CurrentState{ AggressiveShark::SharkState::moving }
	, m_TurnCounts{}
	, m_StateTimer{}
	, m_MoveRange{600.f}
{
	std::cout << "agrgressive shar made";
}

void AggressiveShark::Update(float elapsedSec)
{
	UpdateAnimations(elapsedSec);
	Shark::Update(elapsedSec);
}

void AggressiveShark::UpdatePosition(Entity& entity, float elapsedSec)
{
	MoveShark(entity, elapsedSec);
	Shark::UpdatePosition(entity, elapsedSec);
}

void AggressiveShark::AttackPlayer(Entity& entity)
{
	

	/*if (m_Velocity.y > 0 && m_Shape.left + m_Shape.width <= playerCenterPosition.x || m_Velocity.y < 0 && m_Shape.left <= playerCenterPosition.x)
	{
		m_CurrentState = SharkState::attacking;
	}*/
}

void AggressiveShark::UpdateAnimations(float elapsedSec)
{
	if (m_CurrentState == SharkState::attacking)
	{
		m_pSprite->PlayAnimation("SharkAttack");
		m_StateTimer += elapsedSec;

		if (m_StateTimer >= 1.2f) m_CurrentState = SharkState::moving;
	}
	else
	{
		m_pSprite->PlayAnimation("MovingShark");
	}
}

void AggressiveShark::MoveShark(Entity& entity, float elapsedSec)
{
	/*Rectf standPlatformShark{ m_Shape.left, m_Shape.bottom, m_Shape.width, 5.f };
	(utils::IsOverlapping(entity.GetShape(), standPlatformShark))
		? entity.SetParent(this)
		: entity.SetParent(nullptr);

	entity.SetVelocity(Vector2f{ 0,0 });*/

	std::cout << "Move Shark \n";

	Point2f playerCenterPosition{ entity.GetShape().left + entity.GetShape().width / 2, entity.GetShape().bottom };
	Point2f sharkCenter{ m_Shape.left + m_Shape.width / 2, m_Shape.bottom };

	const int directionShark{ (playerCenterPosition.x < sharkCenter.x) ? -1 : 1 };
	const float speedShark{ 150.f };

	if (sharkCenter.x >= playerCenterPosition.x - m_MoveRange && sharkCenter.x <= playerCenterPosition.x + m_MoveRange)
	{
		m_Velocity.x = directionShark * speedShark;
	}


	/*if(m)*/

}
