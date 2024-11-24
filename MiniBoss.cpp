#include "pch.h"
#include "MiniBoss.h"
#include "AnimatedSprite.h"
#include "Level.h"
#include "Wall.h"


MiniBoss::MiniBoss(Level* level, const Rectf& shape, const Vector2f& speed, int fps, float slideDistance)
	: Entity(level, "Resources/Enemies/MiniBoss.png", shape, speed.x, speed.y)
	, m_Fps{fps}
	, m_SlideDistance{slideDistance}
	, m_Timer {}
	, m_CurrentState {MiniBossState::idle}
	, m_CurrentAnimation {"Idle"}
	, m_WallCount {2}
{
	m_IsMiniBoss = true;
	Initialize();
}

void MiniBoss::Initialize()
{
	MiniBoss::SetupAnimations();
	m_Velocity.x = m_HorSpeed;
}


void MiniBoss::SetupAnimations()
{	
	m_IsFacingLeft = true;
	m_pSprite->SetFramesPerSec(m_Fps);
	m_pSprite->AddAnimation("Idle", 0.f, 60.f, m_Shape.width, m_Shape.height, 2);
	m_pSprite->AddAnimation("Attack", 0.f, 0.f, m_Shape.width, m_Shape.height, 3);
	m_pSprite->AddAnimation("Slide", 0.f, 60.f, m_Shape.width, m_Shape.height, 3);
	m_pSprite->AddAnimation("Collision", 0.f, 180.f, m_Shape.width, m_Shape.height, 1);

	
}

void MiniBoss::Update(float elapsedSec)
{
	MiniBoss::HandleStates();
	m_pSprite->Update(elapsedSec, m_Shape);
}

void MiniBoss::HandleWallCollision(float elapsedSec)
{
	m_pLevel->DeleteWall(elapsedSec, *this);	
}

void MiniBoss::HandleStates()
{
	switch (m_CurrentState)
	{
	case MiniBossState::idle:
		m_pSprite->PlayAnimation("Idle");
		break;
	case MiniBossState::attack:
		m_CurrentAnimation = "Attack";
		m_pSprite->SetFramesPerSec(20);
		m_pSprite->PlayAnimation("Attack");
		break;
	case MiniBossState::slide:
		m_pSprite->SetFramesPerSec(6);
		m_CurrentAnimation = "Slide";
		m_pSprite->PlayAnimation("Slide",2, false);
		break;
	case MiniBossState::collision:
		m_pSprite->PlayAnimation("Collision");
		break;
	}
}

void MiniBoss::AttackPlayer(float elapsedSec, const Entity& player)
{
	const float playerMiddle{ player.GetShape().left + player.GetShape().width / 2 };
	m_Timer += elapsedSec;

	m_CurrentState = MiniBossState::attack;

	if (m_Velocity.x < 0 && playerMiddle >= m_Shape.left  || m_Velocity.x > 0 && playerMiddle <= m_Shape.left + m_Shape.width)
	{
		if (m_Timer >= 0.5f)
		{
			MiniBoss::Slide(elapsedSec, playerMiddle);
		}
		
	}
}

void MiniBoss::Slide(float elapsedSec, float playerMiddle)
{
	m_CurrentState = MiniBossState::slide;

	m_Timer += elapsedSec;

	if (m_Timer >= 2.2f)
	{
		m_Velocity.x *= -1;
		m_Timer = 0;

	}


}




void MiniBoss::UpdatePosition(float elapsedSec, Entity& player)
{
	float startMiniBoss{ 8827.f };
	if (player.GetShape().left >= startMiniBoss)
	{
		MiniBoss::HandleWallCollision(elapsedSec);
		MiniBoss::AttackPlayer(elapsedSec, player);

		m_Shape.left += m_Velocity.x * elapsedSec;
		m_Shape.bottom += m_Velocity.y * elapsedSec;
	}

	
}





