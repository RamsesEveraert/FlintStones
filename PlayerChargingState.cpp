#include "pch.h"
#include "PlayerChargingState.h"
#include "Effects.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "PlayerStateMachine.h"

PlayerChargingState::PlayerChargingState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerState(player, stateMachine, playerData, animation)
{

}

void PlayerChargingState::Enter()
{
	m_pPlayer->GetEffect()->SetEffectOffset(Point2f{ 0.f, -5.f });
	m_pPlayer->GetSprite()->SetFramesPerSec(8);
	PlayerState::Enter();
	m_CanAttack = false;
}

void PlayerChargingState::Exit()
{
	m_pStateMachine->SetPreviousState(this);
	PlayerState::Exit();
}

void PlayerChargingState::LogicUpdate(float elapsedSec)
{
	PlayerState::LogicUpdate(elapsedSec);
	PlayerChargingState::HandleInputs(elapsedSec);
}

void PlayerChargingState::PhysicsUpdate(float elapsedSec)
{
	PlayerState::PhysicsUpdate(elapsedSec);

}

void PlayerChargingState::DoChecks()
{
	PlayerState::DoChecks();
}

void PlayerChargingState::HandleInputs(float elapsedSec)
{
	if (m_pStates[SDL_SCANCODE_X])
	{
		m_pPlayer->GetEffect()->PlayEffect(Effects::Effect::charging, true, 1.f, 9);
	}
	if (m_pStates[SDL_SCANCODE_LEFT] || m_pStates[SDL_SCANCODE_RIGHT])
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["ChargedMove"]);
	}
	else if (!m_pStates[SDL_SCANCODE_X])
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Attack"]);
	}
}

