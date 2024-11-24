#pragma once
#include "Vector2f.h"
#include <vector>

class Logs;
class StageBlocks;
class Entity;

class PlatformManager
{
public:

	PlatformManager();

	PlatformManager(const PlatformManager& other) = delete;
	PlatformManager& operator=(const PlatformManager& other) = delete;
	PlatformManager(PlatformManager&& other) = delete;
	PlatformManager& operator=(PlatformManager&& other) = delete;

	~PlatformManager();

	void DrawLogs() const;
	void DrawFloorBlocks() const;

	void Update(float elapsedSec);

	bool IsOnGround(Entity& entity) const;
	bool CheckWallHit(Entity& entity) const;
	bool HitLedge(Entity& entity) const;

private:

	void HandleCollision(Entity& entity)const;
	
	void CreatePlatformVertices();
	void CreateLogs();
	void CreateFloorBlocks();

	void UpdateLogs(float elapsedSec);
	void UpdateFloorBlocks(float elapsedSec);

	void DeleteLogs();
	void DeleteFloorBlocks();

	const int m_AmountFloorBlocks;

	std::vector<std::vector<Point2f>>m_VerticesPlatforms;
	std::vector<Logs*>m_pLogs;
	std::vector<StageBlocks*>m_pFloorBlocks;

};

