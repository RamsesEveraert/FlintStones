#include "pch.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "PlayerState.h"
#include "PlayerData.h"
#include "PlayerIdleState.h"
#include "PlayerMoveState.h"
#include "PlayerLandState.h"
#include "PlayerInAirState.h"
#include "PlayerJumpState.h"
#include "PlayerSlideState.h"
#include "PlayerCrouchState.h"
#include "PlayerLedgeHangState.h"
#include "PlayerLedgeClimbState.h"
#include "PlayerChargingState.h"
#include "PlayerAttackState.h"
#include "PlayerChargedMoveState.h"
#include "PlayerSlopeRunState.h"
#include "PlayerTransformedState.h"
#include "PlayerTransformIdleState.h"
#include "PlayerTransformMoveState.h"
#include "PlayerTransformFlyState.h"
#include "PlayerTransformAttackState.h"
#include "AnimatedSprite.h"
#include "Level.h"
#include "Camera.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "Entity.h"
#include "MiniBoss.h"
#include "Shark.h"
#include "TransportShark.h"
#include "AggressiveShark.h"
#include "Snake.h"
#include "PlatformBird.h"
#include "GreenBlop.h"
#include "Pig.h"
#include "Piranha.h"
#include "Egg.h"
#include "Effects.h"
#include "Logs.h"
#include "SoundEffect.h"


Player::Player(EnemyManager* enemyManager, ObjectManager* objectManager, Level* level, const std::string& texturePath, const Rectf& shape, float horSpeed, float jumpSpeed)
	: Entity(level, texturePath, shape, horSpeed, jumpSpeed)
	, m_IsTransformed{ false }
	, m_CanTransform  { false }
	, m_IsDead{ false }
	, m_IsJumpKeyLocked{ false }
	, m_pObjectManager{ objectManager }
	, m_pEnemyManager{ enemyManager }
	, m_CurrentSpawnPoint{ SpawnPoints::start }
	, m_TrapTimer{}
	, m_IsTrapActivated{ false }
	, m_AreWallsGone{ false }
	, m_HitEnemy{ false }
	, m_IsGameOver { false }
	, m_isPlatformActivated { false }
	, m_TransformationTimer {}
	, m_Lives {0}
	, m_Hearts {6}
	, m_Coins {0}
	, m_Score {0}
	, m_Credits {0}
	, m_pGotHitSound{ new SoundEffect("Resources/Audio/Flintstones_Player_Hit.wav") }


{
	Initialize();
}

Player::~Player()
{
	DeleteSprite();
	DeletePlayerStates();
	delete m_pStateMachine;
	delete m_pGotHitSound;
}


void Player::Update(float elapsedSec)
{
		CheckDeath();
		
		PlayerState* currentState{ m_pStateMachine->GetCurrentState() };

		if (m_Velocity.y < 0 && !m_IsTransformed && currentState != m_pPlayerState["Idle"] && currentState != m_pPlayerState["InAir"] && currentState != m_pPlayerState["Attack"])
		{
			m_pStateMachine->ChangeState(m_pPlayerState["InAir"]);
		}			

		if (m_IsTransformed && currentState != m_pPlayerState["TransformFly"] && m_Velocity.y != 0)
		{
			m_pStateMachine->ChangeState(m_pPlayerState["TransformFly"]);
		}
			
		if (currentState == m_pPlayerState["LedgeHang"] && m_MovingLog && m_Shape.bottom <= 141.f)
		{
			m_pStateMachine->ChangeState(m_pPlayerState["Idle"]);
		}


		TransformPlayer(elapsedSec, 20.f);


		m_pStateMachine->GetCurrentState()->LogicUpdate(elapsedSec);
		m_pStateMachine->GetCurrentState()->PhysicsUpdate(elapsedSec);

		UpdateHitbox(elapsedSec);
		UpdateGameObjects(elapsedSec);

		UpdatePosition(elapsedSec);
		
		m_pEffect->Update(elapsedSec, *this);
		CheckSpawnPoints();
		
		if (m_Shape.bottom + m_Shape.height <= 0.f || m_Hearts == 0)
		{
			RespawnPlayer();
		}

		m_pSprite->Update(elapsedSec, m_Shape);
}

