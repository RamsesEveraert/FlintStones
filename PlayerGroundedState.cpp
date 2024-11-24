#include "pch.h"
#include "PlayerGroundedState.h"
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStateMachine.h"
#include "AnimatedSprite.h"
#include "Effects.h"

PlayerGroundedState::PlayerGroundedState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerState(player,stateMachine,playerData,animation)
{
}

void PlayerGroundedState::Enter()
{
	PlayerState::Enter();
}

void PlayerGroundedState::Exit()
{
	PlayerState::Exit();
}

void PlayerGroundedState::LogicUpdate(float elapsedSec)
{
	

	PlayerState::LogicUpdate(elapsedSec);
	PlayerGroundedState::HandleInputs(elapsedSec);
}

void PlayerGroundedState::PhysicsUpdate(float elapsedSec)
{
	PlayerState::PhysicsUpdate(elapsedSec);
}

void PlayerGroundedState::DoChecks()
{
	PlayerState::DoChecks();
	if (m_pPlayer->IsOnGround())
	{
		m_IsGrounded = true;
	}
}

void PlayerGroundedState::HandleInputs(float elapsedSec)
{
	PlayerState::HandleInputs(elapsedSec);

	if (m_pStates[SDL_SCANCODE_W] || m_pStates[SDL_SCANCODE_Z])
	{
		if (!m_IsJumpLocked && m_pPlayer->GetVelocity().y == 0)
		{
			m_IsJumpLocked = true;

			m_pPlayer->GetIsTransformed()
				? m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["TransformJump"])
				: m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["JumpState"]);
		}
		else if (!m_IsGrounded)
		{
			m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["InAir"]);
		}
	}	
}
