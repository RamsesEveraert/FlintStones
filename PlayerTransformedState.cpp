#include "pch.h"
#include "PlayerTransformedState.h"
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStateMachine.h"
#include "AnimatedSprite.h"
#include "Effects.h"

PlayerTransformedState::PlayerTransformedState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
		: PlayerState(player, stateMachine, playerData, animation)
		, m_HasShoot { false }
{
}

void PlayerTransformedState::Enter()
{
	PlayerState::Enter();
}

void PlayerTransformedState::Exit()
{
	PlayerState::Exit();
}

void PlayerTransformedState::LogicUpdate(float elapsedSec)
{


	PlayerState::LogicUpdate(elapsedSec);
	PlayerTransformedState::HandleInputs(elapsedSec);
}

void PlayerTransformedState::PhysicsUpdate(float elapsedSec)
{
	PlayerState::PhysicsUpdate(elapsedSec);
}

void PlayerTransformedState::DoChecks()
{
	PlayerState::DoChecks();

}

void PlayerTransformedState::HandleInputs(float elapsedSec)
{
	PlayerState::HandleInputs(elapsedSec);

	m_StartTime += elapsedSec;

	if (!m_HasShoot && !(m_pStateMachine->GetCurrentState() == m_pPlayer->GetPlayerState("TransformAttack")) && m_pStates[SDL_SCANCODE_X])
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["TransformAttack"]);
		/*m_HasShoot = true;*/
	}
	else if (m_HasShoot && m_pStateMachine->GetCurrentState() == m_pPlayer->GetPlayerState("TransformAttack") && m_StartTime >= 0.25f)
	{
		m_HasShoot = false;
	}
	else if (m_pPlayer->GetVelocity().y == 0 &&  m_pStates[SDL_SCANCODE_W] && !(m_pStateMachine->GetCurrentState() == m_pPlayer->GetPlayerState("TransformFly")))
	{
		m_pPlayer->SetJumpSpeed(220.f);
		m_pPlayer->SetVelocity(m_pPlayer->GetPlayerVelocity().x, m_pPlayer->GetJumpSpeed());
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["TransformFly"]);
	}

	
}
