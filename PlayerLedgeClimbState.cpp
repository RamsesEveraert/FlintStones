#include "pch.h"
#include "PlayerLedgeClimbState.h"
#include "PlayerStateMachine.h"
#include "Player.h"
#include "AnimatedSprite.h"

PlayerLedgeClimbState::PlayerLedgeClimbState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerState(player, stateMachine, playerData, animation)
	, m_ClimbOffset {8.f}
{
}


void PlayerLedgeClimbState::Enter()
{
	PlayerState::Enter();

	m_CanAttack = false;
	m_IsInputLocked = true;
	m_pPlayer->GetSprite()->SetFramesPerSec(6);
	m_pPlayer->SetGravity(0);

	m_pPlayer->IsFacingLeft()
		? m_pPlayer->MovePlayer(-m_pPlayer->GetShape().width / 8, (m_pPlayer->GetShape().height / 2) + m_ClimbOffset)
		: m_pPlayer->MovePlayer(m_pPlayer->GetShape().width / 4 , (m_pPlayer->GetShape().height / 2) + m_ClimbOffset);

}

void PlayerLedgeClimbState::Exit()
{
	m_pStateMachine->SetPreviousState(this);

	m_CanAttack = true;
	m_pPlayer->SetGravity(-981.f);

	m_pPlayer->IsFacingLeft()
		? m_pPlayer->MovePlayer(-m_pPlayer->GetShape().width / 8, m_pPlayer->GetShape().height / 3)
		: m_pPlayer->MovePlayer(m_pPlayer->GetShape().width / 4, m_pPlayer->GetShape().height / 3);

	PlayerState::Exit();
}

void PlayerLedgeClimbState::LogicUpdate(float elapsedSec)
{
	m_StartTime += elapsedSec;

	PlayerState::LogicUpdate(elapsedSec);
	PlayerLedgeClimbState::HandleInputs(elapsedSec);

	if (m_StartTime > 0.45)
	{
		m_pStateMachine->ChangeState(m_pPlayer->GetPlayerState("Idle"));
	}
}

void PlayerLedgeClimbState::PhysicsUpdate(float elapsedSec)
{
	PlayerState::PhysicsUpdate(elapsedSec);
}

void PlayerLedgeClimbState::DoChecks()
{
	PlayerState::DoChecks();
}

void PlayerLedgeClimbState::HandleInputs(float elapsedSec)
{

}
