#pragma once
#include <vector>
#include "Vector2f.h"

class Texture;
class PlatformManager;
class AnimatedSprite;
class Entity;
class Wall;

class Level final
{
public:

	Level();

	Level(const Level& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(Level&& other) = delete;

	~Level();

	void Draw()const;
	void DrawForeGround() const;
	void DrawRaycast(const Rectf& entityShape) const; // Temporary

	void Update(float elapsedSec);
	void HandleCollision( Entity& entity) const;

	template<typename T>
	T Lerp(T a, T b, float t) const ;

	void HandleSlope(Entity& entity);

	bool CheckIsOnGround(Entity& entity) const;
	bool HitPlatformLedge(Entity& entity) const;

	Rectf GetBoundaries() const;
	std::vector<std::vector<Point2f>> GetCheckpointWalls() const;

	void DeleteWall(float elapsedSec, Entity& entity);
	bool AreWallsGone() const;

private:


	//**********  FUNCTIONS  **********//

	std::vector <Wall*> GetWalls() const;

	bool CheckHitCeiling(Entity& entity) const;
	bool CheckWallHit(Entity& entity) const;
	
	void CreateStageVertices();
	void CreateCheckpointWalls();
	void CreateStartSign();
	void CreateSpawnPoints();
	void CreateMovingWater();
	void CreateWaterfall();
	void CreateFoam();
	void CreateWalls();

	void DrawSpawnPoints() const;
	void DrawMovingWater() const;
	void DrawFoam() const;
	void DrawWaterfall() const;
	void DrawWalls() const;

	void UpdateMovingWater(float elapsedSec);
	void UpdateWaterfall(float elapsedSec);
	void UpdatePlatforms(float elapsedSec);
	void UpdateFoam(float elapsedSec);
	void UpdateWall(float elapsedSec);


	void CleanUp();

	void DeleteStageTextures();
	void DeletePlatforms();
	void DeleteStartSign();
	void DeleteSpawnPoints();
	void DeleteMovingWater();
	void DeleteWaterfall(); 
	void DeleteFoam();
	void DeleteWalls();

	//********* DATA MEMBERS  ***************//

	// Level properties

	std::vector<std::vector<Point2f>> m_VerticesSurface;
	Texture *m_pStage, *m_pStartSign, *m_pSpawnPoints, *m_pForeGround, *m_pWaterfall;
	AnimatedSprite *m_pBottomFoam,  *m_pTopFoam;

	// camera properties

	Rectf m_Boundaries;
	std::vector<std::vector<Point2f>> m_CheckPointWalls; 

	// Wall properties

	bool m_AreWallsGone;
	int m_WallCount;
	std::vector <Wall*> m_pWalls;

	// Platform

	PlatformManager* m_pPlatforms;

	//startsign:

	Rectf m_DstStartSign, m_SrcStartSign;

	//spawnpoints

	std::vector<Rectf> m_SrcSpawns, m_DstSpawns;

	// moving water
	const int m_NeededSprites;
	std::vector<AnimatedSprite*> m_pMovingWaterTop, m_pMovingWaterBottom;

	std::vector<Rectf> m_DstWaterfall;
	Point2f m_BlWaterfall; 
};

template<typename T>
inline T Level::Lerp(T a, T b, float t) const 
{
	return a + (b - a) * t;
}
