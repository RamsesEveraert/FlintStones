#pragma once
#include "Entity.h"

class MiniBoss final : public Entity
{
public:
	MiniBoss(Level* level, const Rectf& shape, const Vector2f& speed, int fps, float slideDistance);
	~MiniBoss() = default;

	MiniBoss(const MiniBoss& other) = delete;
	MiniBoss& operator=(const MiniBoss& other) = delete;
	MiniBoss(MiniBoss&& other) = delete;
	MiniBoss& operator=(MiniBoss&& other) = delete;

	virtual void Update(float elapsedSec) override;
	void UpdatePosition(float elapsedSec, Entity& player);
	

private:

	enum class MiniBossState
	{
		idle,
		attack,
		slide,
		collision
	};

	void Initialize();
	void SetupAnimations();
	void HandleWallCollision(float elapsedSec);

	void HandleStates();

	void AttackPlayer(float elapsedSec, const Entity& player);
	void Slide(float elapsedSec, float playerMiddle);


	MiniBossState m_CurrentState;

	std::string m_CurrentAnimation;

	const int m_Fps, m_WallCount;
	const float m_SlideDistance;
	float m_Timer;

};

