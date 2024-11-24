#include "pch.h"
#include "PlayerJumpState.h"
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStateMachine.h"
#include "SoundEffect.h"

PlayerJumpState::PlayerJumpState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	:PlayerAbilityState(player, stateMachine, playerData, animation)
	, m_pJumpSound {new SoundEffect("Resources/Audio/Flintstons_Jump.wav")}
{
	m_pJumpSound->SetVolume(45);
}

PlayerJumpState::~PlayerJumpState()
{
	delete m_pJumpSound;
}

void PlayerJumpState::Enter()
{
	PlayerAbilityState::Enter();
	m_pPlayer->SetJumping(true);
	m_pJumpSound->Play(0);
	m_pPlayer->SetVelocity(m_pPlayer->GetPlayerVelocity().x, m_pPlayer->GetJumpSpeed());
	m_IsAbilityDone = true;
}

void PlayerJumpState::Exit()
{
	m_pStateMachine->SetPreviousState(this);
	m_pPlayer->SetJumping(false);
	PlayerAbilityState::Exit();
}

void PlayerJumpState::LogicUpdate(float elapsedSec)
{
	PlayerAbilityState::LogicUpdate(elapsedSec);
}

void PlayerJumpState::PhysicsUpdate(float elapsedSec)
{
	PlayerAbilityState::PhysicsUpdate(elapsedSec);
}

void PlayerJumpState::DoChecks()
{
	PlayerAbilityState::DoChecks();
}
