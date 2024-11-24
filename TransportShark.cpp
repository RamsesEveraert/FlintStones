#include "pch.h"
#include "TransportShark.h"

TransportShark::TransportShark(Level* level, const Rectf& shape, const Vector2f& speed, int fps)
	: Shark(level, shape, speed, fps)
{

}

void TransportShark::UpdatePosition(Entity& entity, float elapsedSec)
{
	MoveShark(entity, elapsedSec);
	Shark::UpdatePosition(entity, elapsedSec);
}

void TransportShark::Update(float elapsedSec)
{
	UpdateAnimations(elapsedSec);
	Shark::Update(elapsedSec);
}

void TransportShark::MoveShark(Entity& entity, float elapsedSec)
{
	const float endWaterGap{ 4550.f };
	const float endDistance{ 100.f };
	const float disappearSpeed{ 40.f };

	Shark::ResetShark(entity);

	(entity.GetShape().left >= m_Shape.left && entity.GetShape().left <= endWaterGap)
		? entity.SetParent(this)
		: entity.SetParent(nullptr);

	if (entity.GetShape().bottom == m_Shape.bottom + m_PlatformOffset.y)
		m_Velocity.x = m_HorSpeed;

	if (m_Shape.left >= endWaterGap - endDistance)
	{
		m_Velocity.x = disappearSpeed;
		m_Velocity.y = -disappearSpeed;
	}


}

void TransportShark::UpdateAnimations(float elapsedSec)
{
	Shark::UpdateAnimations(elapsedSec);
}