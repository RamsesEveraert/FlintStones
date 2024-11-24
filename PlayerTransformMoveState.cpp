#include "pch.h"
#include "PlayerTransformMoveState.h"
#include "PlayerStateMachine.h"
#include "Player.h"
#include"AnimatedSprite.h"


PlayerTransformMoveState::PlayerTransformMoveState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerTransformedState(player, stateMachine, playerData, animation)
{
}

void PlayerTransformMoveState::Enter()
{
	PlayerTransformedState::Enter();
	m_pPlayer->GetSprite()->SetFramesPerSec(6);
	std::cout << "transformMove State \n";
}

void PlayerTransformMoveState::Exit()
{
	m_pStateMachine->SetPreviousState(this);
	PlayerTransformedState::Exit();
}

void PlayerTransformMoveState::LogicUpdate(float elapsedSec)
{
	PlayerTransformedState::LogicUpdate(elapsedSec);
	PlayerTransformMoveState::HandleInputs(elapsedSec);
}

void PlayerTransformMoveState::PhysicsUpdate(float elapsedSec)
{
	PlayerTransformedState::PhysicsUpdate(elapsedSec);
}

void PlayerTransformMoveState::DoChecks()
{
	PlayerTransformedState::DoChecks();
}

void PlayerTransformMoveState::HandleInputs(float elapsedSec)
{
	if (!m_pStates[SDL_SCANCODE_LEFT] && !m_pStates[SDL_SCANCODE_RIGHT])
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["TransformIdle"]);
	}
}
