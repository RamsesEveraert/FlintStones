#include "pch.h"
#include "Logs.h"
#include "AnimatedSprite.h"

Logs::Logs(const Rectf& shape, float speed)
	: m_Log{ new AnimatedSprite("Resources/Objects/Logs.png",shape.width,shape.height)}
	, m_Velocity{ 0.f, -speed }
	, m_Shape { shape }
{
	Logs::SetupAnimation();
}

Logs::~Logs()
{
	delete m_Log;
	m_Log = nullptr;
}

#pragma region Initialization
void Logs::SetupAnimation() const
{
	m_Log->AddAnimation("FallingLogs", 0.f, 0.f, m_Shape.width, m_Shape.height, 2);
	m_Log->SetFramesPerSec(6);
	m_Log->PlayAnimation("FallingLogs");
}
#pragma endregion 
#pragma region GeneralFunctions
void Logs::Draw() const
{
	m_Log->Draw();
}

void Logs::Update(float elapsedSec)
{
	m_Log->Update(elapsedSec, m_Shape);
	Logs::MovingLogs(elapsedSec);
}
void Logs::MovingLogs(float elapsedSec)
{
	const float BottomWaterfall{ 109.f };
	const float TopWaterfall{ 487.f };

	if (m_Shape.bottom + m_Shape.height <= BottomWaterfall)
	{
		m_Shape.bottom = TopWaterfall - m_Shape.height;
	}

	m_Shape.bottom += m_Velocity.y * elapsedSec;
}
#pragma endregion 
#pragma region GettersAndSetters
Rectf Logs::GetShape() const
{
	return m_Shape;
}
Vector2f Logs::GetVelocity() const
{
	return m_Velocity;
}
#pragma endregion 