#include "pch.h"
#include "PlayerAttackState.h"
#include "Effects.h"
#include "PlayerStateMachine.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "SoundEffect.h"

PlayerAttackState::PlayerAttackState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation)
	:PlayerAbilityState(player, stateMachine, playerData, animation)
	, m_ChargeTimer{}
	, m_pHitSound {new SoundEffect("Resources/Audio/Flintstones_Hit.wav")}
{
	m_pHitSound->SetVolume(35);
}

PlayerAttackState::~PlayerAttackState()
{
	delete m_pHitSound;
}

void PlayerAttackState::Enter()
{
	if (m_pPlayer->GetEffect()->GetCurrentEffectName() == "Charging")
	{
		m_pPlayer->GetEffect()->StopEffect();
	}
	m_pPlayer->GetSprite()->SetFramesPerSec(6);
	PlayerAbilityState::Enter();
	m_pHitSound->Play(0);
	m_pPlayer->SetAttacking(true);
	m_CanAttack = false;
	m_CanMove = false;
	m_ChargeTimer = 0;
}

void PlayerAttackState::Exit()
{
	m_pPlayer->SetAttacking(false);
	m_pStateMachine->SetPreviousState(this);
	PlayerAbilityState::Exit();
}
	

void PlayerAttackState::LogicUpdate(float elapsedSec)
{
	PlayerAbilityState::LogicUpdate(elapsedSec);
	PlayerAttackState::HandleInputs(elapsedSec);

	
	if (m_pPlayer->GetIsEnemyHit())
	{

		Rectf animLocation{ m_pPlayer->GetShape() };
		m_pPlayer->IsFacingLeft() ? animLocation.left : animLocation.left += 0.9f * animLocation.width;
		animLocation.bottom += 0.9f * animLocation.height;

		m_pPlayer->GetEffect()->SetDestinationEffect(animLocation);
		m_pPlayer->GetEffect()->PlayEffect(Effects::Effect::hit, false, 0.f, 0.3f);
	}

	m_pPlayer->SetHitEnemy(false);

}

void PlayerAttackState::PhysicsUpdate(float elapsedSec)
{
	PlayerAbilityState::PhysicsUpdate(elapsedSec);
}

void PlayerAttackState::DoChecks()
{
	PlayerAbilityState::DoChecks();
}

void PlayerAttackState::HandleInputs(float elapsedSec)
{
	m_StartTime += elapsedSec;

	if (!m_pStates[SDL_SCANCODE_X])
	{
		m_ChargeTimer = 0;

		if (m_StartTime > 0.17f)
		{
			m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Idle"]);
			m_StartTime = 0;
		}
	}
	else if (m_pStates[SDL_SCANCODE_X])
		{	
			m_ChargeTimer += elapsedSec;

			if (m_ChargeTimer > 0.17f)
			{
				m_pStateMachine->ChangeState(m_pPlayer->m_pPlayerState["Charging"]);
			}
		}
	
	
}
