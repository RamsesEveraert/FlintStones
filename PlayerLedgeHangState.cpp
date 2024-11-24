#include "pch.h"
#include "PlayerLedgeHangState.h"
#include "PlayerStateMachine.h"
#include "Player.h"
#include "AnimatedSprite.h"

PlayerLedgeHangState::PlayerLedgeHangState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerState(player, stateMachine, playerData, animation)
{
}


void PlayerLedgeHangState::Enter()
{
	PlayerState::Enter();

	m_CanAttack = false;
	m_IsInputLocked = true;
	m_pPlayer->GetSprite()->SetFramesPerSec(6);
	m_pPlayer->SetGravity(0);
}

void PlayerLedgeHangState::Exit()
{
	m_pStateMachine->SetPreviousState(this);

	m_CanAttack = true;
	m_pPlayer->SetGravity(-981.f);

	PlayerState::Exit();
	
}

void PlayerLedgeHangState::LogicUpdate(float elapsedSec)
{
	PlayerState::LogicUpdate(elapsedSec);
	PlayerLedgeHangState::HandleInputs(elapsedSec);
}

void PlayerLedgeHangState::PhysicsUpdate(float elapsedSec)
{
	PlayerState::PhysicsUpdate(elapsedSec);
}

void PlayerLedgeHangState::DoChecks()
{
	PlayerState::DoChecks();
}

void PlayerLedgeHangState::HandleInputs(float elapsedSec)
{
	if (m_pStates[SDL_SCANCODE_UP])
	{
		m_pStateMachine->ChangeState(m_pPlayer->GetPlayerState("LedgeClimb"));
	}
	else if (!m_pStates[SDL_SCANCODE_W])
	{
		m_pStateMachine->ChangeState(m_pPlayer->GetPlayerState("InAir"));
	}

}
