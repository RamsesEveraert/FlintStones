#include "pch.h"
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStateMachine.h"
#include "PlayerData.h"
#include "PlayerMoveState.h"
#include "AnimatedSprite.h"
#include "Effects.h"



PlayerState::PlayerState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: m_pPlayer{ player }
	, m_pStateMachine{ stateMachine }
	, m_pPlayerData{ playerData }
	, m_AnimationName{ animation }
	, m_pStates{ SDL_GetKeyboardState(nullptr) }
	, m_StartTime{}
	, m_IsAnimationFinished{ false }
	, m_IsInputLocked{ false }
	, m_CanMove{ true }
	, m_IsAttacking{ false }
	, m_CanAttack{ true }
	, m_IsJumpLocked{ false }
{

}


void PlayerState::Enter()
{
	m_StartTime = 0;
	m_IsAnimationFinished = false;
	m_IsInputLocked = false;
	m_CanAttack = true;

	m_pStates = SDL_GetKeyboardState(nullptr);
	PlayerState::DoChecks();

	if (m_pStateMachine->GetCurrentState() == m_pPlayer->GetPlayerState("Attack"))
	{
		m_pPlayer->GetSprite()->SetSpriteWidth(55.f);
		m_pPlayer->GetSprite()->SetSpriteHeight(50.f);
	}
	else
	{
		m_pPlayer->GetSprite()->SetSpriteWidth(50.f);
		m_pPlayer->GetSprite()->SetSpriteHeight(50.f);
	}


	m_pPlayer->GetSprite()->PlayAnimation(m_AnimationName);	

}

void PlayerState::Exit()
{
	m_pPlayer->GetSprite()->StopAnimation();
}

void PlayerState::LogicUpdate(float elapsedSec)
{

	if (!m_IsInputLocked)
	{
		PlayerState::HandleInputs(elapsedSec);
	}


}

void PlayerState::PhysicsUpdate(float elapsedSec)
{
	PlayerState::DoChecks();
}

void PlayerState::DoChecks()
{
}

void PlayerState::HandleInputs(float elapsedSec)
{
	m_pPlayer->SetVelocity(0, m_pPlayer->GetPlayerVelocity().y);

	if (m_CanMove)
	{
		if (m_pStates[SDL_SCANCODE_RIGHT] || m_pStates[SDL_SCANCODE_LEFT])
		{
			float scaler{ (m_pStates[SDL_SCANCODE_LEFT]) ? -1.f : 1.f };
			(m_pStates[SDL_SCANCODE_LEFT])
				? m_pPlayer->SetFacingLeft(true)
				: m_pPlayer->SetFacingLeft(false);
			(m_pStateMachine->GetCurrentState() == m_pPlayer->GetPlayerState("ChargedMove"))
				? m_pPlayer->SetVelocity(scaler * m_pPlayer->GetHorizontalSpeed() / 3, m_pPlayer->GetPlayerVelocity().y)
				: m_pPlayer->SetVelocity(scaler * m_pPlayer->GetHorizontalSpeed(), m_pPlayer->GetPlayerVelocity().y);

		}
	}
	if (!m_pPlayer->GetIsTransformed() && !(m_pStateMachine->GetCurrentState() == m_pPlayer->GetPlayerState("ChargedMove")) && m_CanAttack && m_pStates[SDL_SCANCODE_X]
		&& !(m_pStateMachine->GetCurrentState() == m_pPlayer->GetPlayerState("Attack")))
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Attack"]);
	}
}