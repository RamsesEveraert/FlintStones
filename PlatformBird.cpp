#include "pch.h"
#include "PlatformBird.h"
#include "AnimatedSprite.h"


int PlatformBird::m_PlatformBirdCount{};

PlatformBird::PlatformBird(Level* level, const Rectf& shape, const Vector2f& speed, int fps, float radius, BirdType type)
	: Entity(level, "Resources/Enemies/PlatformBird.png", shape, speed.x, speed.y)
	, m_Angle {}
	, m_Fps {fps}
	, m_Type{ type }
	, m_Radius{radius}
	, m_IsOnMovingPlatform {false}
{
	Initialize();
	m_PlatformBirdCount++;
}

void PlatformBird::Initialize()
{
	PlatformBird::SetupAnimations();
}


void PlatformBird::SetupAnimations()
{
	m_pSprite->SetFramesPerSec(m_Fps);
	m_pSprite->AddAnimation("MovingPlatform", 0.f, 0.f, m_Shape.width, m_Shape.height, 3);
	m_pSprite->AddAnimation("MovingPlatformLong", 52.f, 100.f, m_Shape.width, m_Shape.height, 3);
	
}


void PlatformBird::Update(float elapsedSec)
{
	PlatformBird::UpdatePosition(elapsedSec);
	ResetTrapBird();
	
	(m_Type == BirdType::platform_long)
		? m_pSprite->PlayAnimation("MovingPlatformLong")
		: m_pSprite->PlayAnimation("MovingPlatform");

	m_pSprite->Update(elapsedSec, m_Shape);
}

bool PlatformBird::IsOnMovingPlatform() const
{
	return m_IsOnMovingPlatform;
}

bool PlatformBird::HandleCollision(Entity& entity)
{
	m_PlatformVertices = std::vector<Point2f>
	{
		Point2f{m_Shape.left + 3.f,  m_Shape.bottom + 7.f},					// left vert
		Point2f{m_Shape.left + m_Shape.width - 3.f, m_Shape.bottom + 7.f}	// right vert
	};


	return Entity::HandleCollision(entity);
}

void PlatformBird::DropPlatform(Entity& entity)
{
	const float fallSpeed{ -500.f };
	m_Velocity.y = fallSpeed;
}

void PlatformBird::ShootPlatform(Entity& entity)
{
	const float shootSpeed{ 630.f };
	m_Velocity.y = shootSpeed;
}

PlatformBird::BirdType PlatformBird::GetBirdType() const
{
	return m_Type;
}


void PlatformBird::UpdatePosition(float elapsedSec)
{
	if (m_Type == BirdType::platform || m_Type == BirdType::platform_long)
	{
		m_Angle += m_HorSpeed;
		m_Velocity.x = (sin(m_Angle)) * m_Radius;

	}

	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
}

void PlatformBird::ResetTrapBird()
{
	if (m_Type == BirdType::trap_down && m_Shape.bottom + m_Shape.height <= 0.f)
	{
		m_Velocity = Vector2f{};
		m_Shape.left = m_InitialPosition.x;
		m_Shape.bottom = m_InitialPosition.y;
	}

	if (m_Type == BirdType::trap_up && m_Shape.bottom >= 790.f)
	{
		m_Velocity = Vector2f{};
		m_Shape.left = m_InitialPosition.x;
		m_Shape.bottom = m_InitialPosition.y;
	}
}