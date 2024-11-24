#include "pch.h"
#include "PlayerTransformAttackState.h"
#include "PlayerStateMachine.h"
#include "Player.h"
#include"AnimatedSprite.h"


PlayerTransformAttackState::PlayerTransformAttackState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerTransformedState(player, stateMachine, playerData, animation)
{
}

void PlayerTransformAttackState::Enter()
{
	
	PlayerTransformedState::Enter();

	std::cout << "transformAttack state \n";

	if (m_pStateMachine->GetPreviousState() == m_pPlayer->m_pPlayerState["TransformIdle"])
	{
		m_pPlayer->GetSprite()->SetFramesPerSec(4);
		m_pPlayer->GetSprite()->SetSpriteWidth(50.f);
		m_pPlayer->GetSprite()->PlayAnimation("BirdShoot");
	}
	else if (m_pStateMachine->GetPreviousState() == m_pPlayer->m_pPlayerState["TransformWalk"])
	{
		m_pPlayer->GetSprite()->SetFramesPerSec(8);
		m_pPlayer->GetSprite()->SetSpriteWidth(50.f);
		m_pPlayer->GetSprite()->PlayAnimation("BirdWalkShoot");
	}
	else if (m_pStateMachine->GetPreviousState() == m_pPlayer->m_pPlayerState["TransformFly"])
	{
		m_pPlayer->GetSprite()->SetSpriteWidth(63.f);
		m_pPlayer->GetSprite()->PlayAnimation("BirdFlyShoot");
	}
		
	
}

void PlayerTransformAttackState::Exit()
{
	m_pStateMachine->SetPreviousState(this);
	PlayerTransformedState::Exit();
}

void PlayerTransformAttackState::LogicUpdate(float elapsedSec)
{
	PlayerTransformedState::LogicUpdate(elapsedSec);
	PlayerTransformAttackState::HandleInputs(elapsedSec);
	m_StartTime += elapsedSec;

	
}

void PlayerTransformAttackState::PhysicsUpdate(float elapsedSec)
{
	PlayerTransformedState::PhysicsUpdate(elapsedSec);
}

void PlayerTransformAttackState::DoChecks()
{
	PlayerTransformedState::DoChecks();
}

void PlayerTransformAttackState::HandleInputs(float elapsedSec)
{
	if (!m_pStates[SDL_SCANCODE_X])
	{
		m_StartTime += elapsedSec;

		if (m_StartTime > 0.25f)
		{
		m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["TransformIdle"]);
		m_StartTime = 0;
		}
	}
	if (m_pStates[SDL_SCANCODE_X])
	{

	}
}
