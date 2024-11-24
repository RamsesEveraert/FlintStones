#pragma once
#include "PlayerState.h"

class PlayerAbilityState : public PlayerState
{
public:

	PlayerAbilityState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	virtual ~PlayerAbilityState() = default;

	PlayerAbilityState(const PlayerAbilityState& other) = delete;
	PlayerAbilityState& operator=(const PlayerAbilityState& other) = delete;
	PlayerAbilityState(PlayerAbilityState&& other) = delete;
	PlayerAbilityState& operator=(PlayerAbilityState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

protected:

	bool m_IsAbilityDone;

private:

};

