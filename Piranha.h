#pragma once
#include "Entity.h"


class Piranha final : public Entity
{
public:

	Piranha(Level* level, const Rectf& shape, const Vector2f& speed);
	~Piranha() = default;


	Piranha(const Piranha& other) = delete;
	Piranha& operator=(const Piranha& other) = delete;
	Piranha(Piranha&& other) = delete;
	Piranha& operator=(Piranha&& other) = delete;

	virtual void Update(float elapsedSec) override;
	void UpdatePosition(float elapsedSec);

	const Point2f GetSpawnPoint() const;
	void ActivatePiranha();



private:

	void SetupAnimations();

	const Point2f m_SpawnPoint;
};

