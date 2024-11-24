#include "pch.h"
#include "Boss.h"
#include "AnimatedSprite.h"
#include "Level.h"
#include "Wall.h"


Boss::Boss(Level* level, const Rectf& shape, float horSpeed, float jumpSpeed, int fps, float slideDistance)
	: Entity(level, "Resources/Bosses/Boss1.png", shape, horSpeed, jumpSpeed)
	, m_SlideDistance { slideDistance}
{
	Initialize();
}

void Boss::Initialize()
{
	Boss::SetupAnimations();
}


void Boss::SetupAnimations()
{
	m_IsFacingLeft = true;
	m_pSprite->SetFramesPerSec(m_Fps);
	m_pSprite->AddAnimation("Attack", 0.f, 0.f, m_Shape.width, m_Shape.height, 3);
	m_pSprite->AddAnimation("Hit", 0.f, 60.f, m_Shape.width, m_Shape.height, 3);


}


Boss::~Boss()
{
}

void Boss::Update(float elapsedSec)
{
}

void Boss::HandleWallCollision(float elapsedSec)
{
	
}

void Boss::HandleStates()
{
}

void Boss::AttackPlayer(float elapsedSec, const Entity& player)
{
	
}



void Boss::UpdatePosition(float elapsedSec, Entity& player)
{

}




