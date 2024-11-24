#pragma once
#include "Entity.h"
#include "Vector2f.h"
#include <map>

class PlayerStateMachine;
class PlayerIdleState;
class PlayerMoveState;
class PlayerData;
class PlayerState;
class AnimatedSprite;
class ObjectManager;
class EnemyManager;
class Level;
class Camera;
class Effects;
class SoundEffect;

class Player final : public Entity
{
public:

	enum class SpawnPoints
	{
		start, spawnpoint2, spawnpoint3, spawnpoint4, end
	};

	Player(EnemyManager* enemyManager, ObjectManager* objectManager, Level* level, const std::string& texturePath, const Rectf& shape, float horSpeed, float jumpSpeed);

	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
	Player(Player&& Player) = delete;
	Player& operator=(Player&& other) = delete;

	~Player();

	virtual void Update(float elapsedSec) override;
	virtual void UpdatePosition(float elapsedSec) override;

	// State functions

	void SetTransformTimer(float sec);
	void MovePlayer(float x, float y);

	//Player properties

	const int GetLives() const;
	void RemoveLife();
	void SetLives(int lives);
	
	void RemoveHeart();
	const int GetHearts() const;
	void SetHearts(int hearts);

	void AddScore(int points);
	const int GetScore() const;

	void AddCoins();
	const int GetCoinsCount() const;

	void SetFacingLeft(bool isFacingLeft);
	void SetVelocity(float x, float y);
	void SetGravity(float y);

	void SetHitEnemy(bool hitEnemy);
	bool GetIsEnemyHit() const;

	void SetCanBeHit(bool canBeHit);
	bool CheckCanBeHit() const;

	void SetCanTransform(bool canTransform);
	bool GetCanTransform() const;

	void SetIsTransformed(bool isTransformed);
	bool GetIsTransformed() const;

	void SetWallsGone(bool areWallsGone);

	SpawnPoints GetCurrentSpawnPoint();

	const Vector2f GetPlayerVelocity() const;

	bool GetWallsStatus();

	bool GetIsGameOver() const;
	void SetGameOver(bool isGameOver);

	const float GetJumpSpeed() const;
	const float GetHorizontalSpeed() const;

	// Player actions

	
	void SetJumping(bool isJumping);
	void TransformPlayer(float elapsedSec, float transformationTime);

	// checks

	bool IsLedge();

	void CheckDeath();

	// StateMachine

	PlayerStateMachine* GetStateMachine();
	PlayerState* GetPlayerState(const std::string& stateName);

	// Sprite Animation

	AnimatedSprite* GetSprite();

	// Effects
	Effects* GetEffect() const;

	// PlayerStates

	std::map<std::string, PlayerState* > m_pPlayerState;

	// SpawnPoints

	SpawnPoints m_CurrentSpawnPoint;


private:

	// updaters

	void UpdateGameObjects(float elapsedSec);
	void EnemyInteraction(float elapsedSec);
	void UpdateHitbox(float elapsedSec);
	void CheckSpawnPoints();

	//StateMachine 
	void InitializePlayerStates();

	// initialization

	void Initialize();
	virtual void SetupAnimations() override;

	// Player General Functions

	void RespawnPlayer();

	void SetSpriteSize(float size);
	bool IsTransformed();

	// cleanup

	void DeletePlayerStates();
	void DeleteSprite();

	// StateMachine

	PlayerStateMachine* m_pStateMachine;

	// Managers

	ObjectManager* m_pObjectManager;
	EnemyManager* m_pEnemyManager;

	//Player data

	PlayerData* m_pPlayerData; //todo voor zomer

	int m_Lives, m_Hearts,m_Score, m_Coins, m_Credits;

	bool m_IsGameOver;

	bool m_IsTransformed;
	bool m_CanTransform;
	bool m_IsDead;
	bool m_IsJumpKeyLocked;
	bool m_isPlatformActivated;


	float m_TransformationTimer;

	// Enemy data

	float m_TrapTimer;
	bool m_IsTrapActivated;

	bool m_HitEnemy;
	bool m_AreWallsGone;

	// audio

	SoundEffect* m_pGotHitSound;


};

