#include "pch.h"
#include "Camera.h"
#include "HUD.h"
#include "Player.h"

Camera::Camera(const Player* player, float width, float height, float scaling)
	: m_pPlayer {player}
	, m_CamWidth{ width }
	, m_CamHeight{ height }
	, m_Scaling {scaling}
	, m_LevelBoundaries{ 0.f, 0.f, width, height }
	, m_InitialLevelBoundaries {0.f ,0.f, width, height}
	, m_CheckpointWallsX{2765.f, 5837.f, 7210.f, 7898.f, 8563.f, 9594.f, 10607.f, 11275.f, 11471.f}
	, m_Camera{ 0.f, 0.f, width, height }
	, m_IsOverWall {false}
{
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries, const std::vector<std::vector<Point2f>>& checkpointWalls)
{
	m_LevelBoundaries = m_InitialLevelBoundaries = levelBoundaries;
}

void Camera::Transform(const Rectf& target, bool isFacingLeft, bool areWallsGone)

{
	Point2f camPos{ Track(target).x - m_CamWidth / (2 * m_Scaling), Track(target).y - m_CamHeight / 4 };

	Clamp(camPos, target, isFacingLeft, areWallsGone);
	m_Camera.left = camPos.x;
	m_Camera.bottom = camPos.y;

	glTranslatef(-camPos.x, -camPos.y, 0);
}

Rectf Camera::GetCamera() const
{
	return m_Camera;
}

const Point2f Camera::Track(const Rectf& target) const
{
	return Point2f(target.left + (target.width / 2), target.bottom + (target.height));
}

void Camera::Clamp(Point2f& bottomLeftPos, const Rectf& target, bool isFacingLeft, bool areWallsGone)
{
	Vector2f camOffset{};

	m_LevelBoundaries.left = 0.f;

	(areWallsGone)
		? m_LevelBoundaries.width = m_InitialLevelBoundaries.width
		: m_LevelBoundaries.width = 9159.f;


	if (bottomLeftPos.x < 2640.f) // coords checkpoints voor safe file via loop van vectors?
	{
		camOffset.y = 0.f;
	}
	else if (bottomLeftPos.x >= 2640.f && bottomLeftPos.x < 7250.f)
	{
		camOffset.y = 78.f; 
	}
	else if (bottomLeftPos.x >= 7250 && bottomLeftPos.x < 8202.f)
	{
		camOffset.y = 321.f;
	}
	else if (bottomLeftPos.x >= 8202.f) // coords checkpoints voor safe file via loop van vectors?
	{
		camOffset.y = 273.f;
	}
	else if (bottomLeftPos.x >= 5834.f && bottomLeftPos.x < 7250.f && target.bottom + target.height > 0)
	{
		m_LevelBoundaries.left = 5834.f;
		camOffset.y = 78.f;
	}
	
	// camera clipping

	if (bottomLeftPos.x + m_CamWidth / m_Scaling >= m_LevelBoundaries.left +  m_LevelBoundaries.width)
	{
		bottomLeftPos.x = (m_LevelBoundaries.width - m_CamWidth / m_Scaling);
	}
	if (bottomLeftPos.x <= m_LevelBoundaries.left)
	{
		bottomLeftPos.x = m_LevelBoundaries.left;
	}
	if (bottomLeftPos.y + m_CamHeight / m_Scaling >= m_LevelBoundaries.bottom + m_LevelBoundaries.height)
	{
		bottomLeftPos.y = m_LevelBoundaries.height - m_CamHeight / m_Scaling;
	}
	if (bottomLeftPos.y <= m_LevelBoundaries.bottom + camOffset.y)
	{
		bottomLeftPos.y = m_LevelBoundaries.bottom + camOffset.y;
	}
}

