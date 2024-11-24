#include "pch.h"
#include "PlayerTransformFlyState.h"
#include "PlayerStateMachine.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "SoundEffect.h"


PlayerTransformFlyState::PlayerTransformFlyState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	: PlayerTransformedState(player, stateMachine, playerData, animation)
	, m_pJumpSound{ new SoundEffect("Resources/Audio/Flintstons_Jump.wav") }
{
	m_pJumpSound->SetVolume(45);
}

PlayerTransformFlyState::~PlayerTransformFlyState()
{
	delete m_pJumpSound;
}

void PlayerTransformFlyState::Enter()
{
	PlayerTransformedState::Enter();
	m_pJumpSound->Play(0);
	m_pPlayer->GetSprite()->SetSpriteWidth(63.f);
	m_pPlayer->SetGravity(-200.f);
}

void PlayerTransformFlyState::Exit()
{
	m_pStateMachine->SetPreviousState(this);

	m_pPlayer->GetSprite()->SetSpriteWidth(50.f);

	m_pPlayer->SetGravity(-981.f);
	m_pPlayer->SetJumpSpeed(330.f);
	PlayerTransformedState::Exit();
}

void PlayerTransformFlyState::LogicUpdate(float elapsedSec)
{
	PlayerTransformedState::LogicUpdate(elapsedSec);
	PlayerTransformFlyState::HandleInputs(elapsedSec);

	if (m_pPlayer->GetVelocity().y == 0)
	{
		(m_pPlayer->GetVelocity().x == 0)
			? m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["TransformIdle"])
			: m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["TransformWalk"]);
	}
		
}

void PlayerTransformFlyState::PhysicsUpdate(float elapsedSec)
{
	PlayerTransformedState::PhysicsUpdate(elapsedSec);
}

void PlayerTransformFlyState::DoChecks()
{
	PlayerTransformedState::DoChecks();
}

void PlayerTransformFlyState::HandleInputs(float elapsedSec)
{
	if (!m_pStates[SDL_SCANCODE_LEFT] && !m_pStates[SDL_SCANCODE_RIGHT])
	{
		
	}
}