void Player::UpdatePosition(float elapsedSec)
{
	m_Velocity.y += m_GravityAcceleration.y * elapsedSec;
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;

	Player::EnemyInteraction(elapsedSec);

	if (m_pParent)
	{
		m_Shape.left += m_pParent->GetVelocity().x * elapsedSec;
		m_Shape.bottom += m_pParent->GetVelocity().y * elapsedSec;
	}
	if (m_MovingLog)
	{
		m_Shape.left += m_MovingLog->GetVelocity().x * elapsedSec;
		m_Shape.bottom += m_MovingLog->GetVelocity().y * elapsedSec;
	}

	m_pLevel->HandleCollision(*this);

	
}

// SetupAnimation data lezen from file - binnenkort

#pragma region Updaters
void Player::RespawnPlayer()
{
	m_Hearts = 3;

	(m_Lives > 0)
		? --m_Lives
		: m_IsGameOver = true;


	std::cout << "lives: " << m_Lives << std::endl;

	m_Shape.left = 140.f;
	m_Shape.bottom = 60.f;
}

void Player::UpdateGameObjects(float elapsedSec)
{	
	m_pObjectManager->HitItem(*this);
	m_pObjectManager->Update(elapsedSec);
}
void Player::UpdateHitbox(float elapsedSec)
{
	m_Hitbox.left = m_Shape.left + (m_Shape.width / 4);
	m_Hitbox.bottom = m_Shape.bottom;
	m_Hitbox.width = m_Shape.width / 2;
	m_Hitbox.height = 3.f * (m_Shape.height / 4);
}
#pragma endregion
#pragma region StateMachine
void Player::InitializePlayerStates()
{
	m_pPlayerState.insert(std::make_pair("Idle", new PlayerIdleState(this, m_pStateMachine, m_pPlayerData, "Idle"))).second;
	m_pPlayerState.insert(std::make_pair("Moving", new PlayerMoveState(this, m_pStateMachine, m_pPlayerData, "Running"))).second;

	m_pPlayerState.insert(std::make_pair("JumpState", new PlayerJumpState(this, m_pStateMachine, m_pPlayerData, "Jumping"))).second;
	m_pPlayerState.insert(std::make_pair("InAir", new PlayerInAirState(this, m_pStateMachine, m_pPlayerData, "Falling"))).second;
	m_pPlayerState.insert(std::make_pair("LandState", new PlayerLandState(this, m_pStateMachine, m_pPlayerData, "Idle"))).second;
	m_pPlayerState.insert(std::make_pair("Slide", new PlayerSlideState(this, m_pStateMachine, m_pPlayerData, "Sliding"))).second;
	m_pPlayerState.insert(std::make_pair("Crough", new PlayerCrouchState(this, m_pStateMachine, m_pPlayerData, "Crough"))).second;
	m_pPlayerState.insert(std::make_pair("LedgeHang", new PlayerLedgeHangState(this, m_pStateMachine, m_pPlayerData, "Swinging"))).second;
	m_pPlayerState.insert(std::make_pair("LedgeClimb", new PlayerLedgeClimbState(this, m_pStateMachine, m_pPlayerData, "Climbing"))).second;
	m_pPlayerState.insert(std::make_pair("Charging", new PlayerChargingState(this, m_pStateMachine, m_pPlayerData, "Charging"))).second;
	m_pPlayerState.insert(std::make_pair("ChargedMove", new PlayerChargedMoveState(this, m_pStateMachine, m_pPlayerData, "ChargedRunning"))).second;
	m_pPlayerState.insert(std::make_pair("Attack", new PlayerAttackState(this, m_pStateMachine, m_pPlayerData, "Attack"))).second;
	m_pPlayerState.insert(std::make_pair("SlopeRun", new PlayerSlopeRunState(this, m_pStateMachine, m_pPlayerData, "SlopeRun"))).second;

	m_pPlayerState.insert(std::make_pair("TransformIdle", new PlayerTransformIdleState(this, m_pStateMachine, m_pPlayerData, "BirdIdle"))).second;
	m_pPlayerState.insert(std::make_pair("TransformWalk", new PlayerTransformMoveState(this, m_pStateMachine, m_pPlayerData, "BirdWalk"))).second;
	m_pPlayerState.insert(std::make_pair("TransformAttack", new PlayerTransformAttackState(this, m_pStateMachine, m_pPlayerData, "BirdWalkShoot"))).second;
	m_pPlayerState.insert(std::make_pair("TransformFly", new PlayerTransformFlyState(this, m_pStateMachine, m_pPlayerData, "BirdFly"))).second;
}
void Player::Initialize()
{
	m_IsPlayer = true;
	SetupAnimations();
	m_pStateMachine = new PlayerStateMachine();
	InitializePlayerStates();
	m_pStateMachine->Initialize(m_pPlayerState["Idle"]);
	m_pGotHitSound->SetVolume(50);

}
void Player::SetupAnimations()
{
	const float spriteSizeGeneral{ 50.f };
	const float spriteSizeAtack{ 55.f };
	const float spriteSizeTransformedW{ 62.f };
	const float spriteSizeTransformedH{ 50.f };

	//stills
	m_pSprite->AddAnimation("Idle", 0, 0, spriteSizeGeneral, spriteSizeGeneral, 1);
	m_pSprite->AddAnimation("StayDown", 50.f, 0, spriteSizeGeneral, spriteSizeGeneral, 1);
	m_pSprite->AddAnimation("Jumping", 0, 350.f, spriteSizeGeneral, spriteSizeGeneral, 1);
	m_pSprite->AddAnimation("Falling", 50.f, 350.f, spriteSizeGeneral, spriteSizeGeneral, 1);
	m_pSprite->AddAnimation("EndSlide", 300, 50, spriteSizeGeneral, spriteSizeGeneral, 1);
	m_pSprite->AddAnimation("Pause", 0, 768, 40.f, 50.f, 1);


	// Animations Normal
	m_pSprite->AddAnimation("Crough", 0, 0, spriteSizeGeneral, spriteSizeGeneral, 3);
	m_pSprite->AddAnimation("Running", 0, 50, spriteSizeGeneral, spriteSizeGeneral, 6);
	m_pSprite->AddAnimation("ChargedRunning", 0, 100, spriteSizeGeneral, spriteSizeGeneral, 6);
	m_pSprite->AddAnimation("Sliding", 0, 150, spriteSizeGeneral, spriteSizeGeneral, 6);
	m_pSprite->AddAnimation("Swinging", 0, 200, spriteSizeGeneral, spriteSizeGeneral, 3);
	m_pSprite->AddAnimation("Climbing", 0, 250, spriteSizeGeneral, spriteSizeGeneral, 3);
	m_pSprite->AddAnimation("SlopeRun", 0, 150, spriteSizeGeneral, spriteSizeGeneral, 6);

	m_pSprite->AddAnimation("Attack", 110, 400, spriteSizeAtack, spriteSizeAtack, 2);
	m_pSprite->AddAnimation("Charging", 0, 400, spriteSizeAtack, spriteSizeAtack, 2);

	m_pSprite->AddAnimation("Dancing", 0, 300, spriteSizeGeneral, spriteSizeGeneral, 2);
	
	// Animations Transformed
	m_pSprite->AddAnimation("BirdIdle", 0, 455, spriteSizeTransformedW, spriteSizeTransformedH, 1);
	m_pSprite->AddAnimation("BirdShoot", 50.f, 455, spriteSizeTransformedW, spriteSizeTransformedH, 1);
	m_pSprite->AddAnimation("BirdFly", 0, 585, spriteSizeTransformedW, spriteSizeTransformedH, 3);
	m_pSprite->AddAnimation("BirdFlyShoot", 0, 520, spriteSizeTransformedW, spriteSizeTransformedH, 2);
	m_pSprite->AddAnimation("BirdWalk", 0, 650, spriteSizeTransformedW, spriteSizeTransformedH, 2);
	m_pSprite->AddAnimation("BirdWalkShoot", 2.f, 715, spriteSizeTransformedW, spriteSizeTransformedH, 2);
} // mag blijven in player class (later inlezen met tekstfile)
#pragma endregion
#pragma region Actions
void Player::EnemyInteraction(float elapsedSec)
{

	//*******   Slecht gecoded, tijd te kort, wordt improved  **************//

	if (m_IsStunned) Entity::StartStunTimer(elapsedSec);

	for (Entity* pEntity : m_pEnemyManager->GetEnemies())
	{
		GreenBlop* pBlop = dynamic_cast<GreenBlop*>(pEntity);
		Pig* pPig = dynamic_cast<Pig*>(pEntity);
		PlatformBird* pBird = dynamic_cast<PlatformBird*>(pEntity);
		Snake* pSnake = dynamic_cast<Snake*>(pEntity);
		TransportShark* pTShark = dynamic_cast<TransportShark*>(pEntity);
		AggressiveShark* pAShark = dynamic_cast<AggressiveShark*>(pEntity);
		MiniBoss* pMini = dynamic_cast<MiniBoss*>(pEntity);
		Piranha* pPiranha = dynamic_cast<Piranha*>(pEntity);

		if (pEntity->HandleCollision(*this) && m_Velocity.x == 0)
		{
			if (m_pStateMachine->GetCurrentState() == m_pPlayerState["InAir"] || (m_pStateMachine->GetCurrentState() == m_pPlayerState["JumpState"]))
			{
				m_pStateMachine->ChangeState(m_pPlayerState["Idle"]);
			}
			if (pBird)
			{
				if (pBird->GetBirdType() == PlatformBird::BirdType::trap_down)
				{
					m_TrapTimer += elapsedSec;

					if (m_TrapTimer > 0.2f)
					{
						pBird->DropPlatform(*this);
						m_TrapTimer = 0;
					}
					break;
				}

				if (pBird->GetBirdType() == PlatformBird::BirdType::trap_up)
				{
					m_TrapTimer += elapsedSec;

					if (m_TrapTimer > 0.3f)
					{
						pBird->ShootPlatform(*this);
						m_TrapTimer = 0;
					}
					break;
				}
				break;
			}
		}



		if ((pPig || pBlop) && utils::IsOverlapping(m_Hitbox, pEntity->GetShape()))
		{
			if (m_pStateMachine->GetCurrentState() != m_pPlayerState["Attack"] && !pEntity->CheckIsStunned() && !pEntity->CheckIsDead())
			{

				if (m_Hearts > 0 && !m_IsInvinsible)
				{
					Player::RemoveHeart();

					m_pGotHitSound->Play(0);

					m_IsInvinsible = true;
					m_IsStunned = true;

				}

			}
		}

		

		if ((pPig || pBlop || pSnake) && utils::IsOverlapping(m_Shape, pEntity->GetShape()))
		{
			Rectf hitboxEntity{ pEntity->GetShape() };

			if /*(!pSnake->CheckIsStunned() &&*/(m_pStateMachine->GetCurrentState() == m_pPlayerState["Attack"] && !pEntity->CheckIsStunned() && !pEntity->CheckIsDead())
			{
				if (m_IsFacingLeft && m_Shape.left >= hitboxEntity.left || !m_IsFacingLeft && m_Shape.left <= hitboxEntity.left)
				{
					m_HitEnemy = !pEntity->CheckIsStunned();
					m_Score += pEntity->GetKillPoints();
				}
			}
			
		}
		
		//**** Waarom nullptrs?   *************//

		float ActivationDistance{ 30.f };
		//std::cout << pPiranha << std::endl;
		if (pPiranha && m_Shape.left >= pPiranha->GetSpawnPoint().x - ActivationDistance)
		{
			pPiranha->ActivatePiranha();
		}

		if (pPig)
		{
			Rectf hitboxPig{ pPig->GetShape() };
			pPig->MovePig(*this);

			if (m_pStateMachine->GetCurrentState() == m_pPlayerState["Attack"] && utils::IsOverlapping(m_Shape, hitboxPig))
			{
				if (m_IsFacingLeft && m_Shape.left >= hitboxPig.left || !m_IsFacingLeft && m_Shape.left <= hitboxPig.left)
				{
					pPig->StunEntity(*pPig);
				}
			}
		}

		if (pBlop)
		{
			Rectf hitboxBlop{ pBlop->GetShape() };
			pBlop->MoveBlop(*this);


			if (m_pStateMachine->GetCurrentState() == m_pPlayerState["Attack"] && utils::IsOverlapping(m_Shape, pBlop->GetShape()))
			{
				if (m_IsFacingLeft && m_Shape.left >= hitboxBlop.left || !m_IsFacingLeft && m_Shape.left <= hitboxBlop.left)
				{
					pBlop->StunEntity(*pBlop);
				}
			}
		}

		if (pSnake)
		{

			(pSnake->IsAttackTriggered())
				? pSnake->SnakeAttack(elapsedSec, pSnake->GetHitboxOffset().x)
				: pSnake->TriggerAttack(m_Hitbox);


			if (m_pStateMachine->GetCurrentState() == m_pPlayerState["Attack"])
				pSnake->StunSnake(m_Hitbox);
		}

		if (pAShark)
		{
			pAShark->UpdatePosition(*this, elapsedSec);
			break;
		}
		if (pTShark)
		{
			pTShark->UpdatePosition(*this, elapsedSec);
			break;
		}

		if (pMini)
		{
			pMini->UpdatePosition(elapsedSec, *this);
			m_AreWallsGone = m_pLevel->AreWallsGone();
		}

	}
}
#pragma endregion
#pragma region GettersAndSetters
void Player::MovePlayer(float x, float y)
{
	m_Shape.left += x;
	m_Shape.bottom += y;
}

