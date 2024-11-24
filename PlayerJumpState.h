#pragma once
#include "PlayerAbilityState.h"

class SoundEffect;

class PlayerJumpState final : public PlayerAbilityState
{
public:
	PlayerJumpState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerJumpState();

	PlayerJumpState(const PlayerJumpState& other) = delete;
	PlayerJumpState& operator=(const PlayerJumpState& other) = delete;
	PlayerJumpState(PlayerJumpState&& other) = delete;
	PlayerJumpState& operator=(PlayerJumpState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:

	SoundEffect* m_pJumpSound;
};

