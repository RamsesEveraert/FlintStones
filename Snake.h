#pragma once
#include "Entity.h"

class SoundEffect;

class Snake final : public Entity
{
public:
	Snake(Level* level, const Rectf& shape, const Vector2f& speed, bool isFacingLeft);
	~Snake();

	Snake(const Snake& other) = delete;
	Snake& operator=(const Snake& other) = delete;
	Snake(Snake&& other) = delete;
	Snake& operator=(Snake&& other) = delete;

	virtual void Update(float elapsedSec) override;
	

	void TriggerAttack(const Rectf& hitboxPlayer);
	void SnakeAttack(float elapsedSec, float maxDistance);
	bool StunSnake(const Rectf& hitboxPlayer);

	const Vector2f GetHitboxOffset() const;

	bool IsAttackTriggered() const;
	bool CheckSnakeStun() const;
	virtual bool HandleCollision(Entity& entity) override;

private:
	enum class States
	{
		idle,
		attack,
		withdraw,
		knockout
	};

	void Initialize();

	virtual void SetupAnimations() override; 
	void HandleStates(float elapsedSec);
	
	void ReturnSnake();
	void ResetStun(float elapsedSec);

	States m_AnimationState;
	const Point2f m_StartPos;

	const Vector2f m_HitboxOffSet, m_PlatformOffset;

	bool m_CanReturn, m_AttackTriggered, m_IsSnakeStunned;

	SoundEffect* m_pBiteSound;
};

