#pragma once
#include "Enemy.h"

class GreenBlop final : public Enemy
{
public:
	GreenBlop(Level* level, const Rectf& shape, const Vector2f& speed, float maxWalkDistance, float activationDistance, bool isFacingLeft);
	~GreenBlop() = default;

	GreenBlop(const GreenBlop& other) = delete;
	GreenBlop& operator=(const GreenBlop& other) = delete;
	GreenBlop(GreenBlop&& other) = delete;
	GreenBlop& operator=(GreenBlop&& other) = delete;

	virtual void Update(float elapsedSec) override;

	void MoveBlop(const Entity& player);
	virtual void StunEntity(Entity& entity) override;

private:
	void SetupAnimations();	

};

