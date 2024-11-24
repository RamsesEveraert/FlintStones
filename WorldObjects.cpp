#include "pch.h"
#include "WorldObjects.h"
#include "AnimatedSprite.h"


WorldObjects::WorldObjects(const Point2f& centre, float spriteW, float spriteH, int nrFrames)
	: m_SpriteWidth { spriteW }
	, m_SpriteHeight { spriteH }
	, m_Shape { centre.x - (m_SpriteWidth / 2) , centre.y - (m_SpriteHeight / 2), m_SpriteWidth, m_SpriteHeight }
	, m_NrFrames { nrFrames}
	, m_pSprite {}
{
}

WorldObjects::~WorldObjects()
{
	DeleteObject();
}

#pragma region Initialization
void WorldObjects::CreateObject(const std::string& animName, float spriteRowBottom, int fps)
{
	m_pSprite = new AnimatedSprite("Resources/Objects/Objects.png", m_Shape.width, m_Shape.height);
	m_pSprite->SetFramesPerSec(fps);
	m_pSprite->AddAnimation(animName, 0.f, spriteRowBottom, m_Shape.width, m_Shape.height, m_NrFrames);
	m_pSprite->PlayAnimation(animName);
}
#pragma endregion 
#pragma region GeneralFunctions
void WorldObjects::Draw() const
{
	m_pSprite->Draw();
}

void WorldObjects::Update(float elapsedSec)
{
	UpdateObject(elapsedSec);
}
void WorldObjects::UpdateObject(float elapsedSec)
{
	m_pSprite->Update(elapsedSec, m_Shape);
}

void WorldObjects::AddObjectAnimation(const std::string& animName, float spriteRowBottom, int fps)
{
	m_pSprite->AddAnimation("animName", 0.f, spriteRowBottom, m_Shape.width, m_Shape.height, m_NrFrames);
}
bool WorldObjects::IsOverlapping(const Rectf& rect) const
{
	if (utils::IsOverlapping(rect, m_Shape))
	{
		return true;
	}
	return false;
}
#pragma endregion 
#pragma region GettersAndSetters
void WorldObjects::SetObjectAnimation(const std::string& animName)
{
	m_pSprite->PlayAnimation("animName");
}
Rectf WorldObjects::GetShape() const
{
	Rectf center = m_Shape;
	center.left = m_Shape.left + (m_SpriteWidth / 2);
	center.bottom = m_Shape.bottom + (m_SpriteHeight / 2);

	return center;
}

#pragma endregion 
#pragma region CleanUp
void WorldObjects::DeleteObject()
{
	delete m_pSprite;
	m_pSprite = nullptr;
}
#pragma endregion 