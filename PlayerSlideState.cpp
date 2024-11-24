#include "pch.h"
#include "PlayerSlideState.h"
#include "Player.h"
#include "PlayerStateMachine.h"

PlayerSlideState::PlayerSlideState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerGroundedState(player, stateMachine, playerData, animation)
{

}

void PlayerSlideState::Enter()
{
	PlayerGroundedState::Enter();
}

void PlayerSlideState::Exit()
{
	m_pStateMachine->SetPreviousState(this);
	PlayerGroundedState::Exit();
}

void PlayerSlideState::LogicUpdate(float elapsedSec)
{
	m_pPlayer->IsFacingLeft()
		? m_pPlayer->SetVelocity(-m_pPlayer->GetHorizontalSpeed() / 2, m_pPlayer->GetPlayerVelocity().y)
		: m_pPlayer->SetVelocity(m_pPlayer->GetHorizontalSpeed() / 2, m_pPlayer->GetPlayerVelocity().y);

	PlayerSlideState::StartSlideTimer(elapsedSec);

}

void PlayerSlideState::PhysicsUpdate(float elapsedSec)
{
	PlayerGroundedState::PhysicsUpdate(elapsedSec);
}

void PlayerSlideState::DoChecks()
{
	PlayerGroundedState::DoChecks();
}

void PlayerSlideState::StartSlideTimer(float elapsedSec)
{
	m_StartTime += elapsedSec;

	if (m_StartTime > 1.2f)
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Idle"]);
	}
}

