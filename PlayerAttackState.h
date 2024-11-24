#pragma once
#include "PlayerState.h"
#include"PlayerAbilityState.h"

class SoundEffect;

class PlayerAttackState final : public PlayerAbilityState
{
public:
	PlayerAttackState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerAttackState();

	PlayerAttackState(const PlayerAttackState& other) = delete;
	PlayerAttackState& operator=(const PlayerAttackState& other) = delete;
	PlayerAttackState(PlayerAttackState&& other) = delete;
	PlayerAttackState& operator=(PlayerAttackState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

protected:

	virtual void HandleInputs(float elapsedSec);

private:
	float m_ChargeTimer;

	SoundEffect* m_pHitSound;

};

