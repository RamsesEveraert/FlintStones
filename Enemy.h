#pragma once
#include "Entity.h"
#include "Vector2f.h"

class AnimatedSprites;
class Player;

class Enemy : public Entity
{
public:

	Enemy(Level* level, const std::string& texturePath, const Rectf& shape, const Vector2f& speed, float maxWalkDistance, float activationDistance,  bool isFacingLeft = false);
	virtual ~Enemy() = default;

	Enemy(const Enemy& other) = delete;
	Enemy& operator=(const Enemy& other) = delete;
	Enemy(Enemy&& other) = delete;
	Enemy& operator=(Enemy&& other) = delete;


	virtual void Update(float elapsedSec) ;

	const Point2f GetEnemyPos() const;

protected:

	virtual void StunEntity(Entity& entity) override;

	const float m_MaxWalkDistance;
	const float m_ActivationDistance;

	float m_LastTouchDamageTime, m_TouchDamageCoolDown;
	Rectf m_TouchDamageHitbox;

	bool m_IsActivated;

	void SetEnemyPos(const Point2f position);
	

};

