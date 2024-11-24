#include "pch.h"
#include "PlayerCrouchState.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "AnimatedSprite.h"

PlayerCrouchState::PlayerCrouchState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerGroundedState(player, stateMachine, playerData, animation)
	, m_IsNextIdle {true}
{
}

void PlayerCrouchState::Enter()
{
	PlayerGroundedState::Enter();
	m_CanMove = false;
	m_pPlayer->GetSprite()->SetFramesPerSec(12);
}

void PlayerCrouchState::Exit()
{
	m_pStateMachine->SetPreviousState(this);
	PlayerGroundedState::Exit();
}

void PlayerCrouchState::LogicUpdate(float elapsedSec)
{
	m_StartTime += elapsedSec;
	m_pPlayer->GetSprite()->PlayAnimation("Crough", 1, false);
	PlayerGroundedState::LogicUpdate(elapsedSec);

	if (m_StartTime > (1.f / 5))
	{
		if (m_pStates[SDL_SCANCODE_LEFT] || m_pStates[SDL_SCANCODE_RIGHT])
		{
			m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Moving"]);
		}
	else if (!m_pStates[SDL_SCANCODE_DOWN])
		{
			m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Idle"]);
		}
		
		
	}	
}

void PlayerCrouchState::PhysicsUpdate(float elapsedSec)
{
	PlayerGroundedState::PhysicsUpdate(elapsedSec);
}

void PlayerCrouchState::DoChecks()
{
	PlayerGroundedState::DoChecks();
}
