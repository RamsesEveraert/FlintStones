#include "pch.h"
#include "Player.h"
#include "PlayerState.h"
#include "PlayerIdleState.h"
#include "PlayerMoveState.h"
#include "PlayerStateMachine.h"
#include "AnimatedSprite.h"

PlayerIdleState::PlayerIdleState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerGroundedState(player, stateMachine, playerData, animation)
{

}

void PlayerIdleState::Enter()
{
	PlayerGroundedState::Enter();
	m_CanMove = true;
}

void PlayerIdleState::Exit()
{
	m_pStateMachine->SetPreviousState(this);
	PlayerGroundedState::Exit();
}

void PlayerIdleState::LogicUpdate(float elapsedSec)
{
	PlayerGroundedState::LogicUpdate(elapsedSec);
	PlayerIdleState::StartDance(elapsedSec);
	PlayerIdleState::HandleInputs(elapsedSec);	
}

void PlayerIdleState::PhysicsUpdate(float elapsedSec)
{
	PlayerGroundedState::PhysicsUpdate(elapsedSec);

}

void PlayerIdleState::DoChecks()
{
	PlayerGroundedState::DoChecks();
}

void PlayerIdleState::HandleInputs(float elapsedSec)
{
	PlayerGroundedState::HandleInputs(elapsedSec);

	if (!m_pStates[SDL_SCANCODE_W])
	{
		m_IsJumpLocked = false;
	}
	 if (m_pStates[SDL_SCANCODE_LEFT] || m_pStates[SDL_SCANCODE_RIGHT])
	{

		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Moving"]);
	}
	else if (m_pStates[SDL_SCANCODE_DOWN])
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Crough"]);
	}
	
}



void PlayerIdleState::StartDance(float elapsedSec)
{
	m_StartTime += elapsedSec;

	if (m_StartTime > 5.f)
	{
		m_pPlayer->GetSprite()->SetFramesPerSec(6);
		m_pPlayer->GetSprite()->PlayAnimation("Dancing");
	}
}

