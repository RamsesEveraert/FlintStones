#include "pch.h"
#include "Snake.h"
#include "AnimatedSprite.h"
#include "SoundEffect.h"


Snake::Snake(Level* level, const Rectf& shape, const Vector2f& speed, bool isFacingLeft)
	: Entity(level, "Resources/Enemies/Snake.png", shape, speed.x, speed.y, isFacingLeft)
	, m_AnimationState { States::idle }
	, m_StartPos { shape.left, shape.bottom }
	, m_CanReturn { false }
	, m_AttackTriggered { false }
	, m_IsSnakeStunned { false }
	, m_HitboxOffSet { 80.f, shape.height / 2 }
	, m_PlatformOffset {10.f, 3.f}
	, m_pBiteSound {new SoundEffect("Resources/Audio/Flintstones_SnakeAttack.wav")}
{
	Initialize();
}

Snake::~Snake()
{
	delete m_pBiteSound;
}

void Snake::HandleStates(float elapsedSec)
{
	switch (m_AnimationState)
	{
	case States::idle:
		m_pSprite->PlayAnimation("SnakeIdle");
		break;
	case States::attack:
		m_pSprite->PlayAnimation("SnakeAttack");
		m_pBiteSound->Play(0);
		break;
	case States::withdraw:
		m_pSprite->PlayAnimation("SnakeIdle");
		break;
	case States::knockout:
		m_pSprite->PlayAnimation("SnakeKnockout");
		break;
	default:
		break;
	}
}

void Snake::SnakeAttack(float elapsedSec, float maxDistance)
{

	if (m_IsSnakeStunned)
	{
		m_AnimationState = States::knockout;
	}
	else
	{
		m_StartTimer += elapsedSec;

		if (m_IsFacingLeft)
		{
			
			if (m_StartTimer > 0.6f && !m_CanReturn && m_Shape.left > (m_StartPos.x - maxDistance))
				m_Shape.left -= 2.f;
			if (m_StartTimer > 0.7f)
				m_AnimationState = States::attack;				
			if (m_StartTimer > 1.1f)
				m_AnimationState = States::withdraw;
			if (m_StartTimer > 1.8f)
				Snake::ReturnSnake();

		}
		else
		{
			if (m_StartTimer > 0.6f && !m_CanReturn && m_Shape.left < (m_StartPos.x + maxDistance))
				m_Shape.left += 2.f;
			if (m_StartTimer > 0.7f)
				m_AnimationState = States::attack;
			if (m_StartTimer > 1.1f)
				m_AnimationState = States::withdraw;
			if (m_StartTimer > 1.8f)
				Snake::ReturnSnake();
		}

		
	}
}

bool Snake::StunSnake(const Rectf& hitboxPlayer)
{
	Vector2f hitboxOffset{ 5.f,10.f };
	
	Rectf snakeHitbox{  m_Shape.left + hitboxOffset.x,
						m_Shape.bottom - hitboxOffset.y,
						m_Shape.width,
						(m_Shape.height / 2) - hitboxOffset.y }; 

	if (utils::IsOverlapping(hitboxPlayer, snakeHitbox))
	{
		m_IsSnakeStunned = true;
		return true;
	}

	return false;
}

const Vector2f Snake::GetHitboxOffset() const
{
	return m_HitboxOffSet;
}

void Snake::ReturnSnake()
{
	m_CanReturn = true;

	if (m_IsFacingLeft)
	{
		if (m_Shape.left < m_StartPos.x)
			m_Shape.left += 2.f;

		if (m_CanReturn && m_Shape.left >= m_StartPos.x)
		{
			m_CanReturn = false;
			m_AttackTriggered = false;
			m_StartTimer = 0;
			m_AnimationState = States::idle;
		}
	}
	else
	{
		if (m_Shape.left > m_StartPos.x)
			m_Shape.left -= 2.f;

		if (m_CanReturn && m_Shape.left <= m_StartPos.x)
		{
			m_CanReturn = false;
			m_AttackTriggered = false;
			m_StartTimer = 0;
			m_AnimationState = States::idle;
		}
	}

	
}

void Snake::ResetStun(float elapsedSec)
{
	m_StunTimer += elapsedSec;

	if (m_StunTimer > 2.5f)
	{
		m_IsSnakeStunned = false;
		m_CanReturn = true;
		m_StunTimer = 0;
		Snake::ReturnSnake();
	}

	
}

void Snake::TriggerAttack( const Rectf& hitboxPlayer)
{
	Rectf hitboxSnake{ m_Shape.left - m_HitboxOffSet.x, m_Shape.bottom - m_HitboxOffSet.y,m_Shape.width + 2.f * m_HitboxOffSet.x, m_Shape.height + 2.f * m_HitboxOffSet.y };

	if (utils::IsOverlapping(hitboxPlayer, hitboxSnake))
	{
		m_AttackTriggered = true;
		
	}	
		
}

bool Snake::IsAttackTriggered() const
{
	return m_AttackTriggered;
}

bool Snake::CheckSnakeStun() const
{
	return m_IsSnakeStunned;
}

bool Snake::HandleCollision(Entity& entity)
{
	m_PlatformVertices = std::vector<Point2f>{
		Point2f{m_Shape.left + (m_Shape.width / 4) - m_PlatformOffset.x, m_Shape.bottom + (m_Shape.height / 2) + m_PlatformOffset.y},
		Point2f{m_Shape.left + m_Shape.width, m_Shape.bottom + (m_Shape.height / 2) + m_PlatformOffset.y}
	};

	return Entity::HandleCollision(entity);
}

void Snake::Update(float elapsedSec)
{
	if (m_IsSnakeStunned)
	Snake::ResetStun(elapsedSec);

	m_pSprite->Update(elapsedSec, m_Shape);
	HandleStates(elapsedSec);

	
}

void Snake::Initialize()
{
	SetupAnimations();
	m_pBiteSound->SetVolume(8);
}

void Snake::SetupAnimations()
{
	m_pSprite->SetFramesPerSec(4);
	m_pSprite->AddAnimation("SnakeIdle", 0, 0, 116.f, 39.f, 2);
	m_pSprite->AddAnimation("SnakeAttack", 0,39.f, 116.f, 39.f, 1);
	m_pSprite->AddAnimation("SnakeKnockout", 0,78.f, 116.f, 39.f, 1);
}
