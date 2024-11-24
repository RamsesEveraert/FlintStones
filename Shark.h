#pragma once
#include "Entity.h"


class Shark : public Entity
{

public:
	Shark(Level* level, const Rectf& shape, const Vector2f& speed, int fps);
	virtual ~Shark() = default;

	Shark(const Shark& other) = delete;
	Shark& operator=(const Shark& other) = delete;
	Shark(Shark&& other) = delete;
	Shark& operator=(Shark&& other) = delete;

	virtual void Update(float elapsedSec) override;
	virtual void UpdatePosition(Entity& entity, float elapsedSec);
	virtual void MoveShark(Entity& entity, float elapsedSec) = 0;

	bool HandleCollision(Entity& entity);

protected: 

	void SetupAnimations();
	virtual void UpdateAnimations(float elapsedSec);

	void ResetShark(Entity& entity);

	const Point2f m_InitialPos;
	const Vector2f m_PlatformOffset;

	const int m_Fps;
};