const int Player::GetLives() const
{
	return m_Lives;
}

void Player::RemoveLife()
{
	if (m_Lives > 0)
	{
		m_Lives--;
	}
	else
	{
		m_IsGameOver = true;
	}
}

void Player::SetLives(int lives)
{
	m_Lives = lives;
}

void Player::RemoveHeart()
{
	--m_Hearts;
}

const int Player::GetHearts() const
{
	return m_Hearts;
}

void Player::SetHearts(int hearts)
{
	m_Hearts = hearts;
}

void Player::AddScore(int points)
{
	m_Score += points;
}

const int Player::GetScore() const
{
	return m_Score;
}

void Player::AddCoins()
{
	++m_Coins;
}

const int Player::GetCoinsCount() const
{
	return m_Coins;
}

void Player::SetJumping(bool isJumping)
{
	m_IsJumping = isJumping;
}
void Player::TransformPlayer(float elapsedSec, float transformationTime)
{
	if (m_CanTransform)
	{
		m_TransformationTimer += elapsedSec;

		if (!m_IsTransformed && m_pStateMachine->GetCurrentState() != m_pPlayerState["TransformIdle"])
		{
			m_IsTransformed = true;
			m_pStateMachine->ChangeState(m_pPlayerState["TransformIdle"]);
		}


		if (m_TransformationTimer >= transformationTime)
		{
			m_IsTransformed = false;
			m_CanTransform = false;
			m_TransformationTimer = 0;
			m_pStateMachine->ChangeState(m_pPlayerState["Idle"]);
		}
	}

	
}
void Player::SetSpriteSize(float size)
{
	m_pSprite->SetSpriteWidth(size);
	m_pSprite->SetSpriteHeight(size);
}
void Player::SetFacingLeft(bool isFacingLeft)
{
	m_IsFacingLeft = isFacingLeft;
}
void Player::SetTransformTimer(float sec)
{
	m_TransformationTimer = sec;
}
void Player::SetVelocity(float x, float y)
{
	m_Velocity.x = x;
	m_Velocity.y = y;

}
void Player::SetGravity(float y)
{
	m_GravityAcceleration.y = y;
}
void Player::SetHitEnemy(bool hitEnemy)
{
	m_HitEnemy = hitEnemy;
}
void Player::SetWallsGone(bool areWallsGone)
{
	m_AreWallsGone = areWallsGone;
}
Player::SpawnPoints Player::GetCurrentSpawnPoint()
{
	return m_CurrentSpawnPoint;
}
const Vector2f Player::GetPlayerVelocity() const
{
	return m_Velocity;
}
bool Player::GetWallsStatus()
{
	return m_AreWallsGone;
}
bool Player::GetIsGameOver() const
{
	return m_IsGameOver;
}
void Player::SetGameOver(bool isGameOver)
{
	m_IsGameOver = isGameOver;
}
const float Player::GetJumpSpeed() const
{
	return m_JumpSpeed;
}
const float Player::GetHorizontalSpeed() const
{
	return m_HorSpeed;
}

