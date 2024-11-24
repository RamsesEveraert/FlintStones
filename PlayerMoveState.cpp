#include "pch.h"
#include "PlayerMoveState.h"
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStateMachine.h"
#include "AnimatedSprite.h"

PlayerMoveState::PlayerMoveState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerGroundedState(player, stateMachine, playerData, animation)
{

}

void PlayerMoveState::Enter()
{
	PlayerGroundedState::Enter();
	m_pPlayer->GetSprite()->SetFramesPerSec(18);
	m_IsJumpLocked = false;
	m_CanMove = true;
}

void PlayerMoveState::Exit()
{
	PlayerGroundedState::Exit();
}

void PlayerMoveState::LogicUpdate(float elapsedSec)
{
	PlayerGroundedState::LogicUpdate(elapsedSec);
	PlayerMoveState::HandleInputs(elapsedSec);
	
	
}

void PlayerMoveState::PhysicsUpdate(float elapsedSec)
{
	PlayerGroundedState::PhysicsUpdate(elapsedSec);
}

void PlayerMoveState::DoChecks()
{
	PlayerGroundedState::DoChecks();
}

void PlayerMoveState::HandleInputs(float elapsedSec)
{
	PlayerState::HandleInputs(elapsedSec);

	if (m_pPlayer->GetShape().left >= 2950.f && m_pPlayer->GetShape().left <= 3418.f)
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["SlopeRun"]);
	}

	if (!m_pStates[SDL_SCANCODE_LEFT] && !m_pStates[SDL_SCANCODE_RIGHT])
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Idle"]);
	}		
	else if (m_pStates[SDL_SCANCODE_DOWN])
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Crough"]);
	}
}


