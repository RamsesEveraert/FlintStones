#include "pch.h"
#include "PlayerTransformIdleState.h"
#include "PlayerStateMachine.h"
#include "Player.h"
#include"AnimatedSprite.h"


PlayerTransformIdleState::PlayerTransformIdleState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerTransformedState(player, stateMachine, playerData, animation)
{
}

void PlayerTransformIdleState::Enter()
{
	PlayerTransformedState::Enter();
	std::cout << "transformIdle State \n";
}

void PlayerTransformIdleState::Exit()
{
	m_pStateMachine->SetPreviousState(this);
	PlayerTransformedState::Exit();
}

void PlayerTransformIdleState::LogicUpdate(float elapsedSec)
{
	PlayerTransformedState::LogicUpdate(elapsedSec);
	PlayerTransformIdleState::HandleInputs(elapsedSec);
}

void PlayerTransformIdleState::PhysicsUpdate(float elapsedSec)
{
	PlayerTransformedState::PhysicsUpdate(elapsedSec);
}

void PlayerTransformIdleState::DoChecks()
{
	PlayerTransformedState::DoChecks();
}

void PlayerTransformIdleState::HandleInputs(float elapsedSec)
{
	if ( m_pStates[SDL_SCANCODE_LEFT] || m_pStates[SDL_SCANCODE_RIGHT])
	{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["TransformWalk"]);
	}
}