PlayerStateMachine* Player::GetStateMachine()
{
	return m_pStateMachine;
}
PlayerState* Player::GetPlayerState(const std::string& stateName)
{
	return m_pPlayerState[stateName];
}

AnimatedSprite* Player::GetSprite()
{
	return m_pSprite;
}
Effects* Player::GetEffect() const
{
	return m_pEffect;
}
bool Player::GetIsEnemyHit() const
{
	return m_HitEnemy;
}
void Player::SetCanBeHit(bool canHitEnemy)
{
	//TODO
}
bool Player::CheckCanBeHit() const
{
	//TODOS
	return false;
}
void Player::SetCanTransform(bool canTransform)
{
	m_CanTransform = canTransform;
}
bool Player::GetCanTransform() const
{
	return m_CanTransform;
}
void Player::SetIsTransformed(bool isTransformed)
{
	m_IsTransformed = isTransformed;
}
bool Player::GetIsTransformed() const
{
	return m_IsTransformed;
}
#pragma endregion
#pragma region Checks
bool Player::IsLedge()
{
	return m_pLevel->HitPlatformLedge(*this);
}
void Player::CheckSpawnPoints()
{
	if (m_Shape.left > 2855.f)
	{
		m_CurrentSpawnPoint = SpawnPoints::spawnpoint2;
	}
	if (m_Shape.left > 7273.f)
	{
		m_CurrentSpawnPoint = SpawnPoints::spawnpoint3;
	}
	if (m_Shape.left > 9211.f)
	{
		m_CurrentSpawnPoint = SpawnPoints::spawnpoint4;
	}
}
void Player::CheckDeath()
{
	if (m_IsDead)
	{
		m_IsDead = false;
		Player::RespawnPlayer();		
	}
}
#pragma endregion
#pragma region OldChecks_RemovedLater
bool Player::IsTransformed()
{
	if (m_IsTransformed)
	{
		SetSpriteSize(65.f);
		m_GravityAcceleration.y = -150.f;
		return true;
	}
	SetSpriteSize(50.f);
	m_GravityAcceleration.y = -981.f;
	return false;
}
#pragma endregion
#pragma region Cleanup
void Player::DeleteSprite()
{
	delete m_pSprite;
	m_pSprite = nullptr;
}
void Player::DeletePlayerStates()
{
	std::map<std::string, PlayerState*>::iterator it = m_pPlayerState.begin();

	while (it != m_pPlayerState.end())
	{
		delete it->second;
		it->second = nullptr;
		it++;
	}
	m_pPlayerState.clear();
}
#pragma endregion
