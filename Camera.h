#pragma once
#include "pch.h"

class HUD;
class Player;

class Camera final
{
public:
	Camera(const Player* player, float width, float height, float scaling);
	~Camera() = default;

	void SetLevelBoundaries(const Rectf& levelBoundaries, const std::vector<std::vector<Point2f>>& checkpointWalls);
	void Transform(const Rectf& target, bool isFacingLeft, bool areWallsGone);

	Rectf GetCamera() const;

private:

	const Point2f Track(const Rectf& target) const ;
	void Clamp(Point2f& bottomLeftPos, const Rectf& target, bool isFacingLeft, bool areWallsGone);

	const float m_CamWidth, m_CamHeight, m_Scaling;

	bool m_IsOverWall;

	Rectf m_LevelBoundaries, m_InitialLevelBoundaries;

	std::vector<float> m_CheckpointWallsX;

	Rectf m_Camera;

	const Player* m_pPlayer;
	const HUD* m_pHUD;

};

