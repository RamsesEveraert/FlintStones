#include "pch.h"
#include "EnemyManager.h"
#include "MiniBoss.h"
#include "Snake.h"
#include "TransportShark.h"
#include "AggressiveShark.h"
#include "Pig.h"
#include "GreenBlop.h"
#include "Level.h"
#include "Piranha.h"

EnemyManager::EnemyManager(Level* level)
	: m_pLevel {level}
{
	m_pEnemies.reserve(70);
	InitializeEnemies();
}

EnemyManager::~EnemyManager()
{
	DeleteEnemies();
}

#pragma region GeneralFunctions
void EnemyManager::Draw(const Level& level) const
{
	for (Entity* pEnemy : m_pEnemies)
	{
		if (pEnemy)	pEnemy->Draw(level);
	}
}

void EnemyManager::Update(float elapsedSec, const Level& level)
{
	for (Entity* pEnemy : m_pEnemies)
	{
		if (pEnemy)	pEnemy->Update(elapsedSec);
	}
}


void EnemyManager::CreateEnemy(EnemyTypes type, Rectf shape, Vector2f speed, float activationDistance, float maxWalkDistance, int nrFrames, int fps, bool isFacingLeft)
{
	switch (type)
	{
	case EnemyTypes::blop:
		m_pEnemies.push_back(new GreenBlop(m_pLevel, shape, speed, maxWalkDistance, activationDistance, isFacingLeft));
		break;
	case EnemyTypes::pig:
		m_pEnemies.push_back(new Pig(m_pLevel, shape, speed, maxWalkDistance, activationDistance, isFacingLeft));
		break;
	case EnemyTypes::platformBird:
		m_pEnemies.push_back(new PlatformBird(m_pLevel, shape, speed, fps, maxWalkDistance, PlatformBird::BirdType::platform));
		break;
	case EnemyTypes::platformBirdLong:
		m_pEnemies.push_back(new PlatformBird(m_pLevel, shape, speed, fps, maxWalkDistance, PlatformBird::BirdType::platform_long));
		break;
	case EnemyTypes::PlatformTrapDown:
		m_pEnemies.push_back(new PlatformBird(m_pLevel, shape, speed, fps, maxWalkDistance, PlatformBird::BirdType::trap_down));
		break;
	case EnemyTypes::platformTrapUp:
		m_pEnemies.push_back(new PlatformBird(m_pLevel, shape, speed, fps, maxWalkDistance, PlatformBird::BirdType::trap_up));
		break;
	case EnemyTypes::snake:
		m_pEnemies.push_back(new Snake(m_pLevel, shape, speed, isFacingLeft));
		break;
	case EnemyTypes::transportShark:
		m_pEnemies.push_back(new TransportShark(m_pLevel, shape, speed, fps));
		break;
	case EnemyTypes::attackShark:
		m_pEnemies.push_back(new AggressiveShark(m_pLevel, shape, speed, fps));
		break;
	case EnemyTypes::miniboss:
		m_pEnemies.push_back(new MiniBoss(m_pLevel, shape, speed, fps, maxWalkDistance));
		break;
	case EnemyTypes::piranha:
		m_pEnemies.push_back(new Piranha(m_pLevel, shape, speed));
		break;
	}
}

