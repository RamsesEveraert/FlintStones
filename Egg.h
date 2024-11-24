#pragma once
#include "WorldObjects.h"

class Entity;
class Egg final : public WorldObjects
{
public:

	enum class States
	{
		initial,
		activated,
		hatched
	};

	Egg(const Point2f& centre, float spriteW, float spriteH, int nrFrames);
	~Egg() = default;

	Egg(const Egg& other) = delete;
	Egg& operator=(const Egg& other) = delete;
	Egg(Egg&& other) = delete;
	Egg& operator=(Egg&& other) = delete;

	virtual void Update(float elapsedSec) override;

	void SetState(States state);
	const States GetState() const;

	void SetParent(Entity* pParent);
	const Entity* GetParent() const;

private:
	void CheckStates();

	const Vector2f m_Speed;
	Entity* m_pParent;
	States m_EggState;
};

