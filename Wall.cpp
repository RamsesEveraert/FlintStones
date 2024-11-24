#include "pch.h"
#include "Wall.h"
#include "AnimatedSprite.h"

Wall::Wall(const Rectf& shape)
	: m_Shape {shape}
{
	InitWall();
}

Wall::~Wall()
{
	delete m_pSprite;
	m_pSprite = nullptr;
}

#pragma region Initialization
void Wall::InitWall()
{
	m_pSprite = new AnimatedSprite("Resources/Objects/Wall.png", m_Shape.width, m_Shape.height);
	m_pSprite->SetFramesPerSec(1);
	m_pSprite->AddAnimation("Wall", 0.f, 0.f, m_Shape.width, m_Shape.height, 1);
	m_pSprite->PlayAnimation("Wall");
}
#pragma endregion 
#pragma region GeneralFunctions
void Wall::Draw() const
{
	m_pSprite->Draw();
}

void Wall::Update(float elapsedSec)
{
	m_pSprite->Update(elapsedSec, m_Shape);
}
#pragma endregion 
#pragma region GettersAndSetters
const Rectf Wall::GetShape() const
{
	return m_Shape;
}

#pragma endregion 