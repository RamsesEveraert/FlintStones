#include "pch.h"
#include "Piranha.h"
#include "AnimatedSprite.h"

Piranha::Piranha(Level* level, const Rectf& shape, const Vector2f& speed)
	: Entity(level, "Resources/Enemies/Piranha.png", shape, speed.x, speed.y)
	, m_SpawnPoint { shape.left, shape.bottom}
{
	Piranha::SetupAnimations();
	m_GravityAcceleration.y = 0;
	m_Velocity = Vector2f{ 0,0 };
}

void Piranha::Update(float elapsedSec)
{
	m_pSprite->Update(elapsedSec, m_Shape);
	UpdatePosition(elapsedSec);

	if (m_Shape.bottom + m_Shape.height < 0 && m_Velocity.y <= 0)
	{
		m_pSprite->SetVisible(false);
	}

	(m_Velocity.y >= 0)
		? m_pSprite->PlayAnimation("Jump")
		: m_pSprite->PlayAnimation("Fall");

}

void Piranha::UpdatePosition(float elapsedSec)
{
	m_Velocity.y += m_GravityAcceleration.y * elapsedSec;
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
}

const Point2f Piranha::GetSpawnPoint() const
{
	return m_SpawnPoint;
}

void Piranha::ActivatePiranha()
{
	std::cout << "piranha activated";
	m_Velocity.y = m_JumpSpeed;
	m_Velocity.x = m_HorSpeed;
	m_GravityAcceleration.y = -981.f;
}

void Piranha::SetupAnimations()
{
	m_pSprite->AddAnimation("Jump", 0, 0, m_Shape.width, m_Shape.height, 1);
	m_pSprite->AddAnimation("Fall", 0, m_Shape.width, m_Shape.width, m_Shape.height, 1);
}


