#include "pch.h"
#include "PlayerAbilityState.h"
#include "PlayerState.h"
#include "PlayerStateMachine.h"
#include "Player.h"
#include "AnimatedSprite.h"

PlayerAbilityState::PlayerAbilityState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerState(player, stateMachine, playerData, animation)
	, m_IsAbilityDone { false }
{
}

void PlayerAbilityState::Enter()
{
	PlayerState::Enter();
	m_IsAbilityDone = false;
}

void PlayerAbilityState::Exit()
{
	PlayerState::Exit();
}

void PlayerAbilityState::LogicUpdate(float elapsedSec)
{
	PlayerState::LogicUpdate(elapsedSec);
}

void PlayerAbilityState::PhysicsUpdate(float elapsedSec)
{
	PlayerState::PhysicsUpdate(elapsedSec);
}

void PlayerAbilityState::DoChecks()
{
	PlayerState::DoChecks();
	
}