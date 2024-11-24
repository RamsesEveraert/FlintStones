#pragma once
#include "Enemy.h"

class Pig final : public Enemy
{

public:
	Pig(Level* level, const Rectf& shape, const Vector2f& speed, float maxWalkDistance, float activationDistance, bool isFacingLeft);
	~Pig() = default;


	Pig(const Pig& other) = delete;
	Pig& operator=(const Pig& other) = delete;
	Pig(Pig&& other) = delete;
	Pig& operator=(Pig&& other) = delete;

	virtual void Update(float elapsedSec) override;

	void MovePig(const Entity& player);
	virtual void StunEntity(Entity& entity) override;

private:

	void SetupAnimations();

};

