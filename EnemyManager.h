#pragma once

#include "PlatformBird.h"

class Entity;
class Level;

class EnemyManager
{
public:

	enum class EnemyTypes
	{
		blop, platformBird, platformBirdLong, PlatformTrapDown, platformTrapUp, pig, snake, attackShark, transportShark, miniboss, piranha
	};

	EnemyManager(Level* level);

	EnemyManager(const EnemyManager& other) = delete;
	EnemyManager& operator=(const EnemyManager& other) = delete;
	EnemyManager(EnemyManager&& other) = delete;
	EnemyManager& operator=(EnemyManager&& other) = delete;

	~EnemyManager();

	void Draw(const Level& level) const;
	void Update(float elapsedSec, const Level& level);

	const size_t GetContainerSize() const;
	const std::vector<Entity*> GetEnemies() const;

	void CreateEnemy(EnemyTypes type, Rectf shape, Vector2f speed, float activationDistance, float maxWalkDistance, int nrFrames, int fps, bool isFacingLeft = true);

private:

	void InitializeEnemies();
	void DeleteEnemies();

	Level* m_pLevel;
	std::vector<Entity*> m_pEnemies;
};

