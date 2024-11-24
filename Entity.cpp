#include "pch.h"
#include "Entity.h"
#include "Level.h"
#include "Logs.h"
#include "Effects.h"
#include "AnimatedSprite.h"
#include "Player.h"

Entity::Entity(Level* level, const std::string& texturePath, const Rectf& shape, float horSpeed, float jumpSpeed, bool isFacingLeft)
	: m_Velocity {}
	, m_GravityAcceleration {0,-981.f}
	, m_InitialPosition{ shape.left, shape.bottom }
	, m_HorSpeed { horSpeed }
	, m_JumpSpeed { jumpSpeed }
	, m_CanBeHit {true}
	, m_CanMove{true}
	, m_IsAttacking{ false }
	, m_IsFacingLeft{ isFacingLeft }
	, m_Shape { shape }
	, m_pSprite {new AnimatedSprite(texturePath, shape.width, shape.height)}
	, m_pEffect { new Effects()}
	, m_IsVisible{ true }
	, m_IsInvinsible {false}
	, m_pLevel {level}
	, m_IsJumping {false}
	, m_StartTimer {}
	, m_StunTimer{}
	, m_KnockbackStartTime {}
	, m_pParent{ nullptr }
	, m_MovingLog {nullptr}
	, m_PlatformVertices {}
	, m_Hitbox {shape}
	, m_IsPlayer { false }
	, m_IsMiniBoss {false}
	, m_StunFrames {}
	, m_IsStunned {false}
	, m_IsDead { false}
	, m_KillPoints {}


{
}

Entity::~Entity()
{
	delete m_pSprite;
	m_pSprite = nullptr;

	delete m_pEffect;
	m_pEffect = nullptr;
}

#pragma region Initialization
#pragma endregion 
#pragma region GenralFunctions
void Entity::Draw(const Level& level) // geen const omdat ik datamembers moet aanpassen, nog geen alternatief
{
	if (m_Velocity.x != 0)
	{
		(m_Velocity.x < 0)
			? m_IsFacingLeft = true
			: m_IsFacingLeft = false;
	}

	m_pEffect->Draw();

	if (m_IsVisible)
	{
		(m_IsFacingLeft)
			? Entity::DrawReversed()
			: m_pSprite->Draw();

	}

}

void Entity::UpdatePosition(float elapsedSec)
{

	if (m_pParent)
	{
		m_Shape.left += m_pParent->m_Velocity.x * elapsedSec;
		m_Shape.bottom += m_pParent->m_Velocity.y * elapsedSec;
	}
	if (m_MovingLog)
	{
		m_Shape.left += m_MovingLog->GetVelocity().x * elapsedSec;
		m_Shape.bottom += m_MovingLog->GetVelocity().y * elapsedSec;
	}

	m_Velocity.y += m_GravityAcceleration.y * elapsedSec;
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;

	m_pLevel->HandleCollision(*this);

}


