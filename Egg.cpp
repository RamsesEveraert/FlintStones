#include "pch.h"
#include "Egg.h"
#include "Entity.h"
#include "AnimatedSprite.h"

Egg::Egg(const Point2f& centre, float spriteW, float spriteH, int nrFrames)
		: WorldObjects(centre, spriteW, spriteH, nrFrames)
	, m_EggState {States::initial}
	, m_pParent {nullptr}
	, m_Speed {0.9f, 1.f}
{
	WorldObjects::CreateObject("Egg", 81.f, 4);
	m_pSprite->AddAnimation("EggActivated", 0.f, 81.f, m_Shape.width, m_Shape.height, 2);
	m_pSprite->AddAnimation("EggHatched", 0.f, 108.f, m_Shape.width, m_Shape.height, 2);
}

#pragma region GeneralFunctions
void Egg::Update(float elapsedSec)
{
	Egg::CheckStates();
	WorldObjects::Update(elapsedSec);
	if (m_pParent)
	{
		bool isfacingLeft{ m_pParent->IsFacingLeft() };
		Rectf shapeParent{ m_pParent->GetShape() };
		Vector2f velocityParent{ m_pParent->GetVelocity() };
		Vector2f speed = m_Speed;

		if (abs(m_Shape.left - (m_pParent->GetShape().left + 0.5f * shapeParent.width)) >= 1.5f * (shapeParent.width))
		{
			speed = Vector2f{ 1.f,1.f };
		}

		if (m_Shape.left + m_Shape.width < shapeParent.left)
		{
			(isfacingLeft)
				? m_Shape.left -= velocityParent.x * m_Speed.x * elapsedSec
				: m_Shape.left += velocityParent.x * m_Speed.x * elapsedSec;



		}
		else if (m_Shape.left + m_Shape.width > shapeParent.left + shapeParent.width)
		{
			(isfacingLeft)
				? m_Shape.left += velocityParent.x * m_Speed.x * elapsedSec
				: m_Shape.left -= velocityParent.x * m_Speed.x * elapsedSec;
		}

		m_Shape.bottom += velocityParent.y * elapsedSec;

		if (velocityParent.x == 0 && velocityParent.y == 0)
		{
			(isfacingLeft)
				? m_Shape.left = shapeParent.left + shapeParent.width / 2 + m_Shape.width / 2
				: m_Shape.left = shapeParent.left - m_Shape.width / 2;

			m_Shape.bottom = shapeParent.bottom;
		}
	}
}

void Egg::CheckStates()
{
	switch (m_EggState)
	{
	case States::initial:
		m_pSprite->PlayAnimation("Egg");
		break;
	case States::activated:
		m_pSprite->SetFramesPerSec(4);
		m_pSprite->PlayAnimation("EggActivated");
		break;
	case States::hatched:
		m_pSprite->SetFramesPerSec(4);
		m_pSprite->PlayAnimation("EggHatched");
		break;
	}
}
#pragma endregion 
#pragma region GettersAndSetters
const Egg::States Egg::GetState() const
{
	return m_EggState;
}
const Entity* Egg::GetParent() const
{
	return m_pParent;
}
void Egg::SetState(States state)
{
	m_EggState = state;
}
void Egg::SetParent(Entity* pParent)
{
	m_pParent = pParent;
}
#pragma endregion 