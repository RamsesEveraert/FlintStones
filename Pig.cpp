#include "pch.h"
#include "Pig.h"
#include "AnimatedSprite.h"
#include "Level.h"

Pig::Pig(Level* level, const Rectf& shape, const Vector2f& speed, float maxWalkDistance, float activationDistance, bool isFacingLeft)
	:Enemy(level, "Resources/Enemies/Pig.png", shape, speed, maxWalkDistance, activationDistance, isFacingLeft)
{
	Pig::SetupAnimations();
	m_KillPoints = 150;
}

void Pig::Update(float elapsedSec)
{
	m_pSprite->Update(elapsedSec, m_Shape);
	Entity::UpdatePosition(elapsedSec);
	Enemy::Update(elapsedSec);
}

void Pig::MovePig(const Entity& player)
{
	float activationDistance{ 100.f };
	if (!m_IsActivated && player.GetShape().left + player.GetShape().width >= m_Shape.left - activationDistance)
	{
		m_pSprite->SetFramesPerSec(16);
		m_pSprite->PlayAnimation("PigWalk");
		m_IsActivated = true;
		m_Velocity.x = -m_HorSpeed;
	}

	if (m_Shape.left <= m_InitialPosition.x - m_MaxWalkDistance)
	{
		m_IsDead = true;
		m_pSprite->SetVisible(false);
		m_Shape.left = 0;
	}
}

void Pig::StunEntity(Entity& entity)
{
	Enemy::StunEntity(entity);
	m_pSprite->PlayAnimation("PigDead");
}


void Pig::SetupAnimations()
{
	m_pSprite->SetFramesPerSec(4);
	m_pSprite->AddAnimation("PigIdle", 0, 0, 50.f, 36.f, 2);
	m_pSprite->AddAnimation("PigWalk", 0.f, 36.f, 50.f, 36.f, 3);
	m_pSprite->AddAnimation("PigDead", 100.f, 36.f, 50.f, 36.f, 1);
	m_pSprite->PlayAnimation("PigIdle");
}