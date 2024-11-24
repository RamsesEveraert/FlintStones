#pragma once
#include "Entity.h"

class AnimatedSprite;
class PlatformBird final : public Entity
{
public:
	
	enum class BirdType
	{
		platform,
		platform_long,
		trap_down,
		trap_up
	};

	PlatformBird(Level* level, const Rectf& shape, const Vector2f& speed, int fps, float radius, BirdType type);
	~PlatformBird() = default;

	PlatformBird(const PlatformBird& other) = delete;
	PlatformBird& operator=(const PlatformBird& other) = delete;
	PlatformBird(PlatformBird&& other) = delete;
	PlatformBird& operator=(PlatformBird&& other) = delete;

	virtual void Update(float elapsedSec) override;
	bool IsOnMovingPlatform() const;

	virtual bool HandleCollision(Entity& entity) override;

	void DropPlatform(Entity& entity);
	void ShootPlatform(Entity& entity);

	BirdType GetBirdType() const;

private:

	void Initialize();

	virtual void SetupAnimations() override;
	virtual void UpdatePosition(float elapsedSec) override;

	void ResetTrapBird();


	static int m_PlatformBirdCount;

	BirdType m_Type;

	float m_Angle;
	const int m_Fps;
	const float m_Radius;

	bool m_IsOnMovingPlatform;
};

