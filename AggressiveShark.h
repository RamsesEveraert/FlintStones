#pragma once
#include "Shark.h"

class AggressiveShark final : public Shark
{

public:

	AggressiveShark(Level* level, const Rectf& shape, const Vector2f& speed, int fps);
	~AggressiveShark() = default;

	AggressiveShark(const AggressiveShark& other) = delete;
	AggressiveShark& operator=(const AggressiveShark& other) = delete;
	AggressiveShark(AggressiveShark&& other) = delete;
	AggressiveShark& operator=(AggressiveShark&& other) = delete;

	virtual void Update(float elapsedSec) override;
	virtual void UpdatePosition(Entity& entity, float elapsedSec) override;

	void AttackPlayer(Entity& entity);
	virtual void MoveShark(Entity& entity, float elapsedSec) override;

private:

	enum class SharkState
	{
		moving,
		attacking
	};

	virtual void UpdateAnimations(float elapsedSec);

	SharkState m_CurrentState;

	int m_TurnCounts;
	float m_StateTimer;
	const float m_MoveRange;
};

