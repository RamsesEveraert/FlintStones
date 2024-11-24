#include "pch.h"
#include "StageBlocks.h"
#include "AnimatedSprite.h"

StageBlocks::StageBlocks(const Rectf& shape)
	: m_pFloorBlock {new AnimatedSprite("Resources/Objects/FloorBlock.png",shape.width, shape.height)}
	, m_Shape{shape}
{
	StageBlocks::SetupAnimations();
}

StageBlocks::~StageBlocks()
{
	delete m_pFloorBlock;
	m_pFloorBlock = nullptr;
}

#pragma region Initialization
void StageBlocks::SetupAnimations() const
{
	m_pFloorBlock->AddAnimation("Floor", 0.f, 0.f, m_Shape.width, m_Shape.height, 1);
	m_pFloorBlock->PlayAnimation("Floor");
}
#pragma endregion 
#pragma region General Functions
void StageBlocks::Update(float elapsedSec)
{
	m_pFloorBlock->Update(elapsedSec, m_Shape);
}
void StageBlocks::Draw() const
{
	m_pFloorBlock->Draw();
}
#pragma endregion 
#pragma region GettersAndSetters
const Rectf StageBlocks::GetShape() const
{
	return m_Shape;
}
#pragma endregion 