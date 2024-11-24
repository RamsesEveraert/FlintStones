#include "pch.h"
#include "PlayerInAirState.h"
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStateMachine.h"
#include  "AnimatedSprite.h"

PlayerInAirState::PlayerInAirState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerAbilityState(player, stateMachine, playerData, animation)
{
}

void PlayerInAirState::Enter()
{
	PlayerAbilityState::Enter();

	m_pPlayer->GetSprite()->PlayAnimation("Falling");
}

void PlayerInAirState::Exit()
{
	m_pStateMachine->SetPreviousState(this);
	PlayerAbilityState::Exit();
}

void PlayerInAirState::LogicUpdate(float elapsedSec)
{
	PlayerAbilityState::LogicUpdate(elapsedSec);

	if (!m_pPlayer->GetIsTransformed() && m_pPlayer->IsOnGround() && m_pPlayer->GetPlayerVelocity().y <= 0)
	{

		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["LandState"]);
	}
	else if (!m_pPlayer->GetIsTransformed() && m_pPlayer->GetVelocity().y == 0)
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Idle"]);
	}
	else
	{
		HandleInputs(elapsedSec);
	}

}

void PlayerInAirState::PhysicsUpdate(float elapsedSec)
{
	PlayerAbilityState::PhysicsUpdate(elapsedSec);
}

void PlayerInAirState::DoChecks()
{
	PlayerAbilityState::DoChecks();
}

void PlayerInAirState::HandleInputs(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_pPlayer->SetVelocity(m_pPlayer->GetHorizontalSpeed(), m_pPlayer->GetPlayerVelocity().y);
	}
	else if (pStates[SDL_SCANCODE_LEFT])
	{
		m_pPlayer->SetVelocity(-m_pPlayer->GetHorizontalSpeed(), m_pPlayer->GetPlayerVelocity().y);
	}
	else if (pStates[SDL_SCANCODE_X])
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Attack"]);
	}
	else if (pStates[SDL_SCANCODE_W])
	{
		if (m_pPlayer->IsLedge())
		{
			m_pPlayer->SetVelocity(0, m_pPlayer->GetPlayerVelocity().y);
			m_pStateMachine->ChangeState(m_pPlayer->GetPlayerState("LedgeHang"));
		}
	}

}
