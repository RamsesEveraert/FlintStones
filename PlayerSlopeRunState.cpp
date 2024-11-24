#include "pch.h"
#include "PlayerSlopeRunState.h"
#include "PlayerStateMachine.h"
#include "Player.h"
#include"AnimatedSprite.h"


PlayerSlopeRunState::PlayerSlopeRunState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerGroundedState(player, stateMachine, playerData, animation)
{
}

void PlayerSlopeRunState::Enter()
{
	PlayerGroundedState::Enter();
}

void PlayerSlopeRunState::Exit()
{
	m_pStateMachine->SetPreviousState(this);
	PlayerGroundedState::Exit();
}

void PlayerSlopeRunState::LogicUpdate(float elapsedSec)
{
	PlayerGroundedState::LogicUpdate(elapsedSec);
	PlayerSlopeRunState::HandleInputs(elapsedSec);
}

void PlayerSlopeRunState::PhysicsUpdate(float elapsedSec)
{
	PlayerGroundedState::PhysicsUpdate(elapsedSec);
}

void PlayerSlopeRunState::DoChecks()
{
	PlayerGroundedState::DoChecks();
}

void PlayerSlopeRunState::HandleInputs(float elapsedSec)
{
	if (!m_pStates[SDL_SCANCODE_LEFT] && !m_pStates[SDL_SCANCODE_RIGHT])
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Idle"]);
	}
}
