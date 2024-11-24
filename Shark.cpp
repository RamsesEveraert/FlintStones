#include "pch.h"
#include "Shark.h"
#include "Entity.h"
#include "Player.h"
#include "AnimatedSprite.h"

Shark::Shark(Level* level, const Rectf& shape, const Vector2f& speed, int fps)
	: Entity(level, "Resources/Enemies/Shark.png", shape, speed.x, speed.y)
	, m_Fps{ fps }
	, m_PlatformOffset{ 7.f,3.f }
	, m_InitialPos{ shape.left, shape.bottom }
{
	Shark::SetupAnimations();
}

void Shark::Update(float elapsedSec)
{
	m_pSprite->Update(elapsedSec, m_Shape);
}

bool Shark::HandleCollision(Entity& entity)
{
	m_PlatformVertices = std::vector<Point2f>{
		Point2f{m_Shape.left + m_PlatformOffset.x, m_Shape.bottom + m_PlatformOffset.y},
		Point2f{m_Shape.left + m_Shape.width, m_Shape.bottom + m_PlatformOffset.y}
	};



	return Entity::HandleCollision(entity);
}

void Shark::SetupAnimations()
{
	m_pSprite->SetFramesPerSec(m_Fps);
	m_pSprite->AddAnimation("IdleShark", 0, 0, m_Shape.width, m_Shape.height, 1);
	m_pSprite->AddAnimation("MovingShark", 0, 0, m_Shape.width, m_Shape.height, 2);
	m_pSprite->AddAnimation("SharkAttack", 0, 65.f, 129.f, 65.f, 2);
}

void Shark::UpdateAnimations(float elapsedSec)
{
	m_pSprite->PlayAnimation("MovingShark");
}

void Shark::ResetShark(Entity& entity)
{
	if (m_Shape.bottom + m_Shape.height < 0)
	{
		m_Shape.left = m_InitialPos.x;
		m_Shape.bottom = m_InitialPos.y;
		m_Velocity = Vector2f{};
	}
}

void Shark::UpdatePosition(Entity& entity, float elapsedSec)
{
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
}


