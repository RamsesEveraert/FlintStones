#include "pch.h"
#include "GreenBlop.h"
#include "AnimatedSprite.h"
#include "Level.h"

GreenBlop::GreenBlop(Level* level, const Rectf& shape, const Vector2f& speed, float maxWalkDistance, float activationDistance, bool isFacingLeft)
	:Enemy(level, "Resources/Enemies/GreenBlop.png", shape, speed, maxWalkDistance, activationDistance, isFacingLeft)
{
	GreenBlop::SetupAnimations();
	m_KillPoints = 100;
	m_Hitbox.height = m_Shape.height / 2;
}

void GreenBlop::Update(float elapsedSec)
{
	m_pSprite->Update(elapsedSec, m_Shape);
	Entity::UpdatePosition(elapsedSec);
	Enemy::Update(elapsedSec);
}

void GreenBlop::MoveBlop(const Entity& player)
{
	float activationDistance{ 100.f };
	if (!m_IsActivated && player.GetShape().left + player.GetShape().width >= m_Shape.left - activationDistance)
	{
		m_IsActivated = true;
		m_Velocity.x = -m_HorSpeed;
	}

	if (m_Shape.left <= m_InitialPosition.x - m_MaxWalkDistance || m_Shape.left + m_Shape.width >= m_InitialPosition.x + m_MaxWalkDistance)
	{
		m_Velocity.x *= -1;
	}
}

void GreenBlop::StunEntity(Entity& enemy)
{
	Enemy::StunEntity(enemy);
	m_pSprite->PlayAnimation("BlopDead");
}


void GreenBlop::SetupAnimations()
{
	m_pSprite->SetFramesPerSec(4);
	m_pSprite->AddAnimation("BlopWalk", 0, 11.f, 35.f, 22.f, 2);
	m_pSprite->AddAnimation("BlopDead", 0, 44.f, 35.f, 22.f, 1);
	m_pSprite->PlayAnimation("BlopWalk");
}

