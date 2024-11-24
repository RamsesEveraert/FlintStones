#pragma once
#include "Vector2f.h"

class Player;
class AnimatedSprite;
class Level;
class Logs;
class Effects;

class Entity
{
public:

	Entity(Level* level, const std::string& texturePath, const Rectf& shape, float horSpeed, float jumpSpeed, bool isFacingLeft = false);

	Entity(const Entity& other) = delete;
	Entity& operator=(const Entity& other) = delete;
	Entity(Entity&& other) = delete;
	Entity& operator=(Entity&& other) = delete;
	
	virtual ~Entity();

	void Draw(const Level& level);
	virtual void Update(float elapsedSec) = 0;
	virtual void UpdatePosition(float elapsedSec);

	virtual bool HandleCollision(Entity& entity);

	void Knockback(Entity& entity, bool isFacingLeft);

	const int GetKillPoints() const;

	void SetShape(const Rectf& shape);
	const Rectf& GetShape() const;

	void SetGravity(float gravity);
	void SetJumpSpeed(float jumpSpeed);

	void SetHitbox(const Rectf& hitbox);
	const Rectf& GetHitbox() const;

	void SetVelocity(const Vector2f& vel);
	const Vector2f& GetVelocity() const;

	void SetParent(const Entity* pParent);
	const Entity* GetParent() const;

	AnimatedSprite* GetSprite() const;

	void SetStunned(bool isStunned);
	bool CheckIsStunned() const;
	void SetVisible(bool isVisible);

	void SetIsDead(bool isDead);
	bool CheckIsDead() const;

	void SetAttacking(bool isAttacking);
	bool GetIsAttacking() const;

	void SetMovingLog(const Logs* pMovingLog);
	const Logs* GetMovingLog() const;

	bool IsJumping() const;
	bool IsFacingLeft() const;
	bool IsPlayer() const;
	bool IsMiniBoss() const;

	virtual bool IsOnGround();

	// Enity properties

	bool m_CanMove;


	Rectf m_Shape;

protected:

	// General functions

	virtual void SetupAnimations() = 0;

	void StartStunTimer(float elapsedSec);
	virtual void StunEntity(Entity& enemy);
	void EndStun();
	

	// Effects

	Effects* m_pEffect;

	// physics

	Vector2f m_Velocity;
	Vector2f m_GravityAcceleration;
	float m_HorSpeed, m_JumpSpeed;

	bool m_IsJumping;
	
	// Sprite properties

	AnimatedSprite* m_pSprite;

	// entity properties

	Point2f m_InitialPosition;

	float m_StartTimer, m_StunTimer, m_KnockbackStartTime;
	int m_KillPoints;

	bool m_IsVisible, m_IsFacingLeft;
	bool m_IsAttacking;
	bool m_IsInvinsible;
	bool m_CanBeHit;

	int m_StunFrames;
	bool m_IsStunned;
	bool m_IsDead;

	bool m_IsPlayer, m_IsMiniBoss;

	std::vector<Point2f> m_PlatformVertices;

	Rectf m_Hitbox;

	const Entity* m_pParent;
	const Logs* m_MovingLog;

	// level

	Level* m_pLevel;
	

	// animation properties

private:

	void DrawReversed() const;
};


