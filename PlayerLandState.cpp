#include "pch.h"
#include "PlayerLandState.h"

PlayerLandState::PlayerLandState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerGroundedState(player, stateMachine, playerData, animation)
{
}

void PlayerLandState::Enter()
{
	PlayerGroundedState::Enter();
}

void PlayerLandState::Exit()
{
	m_pStateMachine->SetPreviousState(this);
	PlayerGroundedState::Exit();
}

void PlayerLandState::LogicUpdate(float elapsedSec)
{
	PlayerState::LogicUpdate(elapsedSec);
	PlayerLandState::HandleInputs(elapsedSec);
}

void PlayerLandState::PhysicsUpdate(float elapsedSec)
{
	PlayerGroundedState::PhysicsUpdate(elapsedSec);
}

void PlayerLandState::DoChecks()
{
	PlayerGroundedState::DoChecks();
}

void PlayerLandState::HandleInputs(float elapsedSec)
{
	m_StartTime += elapsedSec;

	
		if (m_pStates[SDL_SCANCODE_LEFT] || m_pStates[SDL_SCANCODE_RIGHT])
		{
			if (m_StartTime > 0.065f)
			{
				m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Moving"]);
			}
		}
		else
		{
			if (m_StartTime > 0.12f)
			{
				m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Idle"]);
			}
		}

			
}