bool Entity::HandleCollision(Entity& entity)
{

	const Rectf& entityShape{ entity.GetShape() };
	const Point2f rayP1{ entityShape.left + (entityShape.width / 2), entityShape.bottom + (entityShape.height / 5) };
	const Point2f rayP2{ entityShape.left + (entityShape.width / 2), entityShape.bottom - 1.f };

	utils::HitInfo hitinfo;
	if (entity.GetVelocity().y <= 0 && utils::Raycast(m_PlatformVertices, rayP1, rayP2, hitinfo))
	{
		
		

		Rectf newShape{ entityShape };
		newShape.bottom = hitinfo.intersectPoint.y;

		entity.SetShape(newShape);
		entity.SetVelocity(Vector2f{});
		entity.SetParent(this);
		
		return true;
	}

	entity.SetParent(nullptr);
	return false;
}
void Entity::Knockback(Entity& entity, bool isFacingLeft)
{
//TODO
}
const int Entity::GetKillPoints() const
{
	return m_KillPoints;
}
void Entity::DrawReversed() const
{
	Point2f centerSprite{ m_Shape.left + m_pSprite->GetSpriteWidth() / 2,
													m_Shape.bottom + m_pSprite->GetSpriteHeight() / 2 };

	glPushMatrix();
	glTranslatef(centerSprite.x, centerSprite.y, 0);
	glScalef(-1, 1, 1);
	glTranslatef(-centerSprite.x, -centerSprite.y, 0);
	m_pSprite->Draw();
	glPopMatrix();
}
void Entity::StartStunTimer(float elapsedSec)
{
	m_StunTimer += elapsedSec;
	m_StunFrames++;

	if (!m_IsPlayer && m_StunTimer > 4.f || m_IsPlayer && m_StunTimer > 3.f)
	{
		m_IsPlayer
			? m_IsVisible = true
			: m_IsVisible = false;

		m_StunFrames = 0;
		Entity::EndStun();
	}
	else
	{
		(m_StunFrames % 2 == 0)
			? m_IsVisible = false
			: m_IsVisible = true;
	}

}
#pragma endregion 
#pragma region GettersAndSetters
void Entity::SetShape(const Rectf& shape)
{
	m_Shape = shape;
}
void Entity::SetVelocity(const Vector2f& vel)
{
	m_Velocity = vel;
}
void Entity::SetHitbox(const Rectf& hitbox)
{
	m_Hitbox = hitbox;
}
void Entity::SetStunned(bool isStunned)
{
	m_IsStunned = isStunned;
}
bool Entity::CheckIsStunned() const
{
	return m_IsStunned;
}
void Entity::SetMovingLog(const Logs* pMovingLog)
{
	m_MovingLog = pMovingLog;
}
void Entity::SetVisible(bool isVisible)
{
	m_IsVisible = isVisible;
}
void Entity::SetParent(const Entity* pParent)
{
	m_pParent = pParent;
}

const Rectf& Entity::GetShape() const
{
	return m_Shape;
}
void Entity::SetGravity(float gravity)
{
	m_GravityAcceleration.y = gravity;
}
void Entity::SetJumpSpeed(float jumpSpeed)
{
	m_JumpSpeed = jumpSpeed;
}
const Rectf& Entity::GetHitbox() const
{
	return m_Hitbox;
}
const Vector2f& Entity::GetVelocity() const
{
	return m_Velocity;
}
const Entity* Entity::GetParent() const
{
	return m_pParent;
}
AnimatedSprite* Entity::GetSprite() const
{
	return m_pSprite;
}
const Logs* Entity::GetMovingLog() const
{
	return m_MovingLog;
}
#pragma endregion 
#pragma region Checks
bool Entity::IsOnGround()
{
	if (m_pLevel->CheckIsOnGround(*this))
	{
		m_Velocity.y = 0.f;
		return true;
	}
	m_GravityAcceleration.y = -981.f;
	return false;
}
void Entity::StunEntity(Entity& enemy)
{
	if (!enemy.CheckIsDead())
	{
		Vector2f newVelocity{ enemy.GetVelocity() };
		newVelocity.x = 0;

		enemy.SetStunned(true);
		enemy.SetVelocity(newVelocity);

		Rectf animLocation{ enemy.GetShape() };
		animLocation.left += (animLocation.width / 2.f);
		animLocation.bottom += (0.7f * animLocation.height);

		m_pEffect->SetDestinationEffect(animLocation);
		m_pEffect->PlayEffect(Effects::Effect::stunned, true, 0);
	}
	

}
void Entity::EndStun()
{
	Player* pPlayer = dynamic_cast<Player*>(this);

	if (m_pEffect->GetCurrentEffectName() == "Stun")
		m_pEffect->StopEffect();

	m_IsStunned = false;
	m_StunTimer = 0;

	if (pPlayer)
	{
		m_IsInvinsible = false;

		if (pPlayer->GetHearts() <= 0)  m_IsDead;
	}
	else
	{
		m_IsDead = true;
		m_Shape.left = 0;
	}
	
}
void Entity::SetIsDead(bool isDead)
{
	m_IsDead = isDead;
}
bool Entity::CheckIsDead() const
{
	return m_IsDead;
}
void Entity::SetAttacking(bool isAttacking)
{
	m_IsAttacking = isAttacking;
}
bool Entity::GetIsAttacking() const
{
	return m_IsAttacking;
}
bool Entity::IsJumping() const
{
	return m_IsJumping;
}
bool Entity::IsFacingLeft() const
{
	return m_IsFacingLeft;
}
bool Entity::IsPlayer() const
{
	return m_IsPlayer;
}
bool Entity::IsMiniBoss() const
{
	return m_IsMiniBoss;
}
#pragma endregion 