#include "pch.h"
#include "PlayerChargedMoveState.h"
#include "Effects.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "PlayerStateMachine.h"

PlayerChargedMoveState::PlayerChargedMoveState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerState(player, stateMachine, playerData, animation)
{

}

void PlayerChargedMoveState::Enter()
{
	PlayerState::Enter();
	m_pPlayer->GetEffect()->SetEffectOffset(Point2f{ });
}

void PlayerChargedMoveState::Exit()
{
	m_pStateMachine->SetPreviousState(this);
	PlayerState::Exit();
}

void PlayerChargedMoveState::LogicUpdate(float elapsedSec)
{
	PlayerState::LogicUpdate(elapsedSec);
	PlayerChargedMoveState::HandleInputs(elapsedSec);
}

void PlayerChargedMoveState::PhysicsUpdate(float elapsedSec)
{
	PlayerState::PhysicsUpdate(elapsedSec);

}

void PlayerChargedMoveState::DoChecks()
{
	PlayerState::DoChecks();
}

void PlayerChargedMoveState::HandleInputs(float elapsedSec)
{
	if (m_pStates[SDL_SCANCODE_X])
	{
		m_pPlayer->GetEffect()->PlayEffect(Effects::Effect::charging, true, 1.f, 9);
	}

	if (!m_pStates[SDL_SCANCODE_X])
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Attack"]);
	}
	else if (!m_pStates[SDL_SCANCODE_LEFT] && !m_pStates[SDL_SCANCODE_RIGHT])
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Charging"]);
	}
}

