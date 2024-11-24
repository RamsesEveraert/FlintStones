#include "pch.h"
#include "Enemy.h"
#include "Effects.h"
#include <iostream>

Enemy::Enemy(Level* level, const std::string& texturePath, const Rectf& shape, const Vector2f& speed, float maxWalkDistance, float activationDistance, bool isFacingLeft)
	: Entity(level, texturePath, shape, speed.x, speed.y, isFacingLeft)
	, m_IsActivated {false}
	, m_MaxWalkDistance { maxWalkDistance }
	, m_ActivationDistance { activationDistance }
	, m_LastTouchDamageTime{}
	, m_TouchDamageCoolDown {}
	, m_TouchDamageHitbox{}

{
}

void Enemy::Update(float elapsedSec)
{
	m_pEffect->Update(elapsedSec,*this);

	if (m_IsStunned)
		Entity::StartStunTimer(elapsedSec);

}


const Point2f Enemy::GetEnemyPos() const
{
	return Point2f{ m_Shape.left, m_Shape.bottom };
}

void Enemy::StunEntity(Entity& entity)
{
	Entity::StunEntity(entity);
}

void Enemy::SetEnemyPos(const Point2f position)
{
	m_Shape.left = position.x;
	m_Shape.bottom = position.y;

}