#pragma endregion 
#pragma region GettersAndSetters
const size_t EnemyManager::GetContainerSize() const
{
	return  m_pEnemies.size();
}
const std::vector<Entity*> EnemyManager::GetEnemies() const
{
	return m_pEnemies;
}
#pragma endregion 
#pragma region CleanUp
void EnemyManager::InitializeEnemies()
{
	// 6 blops

	CreateEnemy(EnemyTypes::blop, Rectf{ 365.f, 61.f, 35.f, 22.f }, Vector2f{ 30.f, 0.f }, 100.f, 365.f, 3, 3);
	CreateEnemy(EnemyTypes::blop, Rectf{ 452.f, 61.f, 35.f, 22.f }, Vector2f{ 30.f, 0.f }, 100.f, 452.f, 3, 3);
	CreateEnemy(EnemyTypes::blop, Rectf{ 679.f, 61.f, 35.f, 22.f }, Vector2f{ 30.f, 0.f }, 100.f, 300.f, 3, 3);
	CreateEnemy(EnemyTypes::blop, Rectf{ 6845.f, 475.f, 35.f, 22.f }, Vector2f{ 30.f, 0.f }, 100.f, 160.f, 3, 3);
	CreateEnemy(EnemyTypes::blop, Rectf{ 7245.f, 475.f, 35.f, 22.f }, Vector2f{ 30.f, 0.f }, 100.f, 160.f, 3, 3);
	CreateEnemy(EnemyTypes::blop, Rectf{ 7836.f, 495.f, 35.f, 22.f }, Vector2f{ 30.f, 0.f }, 100.f, 50.f, 3, 3);

	// 2 pigs

	CreateEnemy(EnemyTypes::pig, Rectf{ 795.f, 61.f, 50.f, 36.f }, Vector2f{ 120.f, 0.f }, 50.f, 750.f, 3, 3);
	CreateEnemy(EnemyTypes::pig, Rectf{ 7249.f, 4664.f, 50.f, 36.f }, Vector2f{ 120.f, 0.f }, 100.f, 750.f, 3, 3);

	//9 birds

	CreateEnemy(EnemyTypes::platformBird, Rectf{ 1129.f,230.f, 52.f, 100.f }, Vector2f{ 0.022f, 0.f }, 50.f, 60.f, 3, 6);
	CreateEnemy(EnemyTypes::platformBird, Rectf{ 1283.f,205.f, 52.f, 100.f }, Vector2f{ 0.010f, 0.f }, 50.f, 30.f, 3, 6);
	CreateEnemy(EnemyTypes::PlatformTrapDown, Rectf{ 6637.f,502.f, 52.f, 100.f }, Vector2f{ 0.010f, 0.f }, 50.f, 30.f, 3, 6);
	CreateEnemy(EnemyTypes::platformTrapUp, Rectf{ 7040.f,150.f, 52.f, 100.f }, Vector2f{ 0.010f, 0.f }, 50.f, 30.f, 3, 6);
	CreateEnemy(EnemyTypes::platformTrapUp, Rectf{ 7463.f,463.f, 52.f, 100.f }, Vector2f{ 0.010f, 0.f }, 50.f, 30.f, 3, 6);
	CreateEnemy(EnemyTypes::PlatformTrapDown, Rectf{ 7639.f,467.f, 52.f, 100.f }, Vector2f{ 0.010f, 0.f }, 50.f, 30.f, 3, 6);
	CreateEnemy(EnemyTypes::platformTrapUp, Rectf{ 9412.f,304.f, 52.f, 100.f }, Vector2f{ 0.010f, 0.f }, 50.f, 30.f, 3, 6);
	CreateEnemy(EnemyTypes::PlatformTrapDown, Rectf{ 10848.f,526.f, 52.f, 100.f }, Vector2f{ 0.010f, 0.f }, 50.f, 30.f, 3, 6);
	CreateEnemy(EnemyTypes::platformBirdLong, Rectf{ 10040.f,334.f, 52.f, 200.f }, Vector2f{ 0.014f, 0.f }, 50.f, 45.f, 3, 6);

	// 9 snakes

	CreateEnemy(EnemyTypes::snake, Rectf{ 2462.f,278.f, 116.f, 39.f }, Vector2f{ 25.f, 0.f }, 50.f, 750.f, 2, 4, true );
	CreateEnemy(EnemyTypes::snake, Rectf{ 2462.f,380.f, 116.f, 39.f }, Vector2f{ 25.f, 0.f }, 50.f, 750.f, 2, 4, true );
	CreateEnemy(EnemyTypes::snake, Rectf{ 2462.f,471.f, 116.f, 39.f }, Vector2f{ 25.f, 0.f }, 50.f, 750.f, 2, 4, true );
	CreateEnemy(EnemyTypes::snake, Rectf{ 2223.f,331.f, 116.f, 39.f }, Vector2f{ 25.f, 0.f }, 50.f, 750.f, 2, 4, false );
	CreateEnemy(EnemyTypes::snake, Rectf{ 2223.f,425.f, 116.f, 39.f }, Vector2f{ 25.f, 0.f }, 50.f, 750.f, 2, 4, false );
	CreateEnemy(EnemyTypes::snake, Rectf{ 10444,336.f, 116.f, 39.f }, Vector2f{ 25.f, 0.f }, 50.f, 750.f, 2, 4, true );
	CreateEnemy(EnemyTypes::snake, Rectf{ 10474.f,384.f, 116.f, 39.f }, Vector2f{ 25.f, 0.f }, 50.f, 750.f, 2, 4, true );
	CreateEnemy(EnemyTypes::snake, Rectf{ 10506.f,432.f, 116.f, 39.f }, Vector2f{ 25.f, 0.f }, 50.f, 750.f, 2, 4, true );
	CreateEnemy(EnemyTypes::snake, Rectf{ 10538.f,481.f, 116.f, 39.f }, Vector2f{ 25.f, 0.f }, 50.f, 750.f, 2, 4, true );

	//1 miniboss

	CreateEnemy(EnemyTypes::miniboss, Rectf{ 8947.f,304.f, 130.f, 60.f }, Vector2f{ -90.f, 0.f }, 100.f, 25.f, 3, 9);

	// 2 sharks

	CreateEnemy(EnemyTypes::transportShark, Rectf{ 3470.f,93.f, 95.f, 65.f }, Vector2f{ 300.f, 0.f }, 100.f, 25.f, 2, 4, false);
	//CreateEnemy(EnemyTypes::attackShark, Rectf{ 4684.f,93.f, 95.f, 65.f }, Vector2f{ -300.f, 0.f }, 100.f, 25.f, 2, 4, true);  // TODO

	// 12 piranhas

	CreateEnemy(EnemyTypes::piranha, Rectf{ 3660.f,-34.f,34.f,34.f }, Vector2f{ 150.f, utils::GetRandomNumber(100, 200, true) }, 100.f, 25.f, 2, 4);
	CreateEnemy(EnemyTypes::piranha, Rectf{ 3748.f,-34.f,34.f,34.f }, Vector2f{ 150.f, utils::GetRandomNumber(100, 200, true) }, 100.f, 25.f, 2, 4);
	CreateEnemy(EnemyTypes::piranha, Rectf{ 3807.f,-34.f,34.f,34.f }, Vector2f{ 150.f, utils::GetRandomNumber(100, 200, true) }, 100.f, 25.f, 2, 4);
	CreateEnemy(EnemyTypes::piranha, Rectf{ 3981.f,-34.f,34.f,34.f }, Vector2f{ 150.f, utils::GetRandomNumber(100, 200, true) }, 100.f, 25.f, 2, 4);
	CreateEnemy(EnemyTypes::piranha, Rectf{ 4171.f,-34.f,34.f,34.f }, Vector2f{ 150.f, utils::GetRandomNumber(100, 200, true) }, 100.f, 25.f, 2, 4);
	CreateEnemy(EnemyTypes::piranha, Rectf{ 4268.f,-34.f,34.f,34.f }, Vector2f{ 150.f, utils::GetRandomNumber(100, 200, true) }, 100.f, 25.f, 2, 4);
	CreateEnemy(EnemyTypes::piranha, Rectf{ 4504.f,-34.f,34.f,34.f }, Vector2f{ 150.f, utils::GetRandomNumber(100, 200, true) }, 100.f, 25.f, 2, 4);
	CreateEnemy(EnemyTypes::piranha, Rectf{ 4700.f,-34.f,34.f,34.f }, Vector2f{ 150.f, utils::GetRandomNumber(100, 200, true) }, 100.f, 25.f, 2, 4);
	CreateEnemy(EnemyTypes::piranha, Rectf{ 4864.f,-34.f,34.f,34.f }, Vector2f{ 150.f, utils::GetRandomNumber(100, 200, true) }, 100.f, 25.f, 2, 4);
	CreateEnemy(EnemyTypes::piranha, Rectf{ 5074.f,-34.f,34.f,34.f }, Vector2f{ 150.f, utils::GetRandomNumber(100, 200, true) }, 100.f, 25.f, 2, 4);
	CreateEnemy(EnemyTypes::piranha, Rectf{ 5141.f,-34.f,34.f,34.f }, Vector2f{ 150.f, utils::GetRandomNumber(100, 200, true) }, 100.f, 25.f, 2, 4);
	CreateEnemy(EnemyTypes::piranha, Rectf{ 5544.f,-34.f,34.f,34.f }, Vector2f{ 150.f, utils::GetRandomNumber(100, 200, true) }, 100.f, 25.f, 2, 4);

}
void EnemyManager::DeleteEnemies()
{
	for (Entity* pEnemy : m_pEnemies)
	{
		if (pEnemy)
		{
			delete pEnemy;
			pEnemy = nullptr;
		}
	}
	m_pEnemies.clear();
}
#pragma endregion 









